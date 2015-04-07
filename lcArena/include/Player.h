
#ifndef	PLAYER_H_
#define	PLAYER_H_

#include <Ogre.h>
#include "Cycle.h"
#include "PlayerListener.h"
#include "Clock.h"
#include "InputCFG.h"
#include "Wall.h"

#define M_PI       3.14159265358979323846
#define SPEED		100.0
#define SPEEDR		100.0

class	Player
{
public:
	Player(Ogre::SceneManager*, Ogre::RenderWindow*, std::string, int, Inputcfg*);
	~Player();
	void			UpdateSpeed();
	void			setViewport(float, float, float, float);
	PlayerListener*	getPL();
	void			setBeginPos();
	Ogre::Vector3 const&	getPos();
	void			initTime();

private:
	Ogre::SceneManager*	mgr;
	Ogre::Camera*		camera;
	Ogre::Viewport*		vp;
	PlayerListener*		key;
	Cycle*				cycle;
	Ogre::SceneNode*	node;
	Wall*				mur;
	int					id;
	float				vitesse_x;
	float				orient;
	float				speed_t;
	float				speed_r;
	float				vitesse_z;
	Clock				clock;
};

#endif