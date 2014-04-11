#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "frame.h"
#include "hurdles.h"
#include "Lion.h"

Game::Game()
{
	setWindowTitle( "사자야 우리 저거 사자" );
	srand((unsigned)time(NULL));
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
void Game::draw()
{
	drawBG( );

	switch(game_state){
	case GAME_START:
		setColor( BLACK );
		drawString( 220, 140, "===================");
		drawString( 220, 160, "Press 'F1' to start");
		drawString( 220, 180, "===================");
		break;
	case GAME_ING:
		setColor( BLACK );
		drawString( 220, 140, ">>>>>>>>>>>>>>>>>>>>>>");
		drawString( 220, 160, "REACH THE FINISH LINE!" );
		drawString( 220, 180, ">>>>>>>>>>>>>>>>>>>>>>");
		break;
	case GAME_CLEAR:
		setColor( BLACK );
		drawString( 220.f + camera, 140, "-------------------");
		drawString( 220.f + camera, 160, "GAME CLEAR!");
		drawString( 220.f + camera, 180, "Press 'F1' to retry");
		drawString( 220.f + camera, 200, "-------------------");
		break;
	case GAME_OVER:
		setColor( BLACK );
		drawString( 220 + camera, 140, "-------------------");
		drawString( 220 + camera, 160, "GAME OVER!");
		drawString( 220 + camera, 180, "Press 'F1' to retry");
		drawString( 220 + camera, 200, "-------------------");
		break;
	}
	drawLife();
}

void Game::resetMap()
{
	deleteChildren();

	GameObject* rightRingLayer;

	makeJars();
	rightRingLayer = makeRings();
	makeLion();
	addChild( rightRingLayer );

	camera = CAMERA_DEFAULT;
	game_state = GAME_START;
	keyLeft = false;
	keyRight = false;
	keyUp = false;
	keyF1 = false;
}
void Game::makeLion()
{
	lion = new Lion( this );
	addChild( lion );
}
void Game::makeJars()
{
	GameObject* jarLayer = new GameObject( this, Vector2( 0, 370 ) );
	addChild( jarLayer );

	float currentDistance = JAR_GEN_MIN;
	while(currentDistance < JAR_GEN_MAX){
		currentDistance += (float)((JAR_DIST_MAX - JAR_DIST_MIN + 1) * rand() / (RAND_MAX + 1) + JAR_DIST_MIN);
		jarLayer->addChild( new Jar(jarLayer, currentDistance) );
	}
}
GameObject* Game::makeRings()
{
	GameObject* ringLayerLeft = new GameObject( this, Vector2( 0, 120 ) );
	GameObject* ringLayerRight = new GameObject( this, Vector2( 0, 120 ) );
	addChild( ringLayerLeft );

	float currentDistance = JAR_GEN_MIN;
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
		if( lion->pos.x > FINISH &&
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
	if( lion->pos.x - LION_CAMERA > camera )
	{
		camera = (float)lion->pos.x - LION_CAMERA;
	} else if( lion->pos.x - LION_CAMERA_MIN < camera ){
		camera = (float)lion->pos.x - LION_CAMERA_MIN;
	}

	if( camera < 0 )
		camera = 0;

	if( camera + SCREEN_WIDTH > FINISH + 120 )
		camera = FINISH + 120 - SCREEN_WIDTH;
	setCamera( camera, 0 );
}
void Game::drawBG()
{
		drawColor( TAN );

		setColor( LIME_GREEN );
		drawRectFill( 0, 110, 11000, 370 );

		setColor( YELLOW );
		drawRectFill( (float)FINISH, 370, 10, 110 );

		setLineWidth( 3 );
		setColor( WHITE );
		drawLine( 0, 94, 11000, 94 );
		drawLine( 0, 102, 11000, 102 );
		setColor( BLACK );
		drawLine( 0, 370, 11000, 370 );
		
		setLineWidth( 1 );
		drawLine( 0, 375, 11000, 375 );
}

void Game::drawLife()
{
	for( int i = 0; i < LIFE_DEFAULT; ++i )
	{
		float x = SCREEN_WIDTH - ( 30 + i * 40.f ) - 15.f + camera;
		float y = 30;
		bool fill = i < lion->life;
		setColor( RED );
		setLineWidth(1);
		GLenum mode = fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP;
		drawBegin( mode );
		drawVertex2f(x+15, y+5);
		drawVertex2f(x+10, y+0);
		drawVertex2f(x+5, y+0);
		drawVertex2f(x+0, y+5);
		drawVertex2f(x+0, y+15);
		drawVertex2f(x+15, y+30);
		drawVertex2f(x+30, y+15);
		drawVertex2f(x+30, y+5);
		drawVertex2f(x+25, y+0);
		drawVertex2f(x+20, y+0);
		drawVertex2f(x+15, y+5);
		drawEnd();
	}
}
