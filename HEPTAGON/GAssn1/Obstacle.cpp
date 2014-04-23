#include "Obstacle.h"
#include "frame.h"
#include "Game.h"

Obstacle::Obstacle( GameObject* parent, int lane, float z, int thick )
	: Block( parent, lane, z, thick )
	, startZ( z ), bluffable( true )
{
}
void Obstacle::update()
{
	z = startZ - getParent()->z;
	Block::update();
}
