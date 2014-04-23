#pragma once
#include "Block.h"
#include "frame.h"

class CenterBlock : public Block
{
public:
	CenterBlock( GameObject* parent, int lane, float thick = BLOCK_SCALE );
	void update();
	void draw();
};