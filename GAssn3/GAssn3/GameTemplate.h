#pragma once
#include "GameObject.h"

class GameTemplate : public GameObject
{
public:
	GameTemplate(){};
	virtual ~GameTemplate(){};
	virtual void keyboard( unsigned char key ){};
	virtual void keyboardUp( unsigned char key ){};
	virtual void special( int key ){};
	virtual void specialUp( int key ){};
};