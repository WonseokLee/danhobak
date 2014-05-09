#include "hurdles.h"
#include "frame.h"
#include "Game.h"
#include "ObjLoader.h"

Rock::Rock( GameObject* parent, float z)
	: GameObject( parent, Vector3( 0, 0, z))
{
}

void Rock::draw()
{
	setColor( RED );
	CObjLoader myLoader;
	myLoader.Load("tri_rock.obj", "tri_rock.mtl");
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