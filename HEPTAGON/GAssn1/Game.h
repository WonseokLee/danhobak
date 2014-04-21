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
	void newObstacle( int lane, float z );

	bool keyLeft;
	bool keyRight;
	bool keySpace;

	float z;
	float base;
	
	float centerBase;
	float centerBaseTick;

	int bgColor;
	int bgColor2;
	int foreColor;
	
private:
	void setCamera();
	void showScore();

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
	vector<GameObject*> obstacles;
	DWORD begin;
	DWORD highScore;

	void makeObstacles( float& z );
};
