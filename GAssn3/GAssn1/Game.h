#pragma once
#include <vector>
#include "GameTemplate.h"

using namespace std;

class Lion;

class Game : public GameTemplate
{
public:
	Game();
	~Game();
	void update();
	void special( int key );
	void specialUp( int key );
	
	int game_state;
	int view_state;
	float camera;

	bool keyLeft;
	bool keyRight;
	bool keyUp;
	bool keyF1;

	bool keyF2;
	bool keyF3;
	bool keyF4;
	bool keyF5;
	
	GameObject* ringLayer;
	GameObject* rockLayer;
	Lion* lion;

private:
	void resetMap();
	GameObject* makeRocks();
	GameObject* makeRings();
	
	void moveState();
	void moveCamera();
};
