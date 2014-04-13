#pragma once
#include "GameObject.h"

class LionLeg : public GameObject
{
public:
	LionLeg( GameObject* parent, Vector2 pos, int type, int color);
	void update();
	void draw();
	int legType;//앞다리는 0, 뒷다리는 1
	int tick;
	int color;
	bool jump;
};

class LionUnderLeg : public GameObject
{
public:
	LionUnderLeg( GameObject* parent, Vector2 pos, int type, int color);
	void update();
	void draw();
private:
	int legType;
	int color;
};

class LionTail : public GameObject
{
public:
	LionTail( GameObject* parent, Vector2 pos );
	void update();
	void draw();
};
class LionBody : public GameObject
{
public:
	LionBody( GameObject* parent, Vector2 pos );
	void draw();
};

class Lion : public GameObject
{
public:
	Lion( GameObject* parent );
	void update();
	
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
