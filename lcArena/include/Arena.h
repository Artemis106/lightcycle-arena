
#ifndef ARENA_H_
#define ARENA_H_

#include <Ogre.h>

#define SIZEX 1000
#define SIZEY 1000
#define SIZEZ 125

class	Arena
{
public:
	Arena(Ogre::SceneManager*, int);
	~Arena();
	void	drawArena();
	void	setColide(int, int);
	bool	getColide(int, int, int);

private:
	int			realx[4];
	int			realy[4];
	int			index;
	int			cx;
	int			cy;
	Ogre::SceneManager*	mSceneMgr;
	bool**	colide;
};

#endif