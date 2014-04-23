#pragma once
#include "Block.h"
#include "frame.h"

class Obstacle : public Block
{
public:
	Obstacle( GameObject* parent, int lane, float z, int thick = BLOCK_SCALE );
	void update();

	bool bluffable;

private:
	float startZ;
};
