#pragma once
#include "Block.h"

class Obstacle : public Block
{
public:
	Obstacle( GameObject* parent, int lane, float z );
	void update();

	bool bluffable;

private:
	float startZ;
};
