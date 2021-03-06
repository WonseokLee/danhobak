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
	stage = 0;
	addChild( new BG( this ) );
	addChild( new LifeContainer( this ) );
	addChild( new HelpText( this ) );
	jarLayer = makeJars();
	addChild( jarLayer );
	ringLayer = makeRings();
	lion = new Lion( this );
	addChild( lion );
	addChild( ringLayer );

	camera = CAMERA_DEFAULT;
	game_state = GAME_START;
}

void Game::stageUpMap()
{
	deleteChildren();

	addChild( new BG( this ) );
	addChild( new LifeContainer( this ) );
	addChild( new HelpText( this ) );
	stage++;
	if(stage > 3)
		stage = 0;
	jarLayer = makeJars();
	addChild( jarLayer );
	ringLayer = makeRings();
	lion = new Lion( this );
	addChild( lion );
	addChild( ringLayer );

	camera = CAMERA_DEFAULT;
	game_state = GAME_START;
}

GameObject* Game::makeJars()
{
	GameObject* jarLayer = new GameObject( this, Vector2( 0, 370 ) );

	float currentDistance = JAR_GEN_MIN;
	float JAR_DIST_MIN = 0;
	float JAR_DIST_MAX = 0;
	switch(stage){
	case 0:
		JAR_DIST_MIN = JAR_DIST_MIN_0;
		JAR_DIST_MAX = JAR_DIST_MAX_0;
		break;
	case 1:
		JAR_DIST_MIN = JAR_DIST_MIN_1;
		JAR_DIST_MAX = JAR_DIST_MAX_1;
		break;
	case 2:
		JAR_DIST_MIN = JAR_DIST_MIN_2;
		JAR_DIST_MAX = JAR_DIST_MAX_2;
		break;
	case 3:
		JAR_DIST_MIN = JAR_DIST_MIN_3;
		JAR_DIST_MAX = JAR_DIST_MAX_3;
		break;
	}
	while(currentDistance < JAR_GEN_MAX){
		jarLayer->addChild( new Jar(jarLayer, currentDistance) );
		currentDistance += (float)((JAR_DIST_MAX - JAR_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + JAR_DIST_MIN);
	}
	return jarLayer;
}
GameObject* Game::makeRings()
{
	GameObject* ringLayerLeft = new GameObject( this, Vector2( 0, 120 ) );
	GameObject* ringLayerRight = new GameObject( this, Vector2( 0, 120 ) );
	addChild( ringLayerLeft );

	float currentDistance = JAR_GEN_MIN;
	float RING_DIST_MIN = 0;
	float RING_DIST_MAX = 0;
	switch(stage){
	case 0:
		RING_DIST_MIN = RING_DIST_MIN_0;
		RING_DIST_MAX = RING_DIST_MAX_0;
		break;
	case 1:
		RING_DIST_MIN = RING_DIST_MIN_1;
		RING_DIST_MAX = RING_DIST_MAX_1;
		break;
	case 2:
		RING_DIST_MIN = RING_DIST_MIN_2;
		RING_DIST_MAX = RING_DIST_MAX_2;
		break;
	case 3:
		RING_DIST_MIN = RING_DIST_MIN_3;
		RING_DIST_MAX = RING_DIST_MAX_3;
		break;
	}
	while(currentDistance < RING_GEN_MAX){
		currentDistance += (float)((RING_DIST_MAX - RING_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + RING_DIST_MIN);
		ringLayerLeft->addChild( new RingLeft(ringLayerLeft, currentDistance) );
		ringLayerRight->addChild( new RingRight(ringLayerRight, currentDistance) );
	}

	return ringLayerRight;
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
		if( keyF1 )
		{
			resetMap();
			game_state = GAME_START;
			keyF1 = false;
		}
		break;
	case GAME_CLEAR:
		if( keyF1 )
		{
			stageUpMap();
			game_state = GAME_START;
			keyF1 = false;
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
