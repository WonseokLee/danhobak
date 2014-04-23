#pragma once
#include "GameObject.h"
#include "Obstacle.h"

class Game;
class Marker : public GameObject
{
public:
	Marker( GameObject* parent );
	void update();
	void draw();
	int getLane();

protected:
	Game* getParent();

private:
	void checkWall();
	void checkObstacle( Obstacle* obstacle, int lane );

	bool leftKey;
	double lastRot;
};