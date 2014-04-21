#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "frame.h"
#include "hsi.h"
#include "Obstacle.h"
#include "CenterBlock.h"

Game::Game()
{
	setWindowTitle( "HEPTAGON" );

	srand((unsigned)time(NULL));
	
	keyLeft = false;
	keyRight = false;
	keySpace = false;

	initialize();
}
void Game::initialize()
{
	bgHue = 0;
	z = 0;
	speedTick = 0;
	nowSpeed = 0;
	smoothSpeed = 0;
	viewRot = 0;
	viewRotSpeed = 0;
	viewRotTick = 0;
	centerBase = 0;
	centerBaseTick = 0;
	base = 60;
	highScore = 0;

	position = Vector2( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );

	marker = new Marker(this);
	addChild( marker );
	newGame();
}
void Game::newGame()
{
	z = 0;

	popChild( marker );

	obstacles.clear();
	deleteChildren();

	float z = 600.f;
	for( int i = 0; i < 100; i++ )
	{
		makeObstacles( z );
	}
	for( int k = 0; k < 6; k++ )
		addChild( new CenterBlock( this, k ) );
	addChild( marker );
	
	textScore = new Text( this, Vector2( SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT/2 - 20 ) );
	textHigh =  new Text( this, Vector2( -SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT/2 - 20 ) );
	addChild( textScore );
	addChild( textHigh );

	begin = GetTickCount();
}
void Game::makeObstacles( float& z )
{
	int k, r, d;
	
	switch( rand() % 3 )
	{
	case 0:
		z += 40;
		k = rand() % 2;
		r = rand() % 4 + 4;
		for( int i = 0; i < r; i++ )
		{
			z += 60;
			newObstacle( 0+k, z );
			newObstacle( 2+k, z );
			newObstacle( 4+k, z );
			k = (k + 1) % 6;
			z += 60;
		}
		break;
	case 1:
		z += 40;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 3;
		r = rand() % 4 + 4;
		for( int i = 0; i < r; i++ )
		{
			z += 40;
			newObstacle( 3+k, z );
			newObstacle( 0+k, z );
			k = (k + d +6) % 6;
			z += 40;
		}
		break;
	case 2:
		z += 40;
		k = rand() % 6;
		r = rand() % 4 + 2;
		for( int i = 0; i < r; i++ )
		{
			z += 80;
			for( int lane = 0; lane < 6; lane++ )
			if( k != lane )
				newObstacle( lane, z );
			k = (k + 3) % 6;
			z += 80;
		}
		break;
	}
}
void Game::newObstacle( int lane, float z )
{
	Obstacle* obstacle = new Obstacle( this, lane, z );
	obstacles.push_back( obstacle );
	addChild( obstacle );
}
Game::~Game()
{
	
}
void Game::update()
{
	setCamera();
	showScore();
	checkCollision();

	z += 4;

	bgHue += 0.1f;
	if( bgHue > 2*PI )
		bgHue -= 2*PI;

	if( smoothSpeed > nowSpeed )
		smoothSpeed -= 0.6f;
	if( smoothSpeed < nowSpeed )
		smoothSpeed += 0.6f;
	else
		smoothSpeed = nowSpeed;
	rotation += smoothSpeed;

	if( --speedTick <= 0 )
	{
		speedTick = 60;
		int rotateDirection = rand()%2 ? 1 : -1;
		nowSpeed = rotateDirection * 6 + sin(float(rand()));
	}
	if( --viewRotTick <= 60 )
	{
		viewRotTick = 60;
		viewRotSpeed = sin(float(rand())) * 0.1f;
	}
	viewRot += viewRotSpeed;
	centerBaseTick += 0.3f;
	centerBase = ( 1 + sin(float(rand()))) * sin(centerBaseTick) * 3;
}
void Game::setCamera()
{
	float theta = PI + viewRot;
	float phi = 16.f;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 60, 1, 0, SCREEN_HEIGHT*2 );
	gluLookAt( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_HEIGHT, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0.0f, 1.0f, 0.0f );
	glRotatef( phi, cos(theta), sin(theta), 0 );
}
void Game::showScore()
{
	char a[100], b[100], c[3], d[3];
	DWORD score = GetTickCount()-begin;
	if( score > highScore )
		highScore = score;
	_itoa_s( score/1000, a, 10 );
	_itoa_s( highScore/1000, b, 10 );
	_itoa_s( (score/10%100), c, 10 );
	_itoa_s( (highScore/10%100), d, 10 );
	textScore->setText( std::string("SCORE: ") + a + "." + c );
	textHigh->setText( std::string("HIGH: ") + b + "." + d );
}
void Game::checkCollision()
{
	for( auto obstacleIter = obstacles.begin(); obstacleIter != obstacles.end(); ++obstacleIter )
	{
		auto obstacle = static_cast<Obstacle*>( *obstacleIter );
		if( obstacle->z < 27 && obstacle->bluffable )
		{
			int lane = marker->getLane();
			if( obstacle->lane == lane )
			{
				newGame();
				return;
			}
			else
			{
				obstacle->bluffable = false;
			}
		}
	}
}
void Game::draw()
{
	bgColor = HSIToRGB( bgHue, 1.f, 0.6f );
	bgColor2 = HSIToRGB( bgHue, 1.f, 0.55f );
	foreColor = HSIToRGB( bgHue, 0.3f, 2.f );
	drawColor( bgColor );
	
	setColor( bgColor2 );
	drawBegin( GL_TRIANGLES );
	drawVertex2f( 0, 0 );
	drawVertex2f( -500, -866 );
	drawVertex2f( 500, -866 );
	drawVertex2f( 0, 0 );
	drawVertex2f( -1000, 0 );
	drawVertex2f( -500, 866 );
	drawVertex2f( 0, 0 );
	drawVertex2f( 1000, 0 );
	drawVertex2f( 500, 866 );
	drawEnd();
}
void Game::special( int key )
{
	if ( key == GLUT_KEY_LEFT )
		keyLeft = true;
	if ( key == GLUT_KEY_RIGHT )
		keyRight = true;
}
void Game::specialUp( int key )
{
	if ( key == GLUT_KEY_LEFT )
		keyLeft = false;
	if ( key == GLUT_KEY_RIGHT )
		keyRight = false;
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
