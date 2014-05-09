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
		addChild( new CubeSolid( parent,
			Vector3( 0, 0, 5000),
			Vector3( 200, 5, 10000 ),
			TAN ) );

		addChild( new CubeSolid( parent,
			Vector3(0, 0, FINISH+200),
			Vector3( 400, 5, 400 ),
			YELLOW ) );
	}
};