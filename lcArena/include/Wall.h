
#ifndef	WALL_H_
#define WALL_H_

#include <Ogre.h>
#include "Clock.h"

class Wall
{
public:
	Wall(Ogre::SceneManager*, std::string);
	~Wall();
	void	createWall(float, float, float);
private:
	Ogre::SceneNode*	node;
	Ogre::SceneManager*	mgr;
	std::string			wallname;
	int					nb;
};

#endif