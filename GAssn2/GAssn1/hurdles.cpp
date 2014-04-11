#include "hurdles.h"
#include "frame.h"

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
	double& x = pos.x;
	x -= RING_SPEED;
	if( x < RING_REMOVE )
		x = RING_REGEN;
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
	double& x = pos.x;
	x -= RING_SPEED;
	if( x < RING_REMOVE )
		x = RING_REGEN;
}
void RingRight::draw()
{
	setLineWidth( 5 );
	setColor( RED );
	drawElipseRight( -25, 0, 50, 200, false );
}
