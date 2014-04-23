#pragma once
#include "Block.h"
#include "frame.h"

class Obstacle : public Block
{
public:
	Obstacle( GameObject* parent, int lane, float z, float thick = BLOCK_SCALE );
	void update();

	bool bluffable;
	bool lastBlockable; // ���� �����ӿ� ��Ŀ�� ����� �� �ִ� ��ġ�� �־��ٸ� Ʈ��

private:
	float startZ;
};
