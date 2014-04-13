#include "Lion.h"
#include "Game.h"
#include "frame.h"
#include "configurations.h"

LionLeg::LionLeg( GameObject* parent, Vector2 pos, int type, int color ) 
	: GameObject( parent, pos )
{
	legType = type;
	this->color = color;
	jump = false;
	addChild(new LionUnderLeg(this, Vector2(0, 10), legType, color ));
}

void LionLeg::update()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	tick = -parent->walk_state;

	if(parent->crash > 0){
		switch((parent->crash)%4){
		case 0:
			switch(legType%2){
			case 0:
				color = YELLOW;
				break;
			case 1:
				color = YELLOW_DARK;
			}
			break;
		default:
			switch(legType%2){
			case 0:
				color = YELLOW_TRANS;
				break;
			case 1:
				color = YELLOW_DARK_TRANS;
			}
			break;
		}
	}
	else{
		switch(legType%2){
			case 0:
				color = YELLOW;
				break;
			case 1:
				color = YELLOW_DARK;
			}
	}

	switch(legType){
	case 0: // µÞ¾Õ´Ù¸®
		if(parent->lionJumpHeight == 0){
			pos().x = -20;
			rotation = 30 * cos( tick*3.14/30 ) + 20;
			jump = false;
		}
		else{
			pos().x = -10;
			rotation = -50;
			jump = true;
		}
		break;
	case 1: // µÞµÞ´Ù¸®
		if(parent->lionJumpHeight == 0){
			rotation = -25 * cos( tick*3.14/30 ) + 15;
			jump = false;
		}
		else{
			rotation = -50;
			jump = true;
		}
		break;
	case 2: //¾Õ¾Õ´Ù¸®
		if(parent->lionJumpHeight == 0){
			pos().x = 10;
			rotation = 30 * cos( tick*3.14/30 ) + 20;
			jump = false;
		}
		else{
			pos().x = 20;
			rotation = 50;
			jump = true;
		}
		break;
	case 3: //¾ÕµÞ´Ù¸®
		if(parent->lionJumpHeight == 0){
			rotation = -25 * cos( tick*3.14/30 ) + 15;
			jump = false;
		}
		else{
			rotation = 50;
			jump = true;
		}
		break;
	}
	
}

void LionLeg::draw()
{
	setColor( static_cast<COLOR>(color) );
	drawRectFill(-3, 0, 6, 10);
}

LionUnderLeg::LionUnderLeg( GameObject* parent, Vector2 pos, int type, int color )
	: GameObject( parent, pos )
{
	legType = type;
	this->color = color;
}

void LionUnderLeg::update()
{
	LionLeg* parent = static_cast<LionLeg*>( getParent() );
	int tick = parent->tick;

	this->color = parent->color;

	switch(legType%2){
	case 0: // ¾Õ´Ù¸®
		if(parent->jump)
			rotation = 0;
		else
			rotation = 40 * cos( tick*3.14/30 ) - 40;
		break;
	case 1: // µÞ´Ù¸®
		if(parent->jump)
			rotation = 0;
		else
			rotation = -30 * cos( tick*3.14/30 ) - 30;
		break;
	}
}

void LionUnderLeg::draw()
{
	setColor( static_cast<COLOR>(color) );
	drawRectFill(-3,0, 6, 13);
}
LionTail::LionTail( GameObject* parent, Vector2 pos )
	: GameObject( parent, pos )
{
}
void LionTail::update()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	int tick = -parent->walk_state - 5;
	rotation = 30 * cos( tick*3.14/30 ) + 15;
}
void LionTail::draw()
{
	setColor( BROWN );
	setLineWidth( 3 );
	drawLine( -2, 0, -10, 0 );

}
LionBody::LionBody( GameObject* parent, Vector2 pos )
	: GameObject( parent, pos )
{
}
void LionBody::draw()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	int& crash = parent->crash;

	COLOR my_yellow;
	COLOR my_brown;
	COLOR my_black;
	COLOR my_red;
	if(crash > 0){
		switch(crash%4){
		case 0:
			my_yellow = YELLOW;
			my_brown = BROWN;
			my_black = BLACK;
			my_red = RED;
			break;
		default:
			my_yellow = YELLOW_TRANS;
			my_brown = BROWN_TRANS;
			my_black = BLACK_TRANS;
			my_red = RED_TRANS;
			break;
		}
		crash--;
	}
	else{
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
	setColor(my_black);
	drawRectFill( -30 + 45, head - 25, 10, 16 );
	drawRectFill( -30 + 40, head - 11, 19, 3);
	setColor(my_red);
	drawRectFill( -30 + 44, head - 14, 11, 2);
}
Lion::Lion( GameObject* parent )
	: GameObject( parent, Vector2( LION_DEFAULT, 310 ) )
{
	life = LIFE_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
	crash = 0;
	walk_state = 0;
	addChild( new LionLeg(this, Vector2(+10, 40), 3, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector2(-20, 40), 1, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector2(-20, 40), 0, YELLOW) );
	addChild( new LionLeg(this, Vector2(+10, 40), 2, YELLOW) );
	addChild( new LionBody( this, Vector2(0, 0) ) );
	addChild( new LionTail( this, Vector2(-20, 36) ) );
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
		if(walk_state != 13 && walk_state != 47 && walk_state != 73 && walk_state != 107)
			walk_state++;

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
