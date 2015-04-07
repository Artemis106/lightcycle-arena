
#include "PlayerListener.h"

PlayerListener::PlayerListener(Ogre::RenderWindow *wnd, Inputcfg* _in)
{
    mWindow = wnd;
	orient = 0;
	in = _in;
	pad = new bool[4];
	for (int i = 0; i != 4; i++)
		pad[i] = false;
	startOIS();
}

PlayerListener::~PlayerListener()
{
	delete pad;
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
}

bool PlayerListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
    mKeyboard->capture();
	if(mKeyboard->isKeyDown(in->gauche))
		pad[2] = true;
	else
		pad[2] = false;
	if(mKeyboard->isKeyDown(in->droite))
		pad[3] = true;
	else
		pad[3] = false;
	if(mKeyboard->isKeyDown(in->haut))
		pad[0] = true;
	else
		pad[0] = false;
	if(mKeyboard->isKeyDown(in->bas))
	{
		pad[1] = true;
	}
	else
		pad[1] = false;
    return true;
}

void	PlayerListener::startOIS()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
 
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

bool	PlayerListener::getUp()
{
	return(pad[0]);
}

bool	PlayerListener::getDown()
{
	return(pad[1]);
}

bool	PlayerListener::getLeft()
{
	return(pad[2]);
}

bool	PlayerListener::getRight()
{
	return(pad[3]);
}