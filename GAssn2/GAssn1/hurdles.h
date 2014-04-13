#pragma once
#include "GameObject.h"

class JarFire : public GameObject
{
public:
	JarFire( GameObject* parent, Vector2& position );
	void update();
	void draw();
private:
	int tick;
};

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
