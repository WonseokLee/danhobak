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
	setColor( GOLDENROD );
	drawBegin( GL_POLYGON );
	drawVertex2f( -12, -30 );
	drawVertex2f( -18, -15 );
	drawVertex2f( -12, 0 );
	drawVertex2f( +12, 0 );
	drawVertex2f( +18, -15 );
	drawVertex2f( +12, -30 );
	drawEnd();
	setColor( BROWN );
	drawBegin( GL_POLYGON );
	drawVertex2f( -12, -30 );
	drawVertex2f( 0, -27 );
	drawVertex2f( +12, -30 );
	drawEnd();
	setColor( GOLD );
	setLineWidth( 5 );
	drawBegin( GL_LINE_STRIP );
	drawVertex2f( -18, -15 );
	drawVertex2f( 0, -10 );
	drawVertex2f( +18, -15 );
	drawEnd();
}

RingFire::RingFire( GameObject* parent, Vector2& position, int color, double fireScale, int tick, int derivation)
	: GameObject( parent, position ),
	color( color ), fireScale( fireScale ), tick( tick ), derivation(derivation)
{
}
void RingFire::update()
{
	if( ++tick == 60 )
		tick = 0;

	rotation = derivation + sin( (double)tick / 30 * 3.14 ) * 15;

	int t = tick<30?tick:60-tick;
	double s = sin(t / 300.0) + 1;
	scale = fireScale * Vector2( s );
}
void RingFire::draw()
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

RingLeft::RingLeft( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
	const int n = 5;
	const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;
	float radX = 50 / 2;
	float radY = 180 / 2;
	float centerX = -25 + radX;
	float centerY = 0 + radY;

    for(int k = n; k < 3*n; k++)
    {
        float circleX = centerX + radX * cos(k * PI/(2*n));
        float circleY = centerY + radY * sin(k * PI/(2*n));
			addChild( new RingFire( this, Vector2(circleX, circleY), FIRE_RED, 0.70, rand()%60, 30));
	}
	/*
	for(int k = 2*n; k < 3*n; k++)
	{
		float circleX = centerX + radX * cos(k * PI/(2*n));
        float circleY = centerY + radY * sin(k * PI/(2*n)) - 15;
		addChild( new RingFire( this, Vector2(circleX, circleY), FIRE, 0.45, rand()%60));
	}
	*/
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
	setColor( FIRE_DARK );
	drawElipseLeft( -25, 0, 50, 180, false );
	setColor( BLACK );
	drawLine( 0, -10, 0, 5 );
}
RingRight::RingRight( GameObject* parent, float x )
	: GameObject( parent, Vector2( x, 0 ) )
{
	const int n = 5;
	const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;
	float radX = 50 / 2;
	float radY = 180 / 2;
	float centerX = -25 + radX;
	float centerY = 0 + radY;

    for(int k = -n; k < n; k++)
    {
        float circleX = centerX + radX * cos(k * PI/(2*n));
        float circleY = centerY + radY * sin(k * PI/(2*n));
		addChild( new RingFire( this, Vector2(circleX, circleY), FIRE, 0.85, rand()%60, -30));
	}
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
	setColor( FIRE_DARK );
	drawElipseRight( -25, 0, 50, 180, false );
}
