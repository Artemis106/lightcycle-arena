
#ifndef	CYCLE_H_
#define	CYCLE_H_

#include <Ogre.h>
#include "PlayerListener.h"

class	Cycle
{
public:
	Cycle(Ogre::SceneNode*, Ogre::SceneManager*, std::string);
	~Cycle();
	
private:
	Ogre::Entity*		ent;
	Ogre::SceneNode*	node;
	Ogre::SceneManager* mSceneMgr;
	int					nb;
};

#endif