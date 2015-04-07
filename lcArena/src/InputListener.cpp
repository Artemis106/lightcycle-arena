
#include "InputListener.h"

InputListener::InputListener(Ogre::RenderWindow *wnd)
{
    mWindow = wnd;
	pause = false;
	startOIS();
}

InputListener::~InputListener()
{
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;
    mKeyboard->capture();
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
	if(mKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		if (!pause)
			pause = true;
		else
			pause = false;
	}
    return true;
}

void	InputListener::startOIS()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem( pl );
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

void InputListener::windowResized(Ogre::RenderWindow* wnd)
{
    unsigned int width, height, depth;
    int left, top;
    wnd->getMetrics(width, height, depth, left, top);
}

void InputListener::windowClosed(Ogre::RenderWindow* wnd)
{
    if( wnd == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mKeyboard );
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

bool	InputListener::checkPause()
{
	return pause;
}