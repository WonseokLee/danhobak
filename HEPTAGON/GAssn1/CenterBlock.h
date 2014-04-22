#pragma once
#include "Block.h"

class CenterBlock : public Block
{
public:
	CenterBlock( GameObject* parent, int lane );
	void update();
	void draw();
};