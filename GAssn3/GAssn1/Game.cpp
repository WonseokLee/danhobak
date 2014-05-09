#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "frame.h"
#include "hurdles.h"
#include "Lion.h"
#include "HelpText.h"
#include "LifeContainer.h"
#include "BG.hpp"

Game::Game()
{
	setWindowTitle( "사자야 우리 저거 사자" );

	srand((unsigned)time(NULL));
	
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyF1 = false;

	resetMap();
}
Game::~Game()
{

}
void Game::update()
{
	moveState();
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
	if ( key == GLUT_KEY_F1 )
		keyF1 = true;
}
void Game::specialUp( int key )
{
	if ( key == GLUT_KEY_LEFT )
		keyLeft = false;
	if ( key == GLUT_KEY_RIGHT )
		keyRight = false;
	if ( key == GLUT_KEY_UP )
		keyUp = false;
	if ( key == GLUT_KEY_F1 )
		keyF1 = false;
}
void Game::resetMap()
{
	deleteChildren();

	addChild( new BG( this ) );
	addChild( new LifeContainer( this ) );
	addChild( new HelpText( this ) );
	rockLayer = makeRocks();
	addChild( rockLayer );
	ringLayer = makeRings();
	lion = new Lion( this );
	addChild( lion );
	addChild( ringLayer );

	camera = CAMERA_DEFAULT;
	game_state = GAME_START;
}
GameObject* Game::makeRocks()
{
	GameObject* rockLayer = new GameObject( this, Vector3( 0, 0, 370 ) );

	float currentDistance = JAR_GEN_MIN;
	while(currentDistance < JAR_GEN_MAX){
		rockLayer->addChild( new Rock(rockLayer, currentDistance) );
		currentDistance += (float)((JAR_DIST_MAX - JAR_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + JAR_DIST_MIN);
	}
	return rockLayer;
}
GameObject* Game::makeRings()
{
	GameObject* ringLayer= new GameObject( this, Vector3( 0, 0, 120 ) );
	//addChild( ringLayer );

	float currentDistance = JAR_GEN_MIN;
	while(currentDistance < RING_GEN_MAX){
		currentDistance += (float)((RING_DIST_MAX - RING_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + RING_DIST_MIN);
		ringLayer->addChild( new Ring(ringLayer, currentDistance) );
		ringLayer->addChild( new Ring(ringLayer, currentDistance) );
	}

	return ringLayer;
}
void Game::moveState()
{
	switch(game_state){
	case GAME_START:
		if( keyF1 )
			game_state = GAME_ING;
		break;
	case GAME_ING:
		if( lion->pos().x > FINISH &&
			lion->lionJumpHeight == 0 &&
			lion->crash == 0 )
			game_state = GAME_CLEAR;
		if( lion->life == 0 )
			game_state = GAME_OVER;
		break;
	case GAME_OVER:
	case GAME_CLEAR:
		if( keyF1 )
		{
			resetMap();
			game_state = GAME_START;
		}
	}
}

void Game::moveCamera()
{
	float x = lion->pos().x;
	if( x - LION_CAMERA > camera )
	{
		camera = x - LION_CAMERA;
	} else if( x - LION_CAMERA_MIN < camera ){
		camera = x - LION_CAMERA_MIN;
	}

	if( camera < 0 )
		camera = 0;

	if( camera + SCREEN_WIDTH > FINISH + 120 )
		camera = FINISH + 120 - SCREEN_WIDTH;
	setCamera( camera, 0 );
}
