#include "hurdles.h"
#include "frame.h"
#include "Game.h"

Jar::Jar( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
}
void Jar::draw()
{
	setColor( GOLD );
	drawRectFill( -15, -30, 30, 30 );
}
RingLeft::RingLeft( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
}
void RingLeft::update()
{
	Game* parent = static_cast<Game*>( getAncestor() );
	if( parent->game_state == GAME_ING )
	{
		float& x = pos().x;
		x -= RING_SPEED;
		if( x < RING_REMOVE )
			x = RING_REGEN;
	}
}
void RingLeft::draw()
{
	setLineWidth( 5 );
	setColor( RED );
	drawElipseLeft( -25, 0, 50, 200, false );
	setColor( BLACK );
	drawLine( 0, -10, 0, 5 );
}
RingRight::RingRight( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
}
void RingRight::update()
{
	Game* parent = static_cast<Game*>( getAncestor() );
	if( parent->game_state == GAME_ING )
	{
		float& x = pos().x;
		x -= RING_SPEED;
		if( x < RING_REMOVE )
			x = RING_REGEN;
	}
}
void RingRight::draw()
{
	setLineWidth( 5 );
	setColor( RED );
	drawElipseRight( -25, 0, 50, 200, false );
}
