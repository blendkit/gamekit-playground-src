/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2012 Thomas Trocha

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
#include "gkTweenManager.h"


gkTweenManager::gkTweenManager()
{
	m_tweener.addListener(this);
}

gkTweenManager::~gkTweenManager()
{
}

void gkTweenManager::update(gkScalar dt)
{
	m_tweener.step(dt*1000);
}

void gkTweenManager::addTween(tween::TweenerParam& param, tween::TweenerListener* listener)
{
	m_tweener.addTween(param);
}

void gkTweenManager::onStart(tween::TweenerParam& param)
{
//	gkLogger::write("on start!",true);
}
void gkTweenManager::onStep(tween::TweenerParam& param)
{
//	gkTweenCallback* callback = static_cast<gkTweenCallback*>(param.owner);
//	callback->onTweenStep();
}
void gkTweenManager::onComplete(tween::TweenerParam& param)
{
//	gkTweenCallback* callback = static_cast<gkTweenCallback*>(param.owner);
//	callback->onTweenComplete();
}

UT_IMPLEMENT_SINGLETON(gkTweenManager)
