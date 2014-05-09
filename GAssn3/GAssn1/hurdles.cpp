#include "hurdles.h"
#include "frame.h"
#include "Game.h"

Rock::Rock( GameObject* parent, float z)
	: GameObject( parent, Vector3(0, 30, z), Vector3(1,1,1), -90, Vector3(1, 0, 0))
{
	myLoader.Load("tri_rock.obj", "tri_rock.mtl");
}

void Rock::draw()
{
	setColor( LIGHT_GRAY );
	setLineWidth( 0.5 );
	myLoader.Draw(20);
}

Ring::Ring( GameObject* parent, float z)
	: GameObject( parent, Vector3( 0, RING_HEIGHT, z))
{
}

void Ring::draw()
{
	setColor( RED );
	setLineWidth( 0.1 );
	glutWireTorus( 20.0f, RING_RADIUS, 16, 32 );
}

void Ring::update()
{
	Game* parent = static_cast<Game*>( getAncestor() );
	if( parent->game_state == GAME_ING )
	{
		float& z = pos().z;
		z -= RING_SPEED;
		if( z < RING_REMOVE )
			z = RING_REGEN;
	}
}