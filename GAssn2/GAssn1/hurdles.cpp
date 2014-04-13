#include "hurdles.h"
#include "frame.h"
#include "Game.h"
#include <cmath>

JarFire::JarFire( GameObject* parent, Vector2& position, int color, double fireScale )
	: GameObject( parent, position ),
	color( color ), fireScale( fireScale ), tick( 0 )
{
}
void JarFire::update()
{
	if( ++tick == 60 )
		tick = 0;

	rotation = sin( (double)tick / 30 * 3.14 ) * 5;

	int t = tick<30?tick:60-tick;
	double s = sin(t / 300.0) + 1;
	scale = fireScale * Vector2( s );
}
void JarFire::draw()
{
	setColor( static_cast<COLOR>(color) );
	drawBegin( GL_POLYGON );
	drawVertex2f( 0, -30 );
	drawVertex2f( -7, -15 );
	drawVertex2f( -10, -6 );
	drawVertex2f( -6, +1 );
	drawVertex2f( +6, +1 );
	drawVertex2f( +10, -6 );
	drawVertex2f( +7, -15 );
	drawEnd();
}
Jar::Jar( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
	addChild( new JarFire( this, Vector2( 0, -30 ), RED , 1 ) );
	addChild( new JarFire( this, Vector2( 0, -30 ), WHITE , 0.55 ) );
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
