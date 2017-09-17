/*
-------------------------------------------------------------------------------
    This file is part of ogrekit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Thomas Trocha (dertom)

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

#ifndef DecoratorTween_H
#define DecoratorTween_H

#include <Rocket/Core/Decorator.h>
#include <Core/ElementDefinition.h>
#include <Rocket/Core/Property.h>
#include <Core/ElementStyle.h>
#include <Rocket/Core/Element.h>
#include "gkString.h"
#include "CppTweener.h"
#include "DecoratorTween.h"
#include "utTypes.h"
#include <Rocket/Core/String.h>

#include "Script/Lua/gkLuaScript.h"

#include "Script/Lua/gkLuaManager.h"

#include "gkUtils.h"

using namespace Rocket::Core;

/**
	A decorator used to represent a 'none' decorator; that is, a decorator that does nothing.

	@author Peter Curry
 */

class DecoratorTween : public Decorator
{
	friend class TweenLogic;

	struct DecoratorCall {
	public:
		const ElementDefinition* def;
		gkString m_propName;
	};

	class TweenLogic : public tween::TweenCallback {
	public:
		TweenLogic(Element* elem,const Property* dstProp,const Rocket::Core::String& propertyName,DecoratorTween* decotween,
				const gkString& eventName,const gkString& eventInline)
			: m_decoTween(decotween),m_element(elem),m_property(dstProp),m_isColor(false),
			  m_tweenValue(0),m_tweenValue2(0),m_tweenValue3(0),m_tweenValue4(0),
			  m_cancel(false), m_propertyName(propertyName),m_unit(decotween->m_unit),m_running(false),
			  m_eventFunction(eventName),m_inlineScript(0)
		{
			// create an inline-event if needed
			if (!eventInline.empty())
			{
				m_inlineScript = gkLuaManager::getSingleton().createFromText(gkUtils::getUniqueName(elem->GetId().CString()+gkString("-inline"))
																				,eventInline+" \n");
			}
		}
		virtual ~TweenLogic() {
			if (m_inlineScript) {
				gkLuaManager::getSingleton().destroy(m_inlineScript);
			}
		}
		virtual bool onTweenStep();
		virtual void onTweenComplete();
		void start();

		void callEventScripts(const gkString& eventName);

		Element* m_element;
		const Property* m_property;
		Rocket::Core::String m_propertyName;
		gkString m_unit;
		bool m_isColor;
		float m_tweenValue;
		float m_tweenValue2;
		float m_tweenValue3;
		float m_tweenValue4;

		gkString m_eventFunction;

		DecoratorTween* m_decoTween;
		bool m_cancel;
		bool m_running;
		gkLuaScript* m_inlineScript;

	};
public:

	DecoratorTween() : m_dstValue(0),m_dstValue2(),m_dstValue3(0),m_dstValue4(0),m_time(0),m_repeatTimes(0),m_transition(0),m_wait(0),
						m_equation(0),m_withReverse(0),m_infinite(0),m_styleDef(0)
	{}

	virtual ~DecoratorTween();

	/// Called on a decorator to generate any required per-element data for a newly decorated element.
	/// @param element[in] The newly decorated element.
	/// @return A handle to a decorator-defined data handle, or NULL if none is needed for the element.
	virtual DecoratorDataHandle GenerateElementData(Element* element);
	/// Called to release element data generated by this decorator.
	/// @param element_data[in] The element data handle to release.
	virtual void ReleaseElementData(DecoratorDataHandle element_data);

	/// Called to render the decorator on an element.
	/// @param element[in] The element to render the decorator on.
	/// @param element_data[in] The handle to the data generated by the decorator for the element.
	virtual void RenderElement(Element* element, DecoratorDataHandle element_data);

	bool initalize(int transition,int equation,float time,float wait,Rocket::Core::String propertyName,const Property* dstValue,const gkString& unit,int repeat,
					  bool withReverse,bool infinite,Rocket::Core::String eventFunction,Rocket::Core::String eventInline);
	void startTween();

	static void setTweenLogic(Element* elem, const gkString& property, TweenLogic* logic);
	static DecoratorTween::TweenLogic* getTweenLogic(Element* elem, const gkString& property);
	static bool hasTweenLogic(Element* elem, const gkString& property);
	static void removeTweenLogic(Element* elem, const gkString& property);

private:

	bool isCurrentValueNotDest(const Rocket::Core::Property* prop) {
		if (prop->unit == Property::COLOUR)
		{
			Colourb dstColor = prop->Get<Colourb>();
//			Colourb currentCol = element->GetProperty(m_propertyName)->Get<Colourb)>();
//			if ()
//			m_tweenValue = color.red;
//			m_tweenValue2 = color.green;
//			m_tweenValue3 = color.blue;
//			m_tweenValue4 = color.alpha;
//			m_isColor = true;
			return true;
		}
		else
		{
			float currentFloat = prop->Get<float>();
			if (currentFloat != m_dstValue) {
				int a = 0;
				return true;
			} else {
				return false;
			}
		}

		return false;
	}

//	Element->Property->TweenLogic
	typedef utHashTable<utCharHashKey,TweenLogic*> PropertyLogicMap;
	typedef utHashTable<utPointerHashKey,PropertyLogicMap*> TweenLogicMap;

	static TweenLogicMap m_tweenMap;


	// set this on generation and ask for it on the renderer
	float m_dstValue;
	float m_dstValue2;
	float m_dstValue3;
	float m_dstValue4;

	int m_transition;
	int m_equation;
	float m_time;
	float m_wait;
	Rocket::Core::String m_propertyName;
	Rocket::Core::String m_eventFunction;
	Rocket::Core::String m_eventInline;


	gkString m_unit;
	bool m_withReverse;
	bool m_infinite;
	int m_repeatTimes;

	const ElementDefinition* m_styleDef;

};


#endif
