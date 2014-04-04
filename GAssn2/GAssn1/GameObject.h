#pragma once
#include <vector>
#include "Vector2.h"

class GameObject
{
private:
	const GameObject* parent;
	const std::vector<GameObject*> children;
	virtual void draw() = 0;

public:
	GameObject( GameObject* parent = nullptr, Vector2& pos = Vector2() );
	virtual ~GameObject();
	void drawAll();

	Vector2 pos;
};
