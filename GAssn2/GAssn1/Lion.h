#pragma once
#include "GameObject.h"

class LionLeg : public GameObject
{
public:
	LionLeg( GameObject* parent, Vector2 pos, int type);
	void update();
	void draw();
	int legType;//앞다리는 0, 뒷다리는 1
	int tick;
};

class LionUnderLeg : public GameObject
{
public:
	LionUnderLeg( GameObject* parent, Vector2 pos, int type);
	void update();
	void draw();
private:
	int legType;
};

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
