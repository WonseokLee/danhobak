#include "Block.h"
#include "frame.h"
#include "Game.h"
#include <cmath>

Block::Block( GameObject* parent, int lane, float z )
	: GameObject( parent )
	, z( z )
{
	rotation = 360 * lane / 6.f;
	while( lane < 0 )
		lane += 6;
	lane = lane % 6;
	this->lane = lane;
}
void Block::update()
{
	scale = Vector2( z + getParent()->base );
}
void Block::draw()
{
	if( scale.x < 0 )
		return;

	float thick = 1 + 36/scale.size()*sqrt(2.f);

	setColor( getParent()->foreColor );
	drawBegin( GL_POLYGON );
	drawVertex2f( -0.57735f, -1.0f );
	drawVertex2f( +0.57735f, -1.0f );
	drawVertex2f( +thick* 0.57735f, -thick );
	drawVertex2f( -thick* 0.57735f, -thick );
	drawEnd();
	
}
Game* Block::getParent()
{
	return static_cast<Game*>( GameObject::getParent() );
}
