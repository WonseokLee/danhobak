#pragma once
#include "GameObject.h"

class Rock : public GameObject
{
public:
	Rock( GameObject* parent, float z);
	virtual void draw();
};

class Ring : public GameObject
{
public:
	Ring( GameObject* parent, float z);
	virtual void draw();
	virtual void update();
};

