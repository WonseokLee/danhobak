#pragma once
#include "GameObject.h"

class Jar : public GameObject
{
public:
	Jar( GameObject* parent, float x );
	void draw();
};

class RingLeft : public GameObject
{
public:
	RingLeft( GameObject* parent, float x );
	void update();
	void draw();
};

class RingRight : public GameObject
{
public:
	RingRight( GameObject* parent, float x );
	void update();
	void draw();
};