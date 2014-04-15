#pragma once
#include "GameObject.h"

class BG : public GameObject
{
public:
	BG( GameObject* parent )
		: GameObject( parent )
	{
	}
	void draw()
	{
		drawColor( TAN );
		Game* game = static_cast<Game*>( getParent() );
		switch(game->stage){
		case 0:
			setColor(LIME_GREEN);
			break;
		case 1:
			setColor(GREEN_DARK);
			break;
		case 2:
			setColor(BLUE);
			break;
		case 3:
			setColor(BLUE_VIOLET);
			break;
		}
		drawRectFill( 0, 110, 11000, 370 );

		setColor( YELLOW );
		drawRectFill( FINISH-30.f, 370, 10, 110 );

		setLineWidth( 3 );
		setColor( WHITE );
		drawLine( 0, 94, 11000, 94 );
		drawLine( 0, 102, 11000, 102 );
		setColor( BLACK );
		drawLine( 0, 370, 11000, 370 );
		
		setLineWidth( 1 );
		drawLine( 0, 375, 11000, 375 );
	}
};