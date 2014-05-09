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
	
	keyUp = false;
	keyDown = false;
	keySpace = false;
	keyF1 = false;
	keyF2 = false;
	keyF3 = false;
	keyF4 = false;
	keyF5 = false;
	keyF6 = false;
	keyF7 = false;
	view_state = VIEW_FIRST;

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
void Game::keyboard( unsigned char key )
{
	if ( key == 32 )
		keySpace = true;
}
void Game::keyboardUp( unsigned char key )
{
	if ( key == 32 )
		keySpace = false;
}
void Game::special( int key )
{
	if ( key == GLUT_KEY_UP )
		keyUp = true;
	if ( key == GLUT_KEY_DOWN )
		keyDown = true;
	if ( key == GLUT_KEY_F1 )
		keyF1 = true;
	if ( key == GLUT_KEY_F2 )
		keyF2 = true;
	if ( key == GLUT_KEY_F3 )
		keyF3 = true;
	if ( key == GLUT_KEY_F4 )
		keyF4 = true;
	if ( key == GLUT_KEY_F5 )
		keyF5 = true;
	if ( key == GLUT_KEY_F6 )
		keyF6 = true;
	if ( key == GLUT_KEY_F7 )
		keyF7 = true;
}
void Game::specialUp( int key )
{
	if ( key == GLUT_KEY_UP )
		keyUp = false;
	if ( key == GLUT_KEY_DOWN )
		keyDown = false;
	if ( key == GLUT_KEY_F1 )
		keyF1 = false;
	if ( key == GLUT_KEY_F2 )
		keyF2 = false;
	if ( key == GLUT_KEY_F3 )
		keyF3 = false;
	if ( key == GLUT_KEY_F4 )
		keyF4 = false;
	if ( key == GLUT_KEY_F5 )
		keyF5 = false;
	if ( key == GLUT_KEY_F6 )
		keyF6 = false;
	if ( key == GLUT_KEY_F7 )
		keyF7 = false;
}
void Game::resetMap()
{
	deleteChildren();
	
	addChild( new BG3D( this ) );
	
	ringLayer = makeRings();
	addChild( ringLayer );
	rockLayer = makeRocks();
	addChild( rockLayer );
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
		if( lion->pos().z > FINISH+50 &&
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
	camera = lion->pos().z;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	
	//glOrtho( -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, -SCREEN_HEIGHT/2.f , 0.0f, SCREEN_HEIGHT);
	
	if( keyF2 )
		view_state = VIEW_FIRST;
	if( keyF3 ) 
		view_state = VIEW_THIRD;
	if( keyF4 )
		view_state = VIEW_TOP_MAP;
	if( keyF5 )
		view_state = VIEW_RIGHT_MAP;
	if( keyF6 )
		view_state = VIEW_TOP;
	if( keyF7 )
		view_state = VIEW_RIGHT;

	switch(view_state){
	case VIEW_FIRST:
	default:
			gluPerspective( 90, -1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0, 2000 );
		//glOrtho( -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, -SCREEN_HEIGHT/2.f , 0.0f, SCREEN_HEIGHT);

		//데헷
		gluLookAt( 0.0f, 0.0f, 0.0f, 0.0f , 0.0f, 1.0f, 0.0f, 1.0f, 0.0f );
		glTranslated( 0, -lion->lionJumpHeight-45, -camera-45 );
		break;
	case VIEW_THIRD:
		gluPerspective( 90, -1.0f * SCREEN_WIDTH / SCREEN_HEIGHT, 0, 2000 );
		gluLookAt( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f );
		glTranslated(0, -150, -camera + 200);
		break;
	case VIEW_TOP_MAP:
		glOrtho( 4000, -4000, -3000, 3000 , 0.0f, 2000 );
		gluLookAt( 0.0f, 0.0f, 0.0f, 0.0f , -1.0f, 0.0f, 0.0f, 0.0f, 1.0f );
		glTranslated( 0, -1000, -2900 );
		break;
	case VIEW_RIGHT_MAP:glOrtho( 3200, -3200, -2400, 2400 , 0.0f, 2000 );
		gluLookAt( 0.0f, 0.0f, 0.0f, -1.0f , 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
		glTranslated( 0, -1000, -2500 );
		break;
	case VIEW_TOP:
		//glOrtho(-SCREEN_WIDTH/2, SCREEN_WIDTH/2, 0, 5500, 0, 400);
		glOrtho( SCREEN_WIDTH, -SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT , 0.0f, 2000 );
		gluLookAt( 0.0f, 0.0f, 0.0f, 0.0f , -1.0f, 0.0f, 0.0f, 0.0f, 1.0f );
		glTranslated( 0, -1000, -camera-200 );
		//glTranslated(0, -200, 5000);
		break;
	case VIEW_RIGHT:
		glOrtho( SCREEN_WIDTH, -SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT , 0.0f, 2000 );
		gluLookAt( 0.0f, 0.0f, 0.0f, -1.0f , 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
		glTranslated( -500, -200, -camera-500 );
		break;
	}
}
