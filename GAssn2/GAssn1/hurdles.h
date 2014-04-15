#pragma once
#include "GameObject.h"

class JarFire : public GameObject
{
public:
	JarFire( GameObject* parent, Vector2& position, int color, double fireScale );
	void update();
	void draw();
private:
	int tick;
	int color;
	double fireScale;
};

class Jar : public GameObject
{
public:
	Jar( GameObject* parent, float x );
	void draw();
};

class RingFireGraphic : public GameObject
{
public:
	RingFireGraphic( GameObject* parent, int color, double fireScale );
	void draw();
private:
	int color;
};
class RingFire : public GameObject
{
public:
	RingFire( GameObject* parent, Vector2& position, int color, double fireScale, int tick, int derivation);
	void update();
private:
	int tick;
	int derivation;
	double fireScale;
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
