#include "Game.h"
#include "frame.h"

#include <stdlib.h>
#include <time.h>

Game::Game()
{
	setWindowTitle( "사자야 우리 저거 사자" );
	srand((unsigned)time(NULL));
	makeJars();
	makeRings();

	camera = CAMERA_DEFAULT;
	lion = LION_DEFAULT;
	life = LIFE_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
	crash = 0;
	walk_state = 0;
	keyLeft = false;
	keyRight = false;
	keyUp = false;
}
Game::~Game()
{

}
void Game::update()
{
	moveRings();
	moveLion();
	jumpLion();
	checkJars();
	checkRings();
	moveCamera();
}
void Game::special( int key )
{
	if ( key == GLUT_KEY_LEFT )
		keyLeft = true;
	if ( key == GLUT_KEY_RIGHT )
		keyRight = true;
	if ( key == GLUT_KEY_UP )
		keyUp = true;
}
void Game::specialUp( int key )
{
	if ( key == GLUT_KEY_LEFT )
		keyLeft = false;
	if ( key == GLUT_KEY_RIGHT )
		keyRight = false;
	if ( key == GLUT_KEY_UP )
		keyUp = false;
}
void Game::display()
{
	drawBG( );
	drawRingsRight( );
	drawLion( );
	drawRingsLeft( );
	drawJars();
	drawLife();
}
void Game::moveLion()
{
	if( keyLeft && !keyRight )
		lion -= LION_SPEED;
	if( !keyLeft && keyRight )
		lion += LION_SPEED;

	if( walk_state < 40 && lionJumpHeight == 0)
		walk_state++;
	else
		walk_state = 0;

	if( lion - 30 < 0 )
		lion = 30;
	if( lion + 30 > 11000 )
		lion = 11000 - 30;
}
void Game::jumpLion()
{
	lionJumpSpeed += LION_JUMP_GRAVITY;
	lionJumpHeight += lionJumpSpeed;
	if( lionJumpHeight <= 0 )
	{
		lionJumpHeight = 0;
		lionJumpSpeed = 0;
		if( keyUp )
		{
			lionJumpSpeed = LION_JUMP_SPEED;
		}
	}
}
void Game::moveCamera()
{
	if( lion - LION_CAMERA > camera )
	{
		camera = lion - LION_CAMERA;
	} else if( lion - LION_CAMERA_MIN < camera ){
		camera = lion - LION_CAMERA_MIN;
	}

	if( camera < 0 )
		camera = 0;

	if( camera + SCREEN_WIDTH > 11000 )
		camera = 11000 - SCREEN_WIDTH;
	setCamera( camera, 0 );
}
void Game::makeJars()
{
	float currentDistance = JAR_GEN_MIN;
	jars.push_back(currentDistance);
	while(currentDistance < JAR_GEN_MAX){
		//generate random value between JAR_DIST_MIN ~ JAR_DIST_MAX, which determines distance between
		//ith and (i+1)th component.
		currentDistance += (float)((JAR_DIST_MAX - JAR_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + JAR_DIST_MIN);
		jars.push_back(currentDistance);
	}
}
void Game::makeRings()
{
	float currentDistance = RING_GEN_MIN;
	rings.push_back(currentDistance);
	while(currentDistance < RING_GEN_MAX){
		currentDistance += (float)((RING_DIST_MAX - RING_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + RING_DIST_MIN);
		rings.push_back(currentDistance);
	}
}
void Game::moveRings()
{
	for( auto ringIter = rings.begin(); ringIter != rings.end(); ++ringIter )
	{
		float& ring = *ringIter;
		ring -= RING_SPEED;
		if( ring < RING_REMOVE )
			ring = RING_REGEN;
	}
}
void Game::drawBG()
{
	drawColor( TAN );

	setColor( LIME_GREEN );
	drawRectFill( 0, 110, 11000, 370 );

	setLineWidth( 3 );
	setColor( BLACK );
	drawLine( 0, 370, 11000, 370 );
}
void Game::drawJars()
{
	for each( float jar in jars )
	{
		setColor( GOLD );
		drawRectFill( jar - 15, 340, 30, 30 );
	}
}
void Game::drawRingsLeft()
{
	for each( float ring in rings )
	{
		setLineWidth( 5 );
		setColor( RED );
		drawElipseLeft( ring-25, 120, 50, 200, false );
		
		setColor( BLACK );
		drawLine( ring, 110, ring, 125 );
	}
}
void Game::drawRingsRight( )
{
	for each( float ring in rings )
	{
		setLineWidth( 5 );
		setColor( RED );
		drawElipseRight( ring - 25, 120, 50, 200, false );
	}
}
void Game::drawLion()
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
	if(walk_state < 10){
		setColor(my_yellow_dark);
		drawRectFill( lion - 30 + 10, 310 - lionJumpHeight + 45, 5, 12 );
		drawRectFill( lion - 30 + 32, 310 - lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 10, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 32, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( lion - 30 + 8, 310 - lionJumpHeight + 27, 41, 18 );
		drawRectFill( lion - 30 + 19, 310 - lionJumpHeight + 45, 5, 15 );
		drawRectFill( lion - 30 + 41, 310 - lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 19, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 41, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawCircleFill(lion - 30 + 49, 310 - lionJumpHeight + 25, 9);
		setColor(my_black);
		drawElipseFill(lion - 30 + 53, 310 - lionJumpHeight + 22, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine(lion - 30 + 2, 310 - lionJumpHeight + 41, lion - 30 + 9, 310 - lionJumpHeight + 38);
	}
	else if(walk_state < 20){
		setColor(my_yellow_dark);
		drawRectFill( lion - 30 + 16, 310 - lionJumpHeight + 45, 5, 12 );
		drawRectFill( lion - 30 + 37, 310 - lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 16, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 37, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( lion - 30 + 8, 310 - lionJumpHeight + 27, 41, 18 );
		drawRectFill( lion - 30 + 18, 310 - lionJumpHeight + 45, 5, 15 );
		drawRectFill( lion - 30 + 39, 310 - lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 18, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 39, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawCircleFill(lion - 30 + 49, 310 - lionJumpHeight + 25, 9);
		setColor(my_black);
		drawElipseFill(lion - 30 + 53, 310 - lionJumpHeight + 22, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine(lion - 30 + 2, 310 - lionJumpHeight + 41, lion - 30 + 9, 310 - lionJumpHeight + 38);
	}
	else if(walk_state < 30){
		setColor(my_yellow);
		drawRectFill( lion - 30 + 10, 310 - lionJumpHeight + 45, 5, 12 );
		drawRectFill( lion - 30 + 32, 310 - lionJumpHeight + 45, 5, 12 );
		drawRectFill( lion - 30 + 8, 310 - lionJumpHeight + 27, 41, 18 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 10, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 32, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow_dark);
		drawRectFill( lion - 30 + 19, 310 - lionJumpHeight + 45, 5, 15 );
		drawRectFill( lion - 30 + 41, 310 - lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 19, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 41, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawCircleFill(lion - 30 + 49, 310 - lionJumpHeight + 25, 9);
		setColor(my_black);
		drawElipseFill(lion - 30 + 53, 310 - lionJumpHeight + 22, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine(lion - 30 + 2, 310 - lionJumpHeight + 35, lion - 30 + 9, 310 - lionJumpHeight + 38);
	}
	else{
		setColor(my_yellow_dark);
		drawRectFill( lion - 30 + 18, 310 - lionJumpHeight + 45, 5, 12 );
		drawRectFill( lion - 30 + 37, 310 - lionJumpHeight + 45, 5, 12 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 15, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 34, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawRectFill( lion - 30 + 8, 310 - lionJumpHeight + 27, 41, 18 );
		drawRectFill( lion - 30 + 15, 310 - lionJumpHeight + 45, 5, 15 );
		drawRectFill( lion - 30 + 34, 310 - lionJumpHeight + 45, 5, 15 );
		setColor(my_brown);
		drawRectFill( lion - 30 + 18, 310 - lionJumpHeight + 57, 8, 3 );
		drawRectFill( lion - 30 + 39, 310 - lionJumpHeight + 57, 8, 3 );
		setColor(my_yellow);
		drawCircleFill(lion - 30 + 49, 310 - lionJumpHeight + 25, 9);
		setColor(my_black);
		drawElipseFill(lion - 30 + 53, 310 - lionJumpHeight + 22, 2, 5);
		setColor(my_brown);
		setLineWidth(3);
		drawLine(lion - 30 + 2, 310 - lionJumpHeight + 35, lion - 30 + 9, 310 - lionJumpHeight + 38);
	}
	setColor(my_black);
	drawRectFill( lion - 30 + 45, 310 - lionJumpHeight, 10, 16 );
	drawRectFill( lion - 30 + 40, 310 - lionJumpHeight + 14, 19, 3);
	setColor(my_red);
	drawRectFill( lion - 30 + 44, 310 - lionJumpHeight + 11, 11, 2);
	//drawRectFill( lion - 30, 310 - lionJumpHeight, 60, 60 );
}

void Game::drawLife()
{
	for( int i = 0; i < life; ++i )
	{
		float x = SCREEN_WIDTH - ( 30 + i * 40.f ) - 15.f;
		float y = 30;
		setColor( RED );
		setLineWidth(1);
		drawHeart(x + camera, y, true);
		//drawCircleFill( x + camera, y, 15 );
	}
}

void Game::checkJars()
{
	for( auto jarIter = jars.begin(); jarIter != jars.end(); ++jarIter ){
		float& jar = *jarIter;
		if( -45 <  lion - jar && lion - jar < 45 )
		{
			if( lionJumpHeight <= JAR_HEIGHT )
			{
				//충돌함.
				if( crash == 0 )
				{
					crash = LION_FLASH_TIME;
					life--;
				}
			}
		}
	}
}

void Game::checkRings()
{
	float checkRing = -200;
	for(auto ringIter = rings.begin(); ringIter != rings.end(); ++ringIter ){
		float& ring = *ringIter;
		if( lion - 30 <= ring && ring <= lion + 30 ){
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
