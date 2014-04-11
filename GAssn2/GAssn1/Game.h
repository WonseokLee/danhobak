#pragma once
#include <vector>
#include "GameTemplate.h"

using namespace std;

class Game : public GameTemplate
{
public:
	Game();
	~Game();
	void update();
	void special( int key );
	void specialUp( int key );
	void draw();

private:
	void resetMap();

	void makeJars();
	/// ringLayerRight ∏¶ ∏Æ≈œ
	GameObject* makeRings();
	
	void drawBG();
	void drawLion();

	void drawLife();

	void checkJars();
	void checkRings();

	void moveState();
	void moveLion();
	void jumpLion();
	void moveCamera();
	
	float camera;
	float lion;
	float lionJumpSpeed;
	float lionJumpHeight;
	int game_state;
	int life;
	int crash;
	int walk_state;
	bool keyLeft;
	bool keyRight;
	bool keyUp;
	bool keyF1;
};
