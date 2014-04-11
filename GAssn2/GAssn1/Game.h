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
	void draw();
	
	int game_state;

	bool keyLeft;
	bool keyRight;
	bool keyUp;
	bool keyF1;

private:
	void resetMap();

	void makeLion();
	void makeJars();

	/// ringLayerRight ∏¶ ∏Æ≈œ
	GameObject* makeRings();
	
	void drawBG();
	void drawLife();

	void moveState();
	void moveCamera();
	
	Lion* lion;
	float camera;
};
