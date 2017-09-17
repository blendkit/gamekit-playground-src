/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkPath_h_
#define _gkPath_h_

#include "gkCommon.h"
#include "gkString.h"

#include "OgreDataStream.h"
#include "utStreams.h"

#ifdef OGREKIT_BUILD_ANDROID
# include <android/asset_manager.h>
#endif

extern void gkGetCurrentDir(gkString& buf);


// File system path utilities
class gkPath
{
public:
	static const gkString SEPERATOR;

public:

	gkPath();
	gkPath(const gkString& file);
	gkPath(const char* file);
	~gkPath();

	const gkString& getPath(void) const;
	gkString        getAbsPath(void) const;

	gkString        getAsString(void) const;
	utMemoryStream*		getAsStream(void) const;
	Ogre::DataStreamPtr _getAsOgreStream(void) const;
	utMemoryStream*		_getFromFileStream(void) const;

	gkString        directory(void) const;
	gkString        base(void) const;
	gkString        extension(void) const;
	// Uses the generic seperator '/'
	void    normalize(void) const;

	// normalize based on platform seperator
	void    normalizePlatform(void) const;

	int     getFileSize(void) const;
	void    append(const gkString& v);

	bool    isAbs(void) const;
	bool    isRel(void) const;

	bool    exists(void) const;
	bool    isFile(void) const;
	bool    isDir(void) const;
	void    split(gkStringVector& arr) const;

	gkString	findValidPath() const;

	gkString    getBundlePath(void) const;
	bool        isFileInBundle(void) const;
#ifdef OGREKIT_BUILD_ANDROID
	static void setAssetManager(AAssetManager* assetManager);
	static void initAssetManager();
	static void setSDCardPath(const gkString& path);
	bool androidExsitsInAssets() const;
	utMemoryStream* androidLoadFromAssets();
	static gkString getSDCardPath() { return m_sdcardPath;}
	static AAssetManager* getAssetManager() { return m_assetManager;}
	gkString androidGetAsStringFromAssets();


    Ogre::DataStreamPtr androidOpenAsOgreStream();


#endif

protected:
	mutable gkString m_path;




#ifdef OGREKIT_BUILD_ANDROID
	static gkString m_sdcardPath;
	static AAssetManager* m_assetManager;
#endif
};




#endif//_gkPath_h_
