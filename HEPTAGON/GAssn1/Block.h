#pragma once
#include "GameObject.h"

class Game;
class Block : public GameObject
{
public:
	Block( GameObject* parent, int lane, float z );
	void update();
	void draw();

	Game* getParent();
	
	int lane;
	float z;
};
