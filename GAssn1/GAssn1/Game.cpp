#include "Game.h"
#include "frame.h"

#include <stdlib.h>
#include <time.h>

Game::Game()
{
	srand((unsigned)time(NULL));
	makeJars();
	makeRings();

	camera = CAMERA_DEFAULT;
	lion = LION_DEFAULT;
	lionJumpSpeed = 0;
	lionJumpHeight = 0;
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
}
void Game::moveLion()
{
	if( keyLeft && !keyRight )
		lion -= LION_SPEED;
	if( !keyLeft && keyRight )
		lion += LION_SPEED;
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
	setCamera( camera, 0 );
}
void Game::makeJars()
{
	/*
	int jarNum = (JAR_NUM_MAX - JAR_NUM_MIN + 1) * rand() / ( RAND_MAX+1) + JAR_NUM_MIN;
	for( float i = 0; i < jarNum; ++i )
		jars.push_back( float((JAR_GEN_MAX - JAR_GEN_MIN + 1) * rand() / ( RAND_MAX+1) + JAR_GEN_MIN) );
	*/
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
	/*
	int ringNum = (RING_NUM_MAX - RING_NUM_MIN + 1) * rand() / ( RAND_MAX+1) + RING_NUM_MIN;
	for( float i = 0; i < ringNum; ++i )
		rings.push_back( float((RING_GEN_MAX - RING_GEN_MIN + 1) * rand() / ( RAND_MAX+1) + RING_GEN_MIN) );
	*/
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
	setColor( BROWN );
	drawRectFill( lion - 30, 310 - lionJumpHeight, 60, 60 );
}
