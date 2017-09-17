/*
 * gkTemplateNode.h
 *
 *  Created on: Nov 15, 2015
 *      Author: ttrocha
 */

#ifndef PBSTEX_ALBEDO_H_
#define PBSTEX_ALBEDO_H_

#include <BNodes/out-src/src-gen/Generated/gkGamekit.h>

// gkPBSTex_AlbedoImpl

class gkPBSSlotImpl;

class gkPBSTex_AlbedoImpl
		: public gkPBSTex_AlbedoAbstract
{
public:
	gkPBSTex_AlbedoImpl(gkLogicTree* parent, size_t id, const gkString& name="");
	virtual ~gkPBSTex_AlbedoImpl();

	// overwrite delegator(?) methods that get called by the node if no lua-logic is there (or the strategy tells to do it)
	virtual void _initialize(); // called on node-creation
	virtual bool _evaluate(gkScalar tick); // called everytick to check if the update-method should be called
//	virtual void _afterInit2();
	virtual void _update(gkScalar tick); // update your stuff
private:
	bool m_initialized;
	Ogre::TexturePtr m_texPtr;
	gkPBSSlotImpl* m_parentSlot;
};

#endif
