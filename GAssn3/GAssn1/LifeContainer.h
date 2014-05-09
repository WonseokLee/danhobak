#pragma once
#include "GameObject.h"
#include "frame.h"

class Heart : public GameObject
{
public:
	Heart( GameObject* parent, Vector3 position );
	void draw();
	bool fill;
};

class LifeContainer : public GameObject
{
public:
	LifeContainer( GameObject* parent );
	void update();

private:
	std::vector<Heart*> hearts;
};
