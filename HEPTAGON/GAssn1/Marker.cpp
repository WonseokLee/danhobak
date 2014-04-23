#include "Marker.h"
#include "Game.h"
#include "frame.h"

Marker::Marker( GameObject* parent )
	: GameObject( parent )
{
	leftKey = false;
	rotation = CURSOR_SPEED / 2;
}
void Marker::update()
{
	Game* game = getParent();

	if( game->keyLeft && !game->keyRight )
	{
		leftKey = true;
		rotation -= CURSOR_SPEED;
	}
	if( game->keyRight && !game->keyLeft )
	{
		leftKey = false;
		rotation += CURSOR_SPEED;
	}
	if( game->keyLeft && game->keyRight )
	{
		if( leftKey )
			rotation += CURSOR_SPEED;
		else
			rotation -= CURSOR_SPEED;
	}
	if( rotation < 0 )
		rotation += 360;
	if( 360 <= rotation )
		rotation -= 360;
}
void Marker::draw()
{
	Game* game = getParent();
	setColor( game->foreColor );
	drawBegin( GL_TRIANGLES );
	drawVertex2f( -0, -100 );
	drawVertex2f( -9, -88 );
	drawVertex2f( +9, -88 );
	drawEnd();
}
int Marker::getLane()
{
	double r = rotation;
	r = r + 30;
	return ( int(r) % 360 ) / 60;
}
Game* Marker::getParent()
{
	return static_cast<Game*>( GameObject::getParent() );
}