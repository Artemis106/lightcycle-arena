
#include "Rwindow.h"
#include "Wall.h"

Rwindow::Rwindow(int i): mRoot(0)
{
	players = new Player*[4];
	inputs = new Inputcfg*[4];
	nb = i;
}

Rwindow::~Rwindow()
{
	for(int i = 0; i != nb; i++)
		delete players[i];
	for (int i = 0; i != 4; i++)
		delete inputs[i];
	delete inputs;
	delete players;
	delete mRoot;
}

bool Rwindow::Winit()
{
	mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
	Ogre::ConfigFile configFile;
	configFile.load("resources.cfg");
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}
	mWindow = mRoot->initialise(true, "Lightcycle Arena");
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Mon Scene Manager");
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	setStruct();
    return true;
}

bool	Rwindow::Run()
{
	if (nb < 1 || nb > 4)
		return false;
	InputListener* input = new InputListener(this->mWindow);
	mRoot->addFrameListener(input);
	for (int i = 0; i != nb; i++)
		players[i] = new Player(mSceneMgr, mWindow, "Player", i, inputs[i]);
	switch (nb)
	{
	case 1:
		break;
		case 2:
			players[0]->setViewport(0.0, 0.0, 0.49, 1.0);
			players[1]->setViewport(0.51, 0.0, 0.49, 1.0);
			break;
		case 3:
			players[0]->setViewport(0.0, 0.0, 0.49, 0.49);
			players[1]->setViewport(0.51, 0.0, 0.49, 0.49);
			players[2]->setViewport(0.0, 0.51, 0.49, 0.49);
			break;
		case 4:
			players[0]->setViewport(0.0, 0.0, 0.49, 0.49);
			players[1]->setViewport(0.51, 0.0, 0.49, 0.49);
			players[2]->setViewport(0.0, 0.51, 0.49, 0.49);
			players[3]->setViewport(0.51, 0.51, 0.49, 0.49);
			break;
	}
	for (int i = 0; i != nb; i++)
		mRoot->addFrameListener(players[i]->getPL());
	int index = 1;
	Arena arene(mSceneMgr, index);
	arene.drawArena();
	float x = 0.0;
	float y = 0.0;
	for	(int i = 0; i!=nb; i++)
		players[i]->initTime();
	while(true)
	{
		Ogre::WindowEventUtilities::messagePump();
		for	(int i = 0; i!=nb; i++)
		{
			if (players[i] != NULL)
			{
				players[i]->UpdateSpeed();
				x =(players[i]->getPos().z + 500)*index;
				y =(players[i]->getPos().x + 500)*index;
				if(arene.getColide((int)x, (int)y, i))
				{
					mRoot->removeFrameListener(players[i]->getPL());
					delete players[i];
					players[i] = NULL;
				}
				arene.setColide((int)x, (int)y);
			}
		}
		if(mWindow->isClosed())
			return false;
		if(!mRoot->renderOneFrame())
			return false;
	}
	return(true);
}

void	Rwindow::setStruct()
{
	for (int i = 0; i != 4; i++)
		inputs[i] = new Inputcfg();
	inputs[0]->haut = OIS::KC_W;
	inputs[0]->bas = OIS::KC_S;
	inputs[0]->droite = OIS::KC_D;
	inputs[0]->gauche = OIS::KC_A;
	inputs[2]->haut = OIS::KC_UP;
	inputs[2]->bas = OIS::KC_DOWN;
	inputs[2]->droite = OIS::KC_RIGHT;
	inputs[2]->gauche = OIS::KC_LEFT;
	inputs[1]->haut = OIS::KC_I;
	inputs[1]->bas = OIS::KC_K;
	inputs[1]->droite = OIS::KC_L;
	inputs[1]->gauche = OIS::KC_J;
	inputs[3]->haut = OIS::KC_8;
	inputs[3]->bas = OIS::KC_2;
	inputs[3]->droite = OIS::KC_6;
	inputs[3]->gauche = OIS::KC_4;
}