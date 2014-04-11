#pragma once
#include "GameObject.h"

class Lion : public GameObject
{
public:
	Lion( GameObject* parent );
	void update();
	void draw();
	
	void moveLion();
	void jumpLion();
	void checkJars();
	void checkRings();

	int life;
	int crash;
	float lionJumpSpeed;
	float lionJumpHeight;
	int walk_state;
};
