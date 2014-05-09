#pragma once
#include "GameObject.h"
#include "frame.h"

class CubeSolid : public GameObject
{
public:
	CubeSolid( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double size = 1 )
		: GameObject( parent, position, scale ),
		color( color ), size( size )
	{
	}
	void draw()
	{
		setColor( static_cast<COLOR>(color) );
		glutSolidCube( size );
	}
	COLOR color;
	double size;
};
class BG3D : public GameObject
{
public:
	BG3D( GameObject* parent )
		: GameObject( parent )
	{
		addChild( new CubeSolid( parent,
			Vector3( 0, 0, 5000),
			Vector3( 200, 1, 10000 ),
			TAN ) );

		addChild( new CubeSolid( parent,
			Vector3(0, 0, FINISH+200),
			Vector3( 400, 2, 400 ),
			YELLOW ) );
	}
};