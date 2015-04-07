
#include "Wall.h"

Wall::Wall(Ogre::SceneManager* _mgr, std::string name)
{
	wallname = name + "Wall";
	nb = 0;
	mgr = _mgr;
	node = mgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Plane wall(Ogre::Vector3::UNIT_X, 0);
	Ogre::MeshManager::getSingleton().createPlane("Wall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall, 2, 10, 1, 1, false, 1, 1, 1, Ogre::Vector3::UNIT_Y);
}

Wall::~Wall()
{
	node->detachAllObjects();
}

void	Wall::createWall(float z, float x, float angle)
{
	nb++;
	wallname += nb;
	Ogre::Entity *EntiteMurSide1 = mgr->createEntity(wallname + "w1", "Wall");
	Ogre::Entity *EntiteMurSide2 = mgr->createEntity(wallname + "w2", "Wall");
	EntiteMurSide1->setMaterialName("Arene/Wall");
	EntiteMurSide2->setMaterialName("Arene/Wall");
	Ogre::SceneNode* node1 = node->createChildSceneNode();
	Ogre::SceneNode* node2 = node->createChildSceneNode();
	node1->attachObject(EntiteMurSide1);
	node2->attachObject(EntiteMurSide2);
	node1->setPosition(z, 0.0, x);
	node2->setPosition(z, 0.0, x);
	node2->roll(Ogre::Degree(180));
	node1->yaw(Ogre::Degree(angle));
	node2->yaw(Ogre::Degree(-angle));
}
