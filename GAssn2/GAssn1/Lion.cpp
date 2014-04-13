#include "Lion.h"
#include "Game.h"
#include "frame.h"
#include "configurations.h"

LionLeg::LionLeg( GameObject* parent, Vector2 pos, int type) 
	: GameObject( parent, pos)
{
	legType = type;
		/*
	switch(legType){
	case 0:
		tick = 32;
		break;
	case 1:
		tick = 2;
	}
	*/
	addChild(new LionUnderLeg(this, Vector2(0, 10), legType));
}

void LionLeg::update()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	
	switch(legType){
	case 0:
		tick = -parent->walk_state;
		break;
	case 1:
		tick = parent->walk_state;
		break;
	}
	/*
	if(++tick == 60)
		tick = 0;
		*/
	rotation = 60 * sin( tick*3.14/60);
}

void LionLeg::draw()
{
	setColor(YELLOW);
	drawRectFill(-3, 0, 6, 10);
}

LionUnderLeg::LionUnderLeg( GameObject* parent, Vector2 pos, int type)
	: GameObject( parent, pos)
{
	legType = type;
}

void LionUnderLeg::update()
{
	LionLeg* parent = static_cast<LionLeg*>( getParent() );
	int parentRotation = 60 * sin((parent->tick)*3.14/30);
	switch(legType){
	case 0:
		if(parentRotation < 0){
			rotation = -10;
		}
		else if(parentRotation < 20){
			rotation = -0.5*parentRotation - 10;
		}
		else if(parentRotation < 45){
			rotation = 0.8*parentRotation - 36;
		}
		else{
			rotation = 0.4*parentRotation - 18;
		}
		break;
	case 1:
		if(parentRotation < 10){
			rotation = -(parentRotation + 60)/7;
		}
		else{
			rotation = -(1.4*parentRotation - 4);
		}
		break;
	}
}

void LionUnderLeg::draw()
{
	drawRectFill(-3,0, 6, 10);
}

Lion::Lion( GameObject* parent )
	: GameObject( parent, Vector2( LION_DEFAULT, 310 ) )
{
	life = LIFE_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
	crash = 0;
	walk_state = 0;
	addChild( new LionLeg(this, Vector2(-30 + 41, 40), 0));
	addChild( new LionLeg(this, Vector2(-30 + 10, 40), 1));
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

	if( walk_state > 120 )
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
	pos().y = 310 - lionJumpHeight;
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
		setColor(my_yellow);
		drawRectFill( -30 + 8, 27, 41, 18 );
		setColor(my_brown);
		drawCircleFill( -30 + 39, head, 6);
		drawCircleFill( -30 + 58,  head, 6);
		drawCircleFill( -30 + 45, head-10, 6);
		drawCircleFill( -30 + 53, head-10, 6);
		drawCircleFill( -30 + 45, head+10, 6);
		drawCircleFill( -30 + 53, head+10, 6);
		setColor(my_yellow);
		drawCircleFill( -30 + 49, head, 9);
		setColor(my_black);
		drawElipseFill( -30 + 53, head-3, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine( -30 + 2, 41, -30 + 9, 38);
	setColor(my_black);
	drawRectFill( -30 + 45, head - 25, 10, 16 );
	drawRectFill( -30 + 40, head - 11, 19, 3);
	setColor(my_red);
	drawRectFill( -30 + 44, head - 14, 11, 2);
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
