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
	int stage;
	float camera;

	bool keyLeft;
	bool keyRight;
	bool keyUp;
	bool keyF1;
	
	GameObject* ringLayer;
	GameObject* jarLayer;
	Lion* lion;

private:
	void resetMap();
	void stageUpMap();
	GameObject* makeJars();
	GameObject* makeRings();
	
	void moveState();
	void moveCamera();
};
