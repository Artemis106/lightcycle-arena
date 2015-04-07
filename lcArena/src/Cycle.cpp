
#include <sstream>
#include "Arena.h"
#include "Cycle.h"

Cycle::Cycle(Ogre::SceneNode* _node, Ogre::SceneManager* _mgr, std::string name)
{
	mSceneMgr = _mgr;
	nb = 0;
	node = _node;
	ent = _mgr->createEntity(name, "jt_Root_C.mesh");
	node->attachObject(ent);
	node->setScale(Ogre::Vector3(4, 4, 4));

}

Cycle::~Cycle()
{
	ent->detachFromParent();
}
