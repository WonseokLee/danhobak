#include "Block.h"
#include "frame.h"
#include "Game.h"
#include <cmath>

Block::Block( GameObject* parent, int lane, float z, float thick )
	: GameObject( parent )
	, z( z ), thick( thick )
{
	rotation = 360 * lane / 6.f;
	while( lane < 0 )
		lane += 6;
	lane = lane % 6;
	this->lane = lane;
}
void Block::update()
{
	//Game* game = getParent();
	//scale = Vector2( z * game->speedMultiplier + game->base );
}
void Block::draw()
{
	Game* game = getParent();
	float scale = z * game->speedMultiplier + game->base;
	float scale2 = (z+thick) * game->speedMultiplier + game->base;
	if( scale < game->base )
		scale = game->base;
	if( scale2 < game->base )
		return;

	setColor( getParent()->foreColor );
	drawBegin( GL_POLYGON );

	drawVertex2f( -0.57735f * scale, -1.0f * scale );
	drawVertex2f( +0.57735f * scale, -1.0f * scale );
	drawVertex2f( +0.57735f * scale2, -1.0f * scale2 );
	drawVertex2f( -0.57735f * scale2, -1.0f * scale2 );

	drawEnd();
}
Game* Block::getParent()
{
	return static_cast<Game*>( GameObject::getParent() );
}
