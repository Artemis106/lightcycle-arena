
#include "Arena.h"

Arena::Arena(Ogre::SceneManager* _mSceneMgr, int _index)
{
	// initialisation of the attribut and collision tab
	index = _index;
	for (int i = 0; i != 4; i++)
	{
		realx[i] = 0;
		realy[i] = 0;
	}
	cx = SIZEX*index;
	cy = SIZEY*index;
	mSceneMgr = _mSceneMgr;
	colide = new bool*[cx];
	for (int i = 0; i != cx; i++)
	{
		colide[i] = new bool[cy];
		colide[i][0] = true;
		colide[i][cy - 1] = true;
		colide[0][i] = true;
		if (i != 0 || i != cx)
		{
			for (int j = 1; j != cy-1; j++)
				colide[i][j] = false;
		}
	}
	for (int i = 0; i != cx; i++)
		colide[cx - 1][i] = true;
}

Arena::~Arena()
{
	for (int i = 0; i!= cx; i++)
		delete colide[i];
	delete colide;
}

void	Arena::drawArena()
{
	// drawing the several wall of the arena
	Ogre::Plane Sol(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("sol", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Sol, SIZEX, SIZEY, 1, 1, true, 1, 100, 100, Ogre::Vector3::UNIT_Z);
	Ogre::Entity *EntiteSol= mSceneMgr->createEntity("EntiteSol", "sol");
	EntiteSol->setMaterialName("Arene/Grid");
	Ogre::SceneNode *nodeSol = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeSol->attachObject(EntiteSol);

	Ogre::Plane mur1(Ogre::Vector3::UNIT_Z, -(SIZEY / 2));
	Ogre::MeshManager::getSingleton().createPlane("Mur1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mur1, SIZEX, SIZEZ, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
	Ogre::Entity *EntiteMur1= mSceneMgr->createEntity("EntiteMur1", "Mur1");
	EntiteMur1->setMaterialName("Arene/Mur1");
	Ogre::SceneNode *nodeMur1 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeMur1->attachObject(EntiteMur1);
	nodeMur1->setPosition(Ogre::Vector3(0.0, SIZEZ / 2, 0.0));

	Ogre::Plane mur2(Ogre::Vector3::UNIT_X, -(SIZEX / 2));
	Ogre::MeshManager::getSingleton().createPlane("Mur2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mur2, SIZEY, SIZEZ, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
	Ogre::Entity *EntiteMur2= mSceneMgr->createEntity("EntiteMur2", "Mur2");
	EntiteMur2->setMaterialName("Arene/Mur2");
	Ogre::SceneNode *nodeMur2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeMur2->attachObject(EntiteMur2);
	nodeMur2->setPosition(Ogre::Vector3(0.0, SIZEZ / 2, 0.0));

	Ogre::Plane mur3(Ogre::Vector3::UNIT_Z, -(SIZEY / 2));
	Ogre::MeshManager::getSingleton().createPlane("Mur3", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mur3, SIZEX, SIZEZ, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Y);
	Ogre::Entity *EntiteMur3= mSceneMgr->createEntity("EntiteMur3", "Mur3");
	EntiteMur3->setMaterialName("Arene/Mur3");
	Ogre::SceneNode *nodeMur3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeMur3->attachObject(EntiteMur3);
	nodeMur3->setPosition(Ogre::Vector3(0.0, SIZEZ / 2, 0.0));
	nodeMur3->pitch(Ogre::Degree(180));

	Ogre::Plane mur4(Ogre::Vector3::UNIT_X, -(SIZEX / 2));
	Ogre::MeshManager::getSingleton().createPlane("Mur4", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mur4, SIZEY, SIZEZ, 1, 1, true, 1, 1, 1, -Ogre::Vector3::UNIT_Y);
	Ogre::Entity *EntiteMur4= mSceneMgr->createEntity("EntiteMur4", "Mur4");
	EntiteMur4->setMaterialName("Arene/Mur4");
	Ogre::SceneNode *nodeMur4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeMur4->attachObject(EntiteMur4);
	nodeMur4->setPosition(Ogre::Vector3(0.0, SIZEZ / 2, 0.0));
	nodeMur4->roll(Ogre::Degree(180));

	Ogre::Plane Ciel(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ciel", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Sol, SIZEX, SIZEY, 1, 1, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	Ogre::Entity *EntiteCiel= mSceneMgr->createEntity("EntiteCiel", "ciel");
	EntiteCiel->setMaterialName("Arene/Sky");
	Ogre::SceneNode *nodeCiel = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeCiel->attachObject(EntiteCiel);
	nodeCiel->roll(Ogre::Degree(180));
	nodeCiel->setPosition(Ogre::Vector3(0.0, SIZEZ - 1, 0.0));
}

void	Arena::setColide(int x, int y)
{
	if ((x <= cx && x >= 0) || (y <= cy && y >= 0))
		colide[x][y] = true;
	//set the tab when the lightcycle cross the case
}

bool	Arena::getColide(int x, int y, int id)
{
	if (x >= cx || y >= cy || x <= 0 || y <= 0)
		return true;
	if (realx[id] == x && realy[id] == y)
		return false;
	else
	{
		realx[id] = x;
		realy[id] = y;
		return (colide[x][y]);
	}
	//get if there already is a wall here
}