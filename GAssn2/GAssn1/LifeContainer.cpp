#include "LifeContainer.h"
#include <cmath>
#include "Game.h"
#include "Lion.h"

Heart::Heart( GameObject* parent, Vector2 position )
	: GameObject( parent, position )
{
	fill = true;
}
void Heart::update()
{
	if( ++tick == 60 )
		tick = 0;

	scale = Vector2( 1.1 + 0.1 * cos( tick * 3.14 / 60 ) );
}
void Heart::draw()
{
	if( fill )
	{
		setColor( RED );
		drawHeart( GL_TRIANGLE_FAN );
	}
	setColor( WHITE );
	setLineWidth(1);
	drawHeart( GL_LINE_LOOP );
}
void Heart::drawHeart( GLenum mode )
{
	drawBegin( mode );
	drawVertex2f(0, -5);
	drawVertex2f(-5, -10);
	drawVertex2f(-10, -10);
	drawVertex2f(-15, -5);
	drawVertex2f(-15, 5);
	drawVertex2f(0, 20);
	drawVertex2f(15, 5);
	drawVertex2f(15, -5);
	drawVertex2f(10, -10);
	drawVertex2f(5, -10);
	drawVertex2f(0, -5);
	drawEnd();
}
LifeContainer::LifeContainer( GameObject* parent )
	: GameObject( parent )
{
	for( int i = 0; i < LIFE_DEFAULT; ++i )
	{
		Heart* heart = new Heart( this, Vector2( -i * 40, 0 ) );
		hearts.push_back( heart );
		addChild( heart );
	}
}
void LifeContainer::update()
{
	Game* game = static_cast<Game*>( getAncestor() );
	position = Vector2( SCREEN_WIDTH - 45 + game->camera, 30 );
	
	Lion* lion = game->lion;
	for( int i = 0; i < LIFE_DEFAULT; ++i )
	{
		hearts[i]->fill = i < lion->life;
	}
}
