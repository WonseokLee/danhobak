#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "frame.h"
#include "hurdles.h"
#include "Lion.h"
#include "HelpText.h"
#include "LifeContainer.h"
#include "BG3D.hpp"

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
	moveCamera();
	moveState();
	
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
	
	addChild( new BG3D( this ) );

	rockLayer = makeRocks();
	addChild( rockLayer );
	ringLayer = makeRings();
	addChild( ringLayer );
	lion = new Lion( this );
	addChild( lion );
	
	addChild( new LifeContainer( this ) );
	addChild( new HelpText( this ) );

	camera = CAMERA_DEFAULT;
	game_state = GAME_START;
}
GameObject* Game::makeRocks()
{
	GameObject* rockLayer = new GameObject( this, Vector3( 0, 0, 0 ) );

	float currentDistance = JAR_GEN_MIN;
	while(currentDistance < JAR_GEN_MAX){
		rockLayer->addChild( new Rock(rockLayer, currentDistance) );
		currentDistance += (float)((JAR_DIST_MAX - JAR_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + JAR_DIST_MIN);
	}
	return rockLayer;
}
GameObject* Game::makeRings()
{
	GameObject* ringLayer= new GameObject( this, Vector3( 0, 0, 0 ) );

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
		if( lion->pos().z > FINISH &&
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
	float z = lion->pos().z;
	if( z - LION_CAMERA > camera )
	{
		camera = z - LION_CAMERA;
	} else if( z - LION_CAMERA_MIN < camera ){
		camera = z - LION_CAMERA_MIN;
	}

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 90, -1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0, 100 );
	//glOrtho( -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, -SCREEN_HEIGHT/2.f , 0.0f, SCREEN_HEIGHT);
	
	//데헷
	gluLookAt( 0.0f, 0.0f, 0.0f, 0.0f , 0.0f, 1.0f, 0.0f, 1.0f, 0.0f );
	glTranslated( 0, -100, -camera );
	
	/*
	if( camera < 0 )
		camera = 0;

	if( camera + SCREEN_WIDTH > FINISH + 120 )
		camera = FINISH + 120 - SCREEN_WIDTH;
	setCamera( camera, 0 );
	*/
}
