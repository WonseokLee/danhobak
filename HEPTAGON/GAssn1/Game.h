#pragma once
#include <vector>
#include "GameTemplate.h"
#include "Marker.h"
#include "Text.h"

using namespace std;

class Game : public GameTemplate
{
public:
	Game();
	~Game();
	void update();
	void draw();
	void special( int key );
	void specialUp( int key );
	void keyboard( unsigned char key );
	void keyboardUp( unsigned char key );

	void initialize();
	void newGame();
	void checkCollision();
	void newObstacle( int lane, float z, float thick = BLOCK_SCALE );

	bool keyLeft;
	bool keyRight;
	bool keySpace;

	float z;
	float base;
	
	float centerBase;
	float centerBaseTick;
	float speedMultiplier;

	int bgColor;
	int bgColor2;
	int foreColor;
	int foreColor2;
	vector<GameObject*> obstacles;
	
private:
	void setSpeed();
	void setCamera();
	void showScore();
	void setDifficulty();

	float difficulty;
	float bgHue;
	float speedTick;
	float nowSpeed;
	float smoothSpeed;

	float viewRot;
	float viewRotSpeed;
	float viewRotTick;

	Marker* marker;
	Text* textScore;
	Text* textHigh;
	DWORD begin;
	DWORD highScore;

	void makeObstacles( float& z );
};
