/*
 * gkTemplateNode.h
 *
 *  Created on: Nov 15, 2015
 *      Author: ttrocha
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <BNodes/out-src/src-gen/Generated/gkGamekit.h>
#include <gkEventManager.h>
#include "gkMessageManager.h"

#include "gkHashedString.h"

#include "gkMathUtils.h"
// gkAccelerometerImpl

class gkAccelerometerImpl
		: public gkAccelerometerAbstract, IEventListener
{
public:
	gkAccelerometerImpl(gkLogicTree* parent, size_t id, const gkString& name="");
	virtual ~gkAccelerometerImpl();

	// overwrite delegator(?) methods that get called by the node if no lua-logic is there (or the strategy tells to do it)
	virtual void _initialize(); // called on node-creation
//	virtual void _afterInit();
//	virtual void _afterInit2();
	virtual bool _evaluate(gkScalar tick); // called everytick to check if the update-method should be called
//	virtual void _preUpdate(); // preUpdate
	virtual void _update(gkScalar tick); // update your stuff
//	virtual void _postUpdate(); // afterUpdate
//	virtual bool debug(rapidjson::Value& jsonNode);
private:
	virtual const gkString & getListenerName(void) { static const gkString name="gkAccelerometerImplListener"; return name;};

	virtual bool handleEvent( IEventData const & event);

	gkHashedString m_eventType;
	gkVector3 m_currentState;
	bool m_isActive;
};

#endif
