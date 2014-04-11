#pragma once
#include "GameObject.h"

class Lion : public GameObject
{
	public:
	Lion( GameObject* parent, float x, float y );
	void update();
	void draw();
};
