#include "hurdles.h"
#include "frame.h"
#include "Game.h"

Rock::Rock( GameObject* parent, float z)
	: GameObject( parent, Vector3( 0, 0, z))
{
	myLoader.Load("tri_rock.obj", "tri_rock.mtl");
}

void Rock::draw()
{
	setColor( RED );
	myLoader.Draw(1.0f);
}

Ring::Ring( GameObject* parent, float z)
	: GameObject( parent, Vector3( 0, RING_HEIGHT, z))
{
}

void Ring::draw()
{
	drawRing3D(RING_RADIUS);
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