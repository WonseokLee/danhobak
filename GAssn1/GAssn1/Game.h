#pragma once
#include "GameTemplate.h"
#include <vector>

using namespace std;

class Game : public GameTemplate
{
public:
	Game();
	~Game();
	void update();
	void special( int key );
	void specialUp( int key );
	void display();

private:
	void makeJars();
	void makeRings();
	void moveRings();
	
	void drawBG();
	void drawJars();
	void drawRings();
	void drawLion();

	void moveLion();
	void jumpLion();
	void moveCamera();
	
	vector<float> jars;
	vector<float> rings;
	float camera;
	float lion;
	float lionJumpSpeed;
	float lionJumpHeight;
	bool keyLeft;
	bool keyRight;
	bool keyUp;
};
