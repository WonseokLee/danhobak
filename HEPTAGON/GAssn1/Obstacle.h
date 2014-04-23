#pragma once
#include "Block.h"
#include "frame.h"

class Obstacle : public Block
{
public:
	Obstacle( GameObject* parent, int lane, float z, float thick = BLOCK_SCALE );
	void update();

	bool bluffable;
	bool lastBlockable; // 이전 프레임에 마커를 블락할 수 있는 위치에 있었다면 트루

private:
	float startZ;
};
