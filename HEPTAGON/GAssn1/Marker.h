#pragma once
#include "GameObject.h"

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
	bool leftKeyHidden;
};