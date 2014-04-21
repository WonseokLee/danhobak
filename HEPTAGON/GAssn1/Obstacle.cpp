#include "Obstacle.h"
#include "frame.h"
#include "Game.h"

Obstacle::Obstacle( GameObject* parent, int lane, float z )
	: Block( parent, lane, z )
	, startZ( z ), bluffable( true )
{
}
void Obstacle::update()
{
	z = startZ - getParent()->z;
	Block::update();
}
