#include "CenterBlock.h"
#include "Game.h"
CenterBlock::CenterBlock( GameObject* parent, int lane )
	: Block( parent, lane, 0 )
{
}
void CenterBlock::update()
{
	scale = Vector2( z + getParent()->base + getParent()->centerBase );
}
