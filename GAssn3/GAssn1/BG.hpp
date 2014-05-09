#pragma once
#include "GameObject.h"

class BG2D : public GameObject
{
public:
	BG2D( GameObject* parent )
		: GameObject( parent, Vector3( -400, -80, 0 ) )
	{
	}
	void draw()
	{
		drawColor( LIME_GREEN );

		setColor( TAN );
		drawRectFill( 0, 0, 11000, 110 );

		setColor( YELLOW );
		drawRectFill( FINISH-30.f, 370, 10, 110 );

		setLineWidth( 3 );
		setColor( WHITE );
		drawLine( 0, 94, 11000, 94 );
		drawLine( 0, 102, 11000, 102 );
		setColor( BLACK );
		drawLine( 0, 440, 11000, 370 );
		
		setLineWidth( 1 );
		drawLine( 0, 445, 11000, 375 );
	}
};