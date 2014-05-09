#include "LifeContainer.h"
#include "Game.h"
#include "Lion.h"

Heart::Heart( GameObject* parent, Vector3 position )
	: GameObject( parent, position )
{
	fill = true;
}
void Heart::draw()
{
	setColor( RED );
	setLineWidth(1);
	GLenum mode = fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP;
	drawBegin( mode );
	drawVertex2f(15, 5);
	drawVertex2f(10, 0);
	drawVertex2f(5, 0);
	drawVertex2f(0, 5);
	drawVertex2f(0, 15);
	drawVertex2f(15, 30);
	drawVertex2f(30, 15);
	drawVertex2f(30, 5);
	drawVertex2f(25, 0);
	drawVertex2f(20, 0);
	drawVertex2f(+15, 5);
	drawEnd();
}
LifeContainer::LifeContainer( GameObject* parent )
	: GameObject( parent )
{
	for( int i = 0; i < LIFE_DEFAULT; ++i )
	{
		Heart* heart = new Heart( this, Vector3( -i * 40, 0 ) );
		hearts.push_back( heart );
		addChild( heart );
	}
}
void LifeContainer::update()
{
	Game* game = static_cast<Game*>( getAncestor() );
	position = Vector3( SCREEN_WIDTH - 45 + game->camera, 30 );
	
	Lion* lion = game->lion;
	for( int i = 0; i < LIFE_DEFAULT; ++i )
	{
		hearts[i]->fill = i < lion->life;
	}
}
