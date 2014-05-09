#include "Lion.h"
#include "Game.h"
#include "frame.h"
#include "configurations.h"

Lion::Lion( GameObject* parent )
	: GameObject( parent, Vector2( LION_DEFAULT, 310 ) )
{
	life = LIFE_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
	crash = 0;
	walk_state = 0;
}
void Lion::update()
{
	Game* parent = static_cast<Game*>( getParent() );
	if( parent->game_state == GAME_ING )
	{
		moveLion();
		jumpLion();
		checkJars();
		checkRings();
	}
}

void Lion::moveLion()
{
	Game* parent = static_cast<Game*>( getParent() );
	bool& keyLeft = parent->keyLeft;
	bool& keyRight = parent->keyRight;

	if( keyLeft && !keyRight )
		pos().x -= LION_SPEED;
	if( !keyLeft && keyRight )
		pos().x += LION_SPEED;

	if( lionJumpHeight == 0 &&
		( keyLeft || keyRight ))
		walk_state++;
	else
		walk_state = 9;

	if( walk_state > 40 )
		walk_state = 0;

	if( pos().x - 30 < 0 )
		pos().x = 30;
	if( pos().x + 30 > 11000 )
		pos().x = 11000 - 30;
}
void Lion::jumpLion()
{
	Game* parent = static_cast<Game*>( getParent() );

	lionJumpSpeed += LION_JUMP_GRAVITY;
	lionJumpHeight += lionJumpSpeed;
	if( lionJumpHeight <= 0 )
	{
		lionJumpHeight = 0;
		lionJumpSpeed = 0;
		if( parent->keyUp )
		{
			lionJumpSpeed = LION_JUMP_SPEED;
		}
	}
}
void Lion::draw()
{
	COLOR my_yellow_dark;
	COLOR my_yellow;
	COLOR my_brown;
	COLOR my_black;
	COLOR my_red;
	if(crash > 0){
		switch(crash%4){
		case 0:
			my_yellow_dark = YELLOW_DARK;
			my_yellow = YELLOW;
			my_brown = BROWN;
			my_black = BLACK;
			my_red = RED;
			break;
		default:
			my_yellow_dark = YELLOW_DARK_TRANS;
			my_yellow = YELLOW_TRANS;
			my_brown = BROWN_TRANS;
			my_black = BLACK_TRANS;
			my_red = RED_TRANS;
			break;
		}
		crash--;
	}
	else{
		my_yellow_dark = YELLOW_DARK;
		my_yellow = YELLOW;
		my_brown = BROWN;
		my_black = BLACK;
		my_red = RED;
	}
	int head = 24;
	if(walk_state < 10){
		setColor(my_yellow_dark);
		drawRectFill( -30 + 10, -lionJumpHeight + 45, 5, 12 );
		drawRectFill( -30 + 32, -lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( -30 + 10, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 32, -lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( -30 + 8, -lionJumpHeight + 27, 41, 18 );
		drawRectFill( -30 + 19, -lionJumpHeight + 45, 5, 15 );
		drawRectFill( -30 + 41, -lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( -30 + 19, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 41, -lionJumpHeight + 57, 8, 3 );
		drawCircleFill( -30 + 39, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 58, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head+10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head+10, 6);
		setColor(my_yellow);
		drawCircleFill( -30 + 49, -lionJumpHeight + head, 9);
		setColor(my_black);
		drawElipseFill( -30 + 53, -lionJumpHeight + head-3, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine( -30 + 2, -lionJumpHeight + 41, -30 + 9, -lionJumpHeight + 38);
	}
	else if(walk_state < 20){
		head--;
		setColor(my_yellow_dark);
		drawRectFill( -30 + 16, -lionJumpHeight + 45, 5, 12 );
		drawRectFill( -30 + 37, -lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( -30 + 16, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 37, -lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( -30 + 8, -lionJumpHeight + 27, 41, 18 );
		drawRectFill( -30 + 18, -lionJumpHeight + 45, 5, 15 );
		drawRectFill( -30 + 39, -lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( -30 + 18, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 39, -lionJumpHeight + 57, 8, 3 );
		drawCircleFill( -30 + 39, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 58, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head+10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head+10, 6);
		setColor(my_yellow);
		drawCircleFill( -30 + 49, -lionJumpHeight + head, 9);
		setColor(my_black);
		drawElipseFill( -30 + 53, -lionJumpHeight + head-3, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine( -30 + 2, -lionJumpHeight + 41, -30 + 9, -lionJumpHeight + 38);
	}
	else if(walk_state < 30){
		setColor(my_yellow);
		drawRectFill( -30 + 10, -lionJumpHeight + 45, 5, 12 );
		drawRectFill( -30 + 32, -lionJumpHeight + 45, 5, 12 );
		drawRectFill( -30 + 8, -lionJumpHeight + 27, 41, 18 );
		setColor(my_brown);
		drawRectFill( -30 + 10, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 32, -lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow_dark);
		drawRectFill( -30 + 19, -lionJumpHeight + 45, 5, 15 );
		drawRectFill( -30 + 41, -lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( -30 + 19, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 41, -lionJumpHeight + 57, 8, 3 );
		drawCircleFill( -30 + 39, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 58, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head+10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head+10, 6);
		setColor(my_yellow);
		drawCircleFill( -30 + 49, -lionJumpHeight + head, 9);
		setColor(my_black);
		drawElipseFill( -30 + 53, -lionJumpHeight + head-3, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine( -30 + 2, -lionJumpHeight + 35, -30 + 9, -lionJumpHeight + 38);
	}
	else{
		head++;
		setColor(my_yellow_dark);
		drawRectFill( -30 + 18, -lionJumpHeight + 45, 5, 12 );
		drawRectFill( -30 + 37, -lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( -30 + 15, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 34, -lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( -30 + 8, -lionJumpHeight + 27, 41, 18 );
		drawRectFill( -30 + 15, -lionJumpHeight + 45, 5, 15 );
		drawRectFill( -30 + 34, -lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( -30 + 18, -lionJumpHeight + 57, 8, 3 );
		drawRectFill( -30 + 39, -lionJumpHeight + 57, 8, 3 );
		drawCircleFill( -30 + 39, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 58, -lionJumpHeight + head, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head-10, 6);
		drawCircleFill( -30 + 45, -lionJumpHeight + head+10, 6);
		drawCircleFill( -30 + 53, -lionJumpHeight + head+10, 6);
		setColor(my_yellow);
		drawCircleFill( -30 + 49, -lionJumpHeight + head, 9);
		setColor(my_black);
		drawElipseFill( -30 + 53, -lionJumpHeight + head-3, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine( -30 + 2, -lionJumpHeight + 35, -30 + 9, -lionJumpHeight + 38);
	}
	setColor(my_black);
	drawRectFill( -30 + 45, -lionJumpHeight + head - 25, 10, 16 );
	drawRectFill( -30 + 40, -lionJumpHeight + head - 11, 19, 3);
	setColor(my_red);
	drawRectFill( -30 + 44, -lionJumpHeight + head - 14, 11, 2);
	//drawRectFill( 30, -lionJumpHeight, 60, 60 );
}
void Lion::checkJars()
{
	Game* parent = static_cast<Game*>( getParent() );
	auto jarLayer = parent->jarLayer->getChildren();
	for( auto jarIter = jarLayer->begin(); jarIter != jarLayer->end(); ++jarIter ){
		GameObject* jar = *jarIter;
		float x = absPos().x;
		float jarX = jar->absPos().x;
		if( x - 45 <= jarX && jarX <= x + 45 )
		{
			if( lionJumpHeight <= JAR_HEIGHT )
			{
				//Ãæµ¹ÇÔ.
				if( crash == 0 )
				{
					crash = LION_FLASH_TIME;
					life--;
				}
			}
		}
	}
}

void Lion::checkRings()
{
	Game* parent = static_cast<Game*>( getParent() );
	auto ringLayer = parent->ringLayer->getChildren();
	for(auto ringIter = ringLayer->begin(); ringIter != ringLayer->end(); ++ringIter ){
		GameObject* ring = *ringIter;
		float x = absPos().x;
		float ringX = ring->absPos().x;
		if( x - 30 <= ringX && ringX <= x + 30 ){
			if( lionJumpHeight < RING_BOTTOM || lionJumpHeight > RING_TOP )
			{
				if( crash == 0 )
				{
					crash = LION_FLASH_TIME;
					life--;
				}
			}
			break;
		}
	}
}
