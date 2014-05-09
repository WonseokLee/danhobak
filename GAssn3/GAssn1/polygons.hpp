#pragma once
#include "GameObject.h"
#include "frame.h"

class CubeWire : public GameObject
{
public:
	CubeWire( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double drawWidth )
		: GameObject( parent, position, scale ),
		color( color )
	{
	}
	void draw()
	{
		setLineWidth( (float)drawWidth );
		setColor( static_cast<COLOR>(color) );
		glutWireCube( 1 );
	}
	COLOR color;
	double drawWidth;
};

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

class SphereWire : public GameObject
{
public:
	SphereWire( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double drawWidth )
		: GameObject( parent, position, scale ),
		color( color )
	{
	}
	void draw()
	{
		setLineWidth( (float)drawWidth );
		setColor( static_cast<COLOR>(color) );
		glutWireSphere( 1, 16, 16 );
	}
	COLOR color;
	double drawWidth;
};