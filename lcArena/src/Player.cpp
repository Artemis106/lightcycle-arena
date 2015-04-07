
#include "Player.h"

Player::Player(Ogre::SceneManager* _mgr, Ogre::RenderWindow* _win, std::string name, int z, Inputcfg* in)
{
	mgr = _mgr;
	id = z;
	name += z;
	vitesse_x = 0;
	vitesse_z = 1;
	speed_t = SPEED;
	speed_r = SPEEDR;
	mur = new Wall(mgr, name);
	key = new PlayerListener(_win, in); // init PlayerListener
	node = mgr->getRootSceneNode()->createChildSceneNode();
	cycle = new Cycle(node, mgr, name);
	camera = mgr->createCamera(name += "Cam");
	node->yaw(Ogre::Degree(270));
	camera->setPosition(Ogre::Vector3(-100, 30 ,0));
	camera->setNearClipDistance(5);
	vp = _win->addViewport(camera, id);
	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	camera->lookAt(node->getPosition().x + 100, node->getPosition().y, node->getPosition().z);
	node->attachObject(camera);
	setBeginPos();
}

Player::~Player()
{
	delete mur;
	delete key;
	delete cycle;
}

void	Player::setBeginPos()
{
	switch (id)
	{
	case 0:
		orient = 0.0;
		node->setPosition(Ogre::Vector3(0.0, 0.0, -400.0));
		break;
	case 1:
		orient = 180.0;
		node->yaw(Ogre::Degree(orient));
		node->setPosition(Ogre::Vector3(0.0, 0.0, 400.0));
		break;
	case 2:
		orient = 90.0;
		node->yaw(Ogre::Degree(orient));
		node->setPosition(Ogre::Vector3(-400.0, 0.0, 0.0));
		break;
	case 3:
		orient = 270.0;
		node->yaw(Ogre::Degree(orient));
		node->setPosition(Ogre::Vector3(400.0, 0.0, 0.0));
		break;
	}
}

void	Player::setViewport(float left, float top, float width, float height)
{
	vp->setDimensions(left, top, width, height);
	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

}

PlayerListener*	Player::getPL()
{
	return(key);
}

void	Player::UpdateSpeed()
{
	float time = clock.GetTime();
	float t = time * speed_t;
	float r = 0.0;
	if (key->getRight() ^ key->getLeft())
		r = time * speed_r;
	if (key->getUp() && !key->getDown())
	{
		if (speed_t < SPEED * 1.5)
			speed_t++;
		if (speed_r > SPEEDR / 1.5)
			speed_r--;
	}
	else
	{
		if (speed_t > SPEED)
			speed_t--;
		if (speed_r < SPEEDR)
			speed_r++;
	}
	if (!key->getUp() && key->getDown())
	{
		if (speed_t > SPEED/1.5)
			speed_t--;
		if (speed_r < SPEEDR*1.5)
			speed_r++;
	}
	else
	{
		if (speed_t < SPEED)
			speed_t++;
		if (speed_r > SPEEDR)
			speed_r--;
	}
	if (key->getLeft() && !key->getRight())
		orient = orient>=359?0:orient += r;
	if (key->getRight() && !key->getLeft())
	{
		orient = orient<=0?359:orient -= r;
		r = -r;
	}
	vitesse_z = cos((float)(M_PI * (orient) / 180)) * t;
	vitesse_x = sin((float)(M_PI * (orient) / 180)) * t;
	node->setPosition(node->getPosition().x + vitesse_x, node->getPosition().y, node->getPosition().z + vitesse_z);
	node->yaw(Ogre::Degree(r));
	mur->createWall(node->getPosition().x, node->getPosition().z, orient);
}

Ogre::Vector3 const&	Player::getPos()
{
	return(node->getPosition());
}

void	Player::initTime()
{
	clock.GetTime();
}
