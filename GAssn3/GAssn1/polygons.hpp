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