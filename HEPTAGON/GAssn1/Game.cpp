#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "frame.h"
#include "hsi.h"
#include "Obstacle.h"
#include "CenterBlock.h"

//#define DIFFICULTY_MAX

Game::Game()
{
	setWindowTitle( "0x06" );

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
	nowSpeed = 0;
	smoothSpeed = 0;
	viewRot = 0;
	viewRotSpeed = 0;
	centerBase = 0;
	base = CENTER_SIZE;
	speedMultiplier = 1.f;
	highScore = 0;
	difficulty = 0;

	position = Vector2( SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );

	marker = new Marker(this);
	addChild( marker );
	newGame();
}
void Game::newGame()
{
	z = 0;
	speedTick = 0;
	viewRotTick = 0;
	centerBaseTick = 0;

	popChild( marker );

	obstacles.clear();
	deleteChildren();

	float z = BLOCK_START;
	for( int i = 0; i < 200; i++ )
	{
		makeObstacles( z );
	}
	for( int k = 0; k < 6; k++ )
		addChild( new CenterBlock( this, k ) );
	addChild( marker );
	
	textScore = new Text( this, Vector2( SCREEN_WIDTH/2 - 160, SCREEN_HEIGHT/2 - 20 ) );
	textHigh =  new Text( this, Vector2( -SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT/2 - 20 ) );
	addChild( textScore );
	addChild( textHigh );

	begin = GetTickCount();
}
void Game::makeObstacles( float& z )
{
	int k, r, d;
	
	switch( rand() % 10 )
	{
	case 0:
		z += 40;
		k = rand() % 2;
		r = rand() % 4 + 3;
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
		r = rand() % 4 + 5;
		for( int i = 0; i < r; i++ )
		{
			z += 40;
			newObstacle( 0+k, z );
			newObstacle( 3+k, z );
			k = (k + d + 6) % 6;
			z += 40;
		}
		z += 40;
		break;
	case 2:
		z += 40;
		k = rand() % 6;
		r = rand() % 3 + 2;
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
	case 3:
		z += 60;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 6;
		r = rand() % 3 + 6;
		for( int i = 0; i < r; i++ )
		{
			z += 30;
			newObstacle( 0+k, z );
			newObstacle( 1+k, z );
			newObstacle( 2+k, z );
			k = (k + d + 6) % 6;
			z += 30;
		}
		z += 20;
		break;
	case 4:
		z += 60;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 3;
		r = rand() % 3 + 3;
		for( int i = 0; i < r; i++ )
		{
			z += 60;
			newObstacle( 0+k, z );
			newObstacle( 1+k, z );
			newObstacle( 3+k, z );
			newObstacle( 4+k, z );
			k = (k + d + 6) % 6;
			z += 60;
		}
		break;
	case 5:
		z += 80;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 6;
		r = rand() % 3 + 6;
		for( int i = 0; i < r; i++ )
		{
			z += 40;
			newObstacle( 0+k, z );
			newObstacle( 1+k, z );
			newObstacle( 2+k, z );
			newObstacle( 3+k, z );
			k = (k + d + 6) % 6;
			z += 40;
		}
		z += 60;
		break;
	case 6:
		z += 60;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 3;
		r = rand() % 10 + 5;
		for( int i = 0; i < r; i++ )
		{
			z += 20;
			newObstacle( 0+k, z, 40 );
			newObstacle( 3+k, z, 40 );
			k = (k + d + 6) % 6;
			z += 20;
		}
		z += 60;
		break;
	case 7:
		z += 60;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 6;
		r = rand() % 6 + 6;
		for( int i = 0; i < r; i++ )
		{
			z += 20;
			newObstacle( 0+k, z, 40 );
			newObstacle( 1+k, z, 40 );
			newObstacle( 2+k, z, 40 );
			k = (k + d + 6) % 6;
			z += 20;
		}
		z += 60;
		break;
	case 8:
		z += 80;
		d = (rand() % 2) * 2 - 1;
		k = rand() % 6;
		r = rand() % 6 + 6;
		for( int i = 0; i < r; i++ )
		{
			z += 20;
			newObstacle( 0+k, z, 40 );
			newObstacle( 1+k, z, 40);
			newObstacle( 2+k, z, 40 );
			newObstacle( 3+k, z, 40 );
			k = (k + d + 6) % 6;
			z += 20;
		}
		z += 60;
	case 9:
		z += 40;
		d = rand() % 2;
		k = rand() % 6;
		r = rand() % 3 + 2;
		for( int i = 0; i < r; i++ )
		{
			float thick = BLOCK_SCALE;
			if( i != r-1 )
				thick = 200.f;

			z += 100;
			newObstacle( 0+k, z, thick );
			if( d ){
				newObstacle( 1+k, z );
			}else{
				newObstacle( 5+k, z );
			}
			newObstacle( 2+k, z );
			newObstacle( 3+k, z );
			newObstacle( 4+k, z );
			d = !d;
			z += 100;
		}
		break;
	}
}
void Game::newObstacle( int lane, float z, float thick )
{
	Obstacle* obstacle = new Obstacle( this, lane, z, thick );
	obstacles.push_back( obstacle );
	addChild( obstacle );
}
Game::~Game()
{
	
}
void Game::update()
{
	setDifficulty();
	setCamera();
	showScore();
	setSpeed();
	checkCollision();
	
	centerBaseTick += 0.3f * difficulty;
	centerBase = ( 1 + sin(float(rand()))) * sin(centerBaseTick) * 5;

	bgHue += 0.1f * difficulty * difficulty * difficulty;
	if( bgHue > 2*PI )
		bgHue -= 2*PI;
}
void Game::setDifficulty()
{
#ifdef DIFFICULTY_MAX
	difficulty = 1.f;
	return;
#endif
	int ms = GetTickCount()-begin;
	if( ms < 6000 )
	{
		difficulty = 0.5f;
		speedMultiplier = 1.f;
	}
	else if( ms < 36000)
	{
		difficulty = (ms-6000) * 0.5f / 30000 + 0.5f;
		speedMultiplier = 1.f;
	}
	else if( ms < 216000)
	{
		difficulty = 1.f;
		speedMultiplier = 1 + (ms-36000) / 180000.f;
	}
	else
	{
		difficulty = 1.f;
		speedMultiplier = 2.f;
	}
}
void Game::setSpeed()
{
	z += 4 * difficulty;

	if( smoothSpeed > nowSpeed + ROTATE_SMOOTH )
		smoothSpeed -= ROTATE_SMOOTH;
	else if( smoothSpeed < nowSpeed - ROTATE_SMOOTH )
		smoothSpeed += ROTATE_SMOOTH;
	else
		smoothSpeed = nowSpeed;
	rotation += smoothSpeed;

	if( --speedTick <= 0 )
	{
		speedTick = 60 / difficulty;
		int rotateDirection = rand()%2 ? 1 : -1;
		nowSpeed = rotateDirection * 6 + sin(float(rand()));
		nowSpeed *= difficulty * difficulty * difficulty * difficulty;
	}
	if( --viewRotTick <= 0 )
	{
		viewRotTick = 60 / difficulty;
		int rotateDirection = rand()%2 ? 1 : -1;
		viewRotSpeed = rotateDirection * 0.04f + sin(float(rand())) * 0.01f;
		viewRotSpeed *= difficulty * difficulty * difficulty;
	}
	viewRot += viewRotSpeed;
}
void Game::setCamera()
{
	float theta = PI + viewRot;
	float phi = 15.f * difficulty * difficulty;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 60, 1, 0, SCREEN_HEIGHT*2 );
	gluLookAt( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_HEIGHT, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0.0f, 1.0f, 0.0f );
	glRotatef( phi, cos(theta), sin(theta), 0 );
}
void Game::showScore()
{
	char a[10], b[10], c[3], d[3];
	DWORD score = GetTickCount()-begin;
	if( score > highScore )
		highScore = score;
	_itoa_s( score/1000, a, 16 );
	_itoa_s( highScore/1000, b, 16 );
	_itoa_s( (score*256/1000%256), c, 16 );
	_itoa_s( (highScore*256/1000%256), d, 16 );
	_strupr_s( (char*)a, 10 );
	_strupr_s( (char*)b, 10 );
	_strupr_s( (char*)c, 3 );
	_strupr_s( (char*)d, 3 );
	textScore->setText( std::string("SCORE: 0x") + (score<16000?"0":"") + a + "." + c + (c[1]=='\0'?"0":"") );
	textHigh->setText( std::string("HIGH: 0x") + (highScore<16000?"0":"")  + b + "." + d + (d[1]=='\0'?"0":"") );
}
void Game::checkCollision()
{
	int lane = marker->getLane();
	for( auto obstacleIter = obstacles.begin(); obstacleIter != obstacles.end(); ++obstacleIter )
	{
		auto obstacle = static_cast<Obstacle*>( *obstacleIter );
		if( obstacle->z < 54/speedMultiplier && obstacle->bluffable )
		{
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
	foreColor2 = HSIToRGB( bgHue, 1.f, 0.35f );
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
