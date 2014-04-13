#pragma once
#include "GameObject.h"
#include "frame.h"

class Heart : public GameObject
{
public:
	Heart( GameObject* parent, Vector2 position );
	void update();
	void draw();
	bool fill;
private:
	void drawHeart( GLenum mode );
	int tick;
};

class LifeContainer : public GameObject
{
public:
	LifeContainer( GameObject* parent );
	void update();

private:
	std::vector<Heart*> hearts;
};
