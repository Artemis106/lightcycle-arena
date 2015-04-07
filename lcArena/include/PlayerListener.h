
#ifndef	PLAYERLISTENER_H_
#define PLAYERLISTENER_H_

#include <Ogre.h>
#include <OIS\OIS.h>
#include <math.h>
#include "InputCFG.h"

class PlayerListener : public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:
	PlayerListener(Ogre::RenderWindow*, Inputcfg*);
	~PlayerListener();
	bool	frameRenderingQueued(const Ogre::FrameEvent&);
	void	startOIS();
	bool	getUp();
	bool	getDown();
	bool	getLeft();
	bool	getRight();

private:
    Ogre::RenderWindow* mWindow;
    OIS::InputManager*  mInputManager;
    OIS::Keyboard*      mKeyboard;
	float				orient;
	bool*				pad;
	Inputcfg*			in;
};

#endif