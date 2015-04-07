
#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include <Ogre.h>
#include <OIS/OIS.h>

class InputListener : public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:
	InputListener(Ogre::RenderWindow *);
	~InputListener();
	bool	frameRenderingQueued(const Ogre::FrameEvent&);
	void	startOIS();
	void	windowResized(Ogre::RenderWindow*);
	void	windowClosed(Ogre::RenderWindow* wnd);
	bool	checkPause();

private:
    Ogre::RenderWindow* mWindow;
    OIS::InputManager*  mInputManager;
    OIS::Keyboard*      mKeyboard;
	bool				pause;
};

#endif