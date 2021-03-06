#pragma once
#include "GameObject.h"
#include "frame.h"
#include "polygons.hpp"

class BG3D : public GameObject
{
public:
	BG3D( GameObject* parent )
		: GameObject( parent )
	{
		addChild( new CubeSolidT( parent,
			Vector3( 0, -5, 4500),
			Vector3( 200, 5, 11000 ),
			TAN, "lion_body.jpg" ) );
		/*
		addChild( new CubeSolid( parent,
			Vector3(0, -5, 5250),
			Vector3( 400, 5.1, 400 ),
			YELLOW ) );
		*/
	}
};
