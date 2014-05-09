#pragma once
#include "GameObject.h"
#include "ObjLoader.h"

class Rock : public GameObject
{
public:
	Rock( GameObject* parent, float z);
	virtual void draw();
	
	CObjLoader myLoader;
};

class Ring : public GameObject
{
public:
	Ring( GameObject* parent, float z);
	virtual void draw();
	virtual void update();
};

