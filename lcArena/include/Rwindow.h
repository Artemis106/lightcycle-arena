
#ifndef	RWINDOW_H_
#define	RWINDOW_H_

#include <Ogre.h>
#include "InputListener.h"
#include "Player.h"
#include "Arena.h"
#include "InputCFG.h"

class	Rwindow
{
public:
	Rwindow(int);
	~Rwindow();
	bool	Winit();
	bool	Run();

private:
	void				setStruct();
	Ogre::Root			*mRoot;
	Ogre::RenderWindow	*mWindow;
	Ogre::SceneManager	*mSceneMgr;
	Player**			players;
	Inputcfg**			inputs;
	int					nb;
};

#endif