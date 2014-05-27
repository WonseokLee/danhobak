#include "Lion.h"
#include "Game.h"
#include "frame.h"
#include "configurations.h"
#include "polygons.hpp"

LionLeg::LionLeg( GameObject* parent, Vector3 pos, int type, int color ) 
	: GameObject( parent, pos )
{
	legType = type;
	this->color = color;
	jump = false;
	addChild( new CubeSolidT( this,
		Vector3( 0, -8, 0 ),
		Vector3( 6, 8, 6 ),
		YELLOW, "lion_under_leg.jpg", 2 ) );
	addChild(new LionUnderLeg(this, Vector3(0, -15, 0), legType, color ));
	rotationV = Vector3( -1, 0, 0 );
}

void LionLeg::update()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	tick = -parent->walk_state;

	switch(legType){
	case 0: // µÞ¾Õ´Ù¸®
		if(parent->lionJumpHeight == 0){
			//pos().z = -20;
			rotation = 30 * cos( tick*3.14/30 ) + 20;
			jump = false;
		}
		else{
			//pos().z = -10;
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
			pos().z = 10;
			rotation = 30 * cos( tick*3.14/30 ) + 20;
			jump = false;
		}
		else{
			pos().z = 20;
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
LionUnderLeg::LionUnderLeg( GameObject* parent, Vector3 pos, int type, int color )
	: GameObject( parent, pos )
{
	legType = type;
	this->color = color;
	addChild( new CubeSolidT( this,
		Vector3( 0, -8, 0 ),
		Vector3( 6, 8, 6 ),
		YELLOW,"lion_under_leg.jpg", 2) );
	//addChild(new LionUnderLeg(this, Vector3(0, -10), legType, color ));
	rotationV = Vector3( -1, 0, 0 );
	//drawRectFill(-3,0, 6, 13);
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
	//setColor( static_cast<COLOR>(color) );
	//drawRectFill(-3,0, 6, 13);
}
LionTail::LionTail( GameObject* parent, Vector3 pos )
	: GameObject( parent, pos )
{
	addChild( new CubeSolidT( this,
		Vector3( 0, 0, -10 ),
		Vector3( 6, 6, 12 ),
		BROWN, "lion_tail.jpg", 1 ) );
	rotationV = Vector3( -1, 0, 0 );
}
void LionTail::update()
{
	Lion* parent = static_cast<Lion*>( getParent() );
	int tick = -parent->walk_state - 5;
	rotation = 30 * cos( tick*3.14/30 ) + 15;
}
void LionTail::draw()
{
	//setColor( BROWN );
	//setLineWidth( 3 );
	//drawLine( -2, 0, -10, 0 );
}
LionBody::LionBody( GameObject* parent, Vector3 pos )
	: GameObject( parent, pos )
{
	addChild( new SphereSolidT( this, Vector3( 0, 20, 20 ), Vector3( 15, 15, 15 ), YELLOW , "lion_head.jpg") );

	addChild( new SphereSolidT( this, Vector3( 0, 15, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );
	addChild( new SphereSolidT( this, Vector3( -12, 20, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );
	addChild( new SphereSolidT( this, Vector3( +12, 20, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );
	addChild( new SphereSolidT( this, Vector3( -12, 30, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );
	addChild( new SphereSolidT( this, Vector3( +12, 30, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );
	addChild( new SphereSolidT( this, Vector3( 0, 35, 20 ), Vector3( 10, 10, 10 ), BROWN , "lion_hair.jpg") );

	
	addChild( new CubeSolidT( this,
		Vector3( 0, 0, -5 ),
		Vector3( 10, 10, 20 ),
		YELLOW, "lion_body.jpg" ) );
}
Lion::Lion( GameObject* parent )
	: GameObject( parent, Vector3( 0, 0, LION_DEFAULT ) )
{
	life = LIFE_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
	crash = 0;
	walk_state = 0;
	addChild( new LionLeg(this, Vector3(-10, 30, 10), 3, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector3(-10, 30, -20), 1, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector3(10, 30, -20), 0, YELLOW) );
	addChild( new LionLeg(this, Vector3(10, 30, 10), 2, YELLOW) );
	/*
	addChild( new LionLeg(this, Vector2(+10, 40), 3, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector2(-20, 40), 1, YELLOW_DARK) );
	addChild( new LionLeg(this, Vector2(-20, 40), 0, YELLOW) );
	addChild( new LionLeg(this, Vector2(+10, 40), 2, YELLOW) );
	*/
	addChild( new LionBody( this, Vector3(0, 25, 0) ) );
	addChild( new LionTail( this, Vector3(0, 36, -20) ) );
}
void Lion::update()
{
	Game* parent = static_cast<Game*>( getParent() );
	if( parent->game_state == GAME_ING )
	{
		if( crash > 0 ) crash--;
		moveLion();
		jumpLion();
		checkJars();
		checkRings();
	}
}

void Lion::moveLion()
{
	Game* parent = static_cast<Game*>( getParent() );
	bool& keyDown = parent->keyDown;
	bool& keyUp = parent->keyUp;

	if( lionJumpHeight > 0 )
	{
		pos().z += jumpDirection;
	}
	else
	{
		if( keyDown && !keyUp )
			pos().z -= LION_SPEED;
		if( !keyDown && keyUp )
			pos().z += LION_SPEED;
	}

	if( lionJumpHeight == 0 &&
		( keyDown || keyUp ))
		walk_state++;
	else
		walk_state = 9;

	if( walk_state > 120 )
		walk_state = 0;

	if( pos().z  < 0 )
		pos().z = 0;
	if( pos().z  > 11000 )
		pos().z = 11000;
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
		if( parent->keySpace )
		{
			lionJumpSpeed = LION_JUMP_SPEED;
			jumpDirection = 0;
			if( parent->keyDown && !parent->keyUp )
				jumpDirection = -LION_SPEED;
			if( !parent->keyDown && parent->keyUp )
				jumpDirection = LION_SPEED;
		}
	}

	pos().y = lionJumpHeight;
}
void Lion::checkJars()
{
	Game* parent = static_cast<Game*>( getParent() );
	auto rockLayer = parent->rockLayer->getChildren();
	for( auto rockIter = rockLayer->begin(); rockIter != rockLayer->end(); ++rockIter ){
		GameObject* rock = *rockIter;
		float z = absPos().z;
		float rockZ = rock->absPos().z - 20;
		//float rockZ = rock->absPos().z;
		if( z - 45 <= rockZ && rockZ <= z + 45 )
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
		float z = absPos().z;
		float ringZ = ring->absPos().z;
		if( z - 30 <= ringZ && ringZ <= z + 30 ){
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
