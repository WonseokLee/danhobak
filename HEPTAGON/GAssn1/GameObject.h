#pragma once
#include <vector>
#include "Vector2.h"

class GameObject
{
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	virtual void update(){}
	virtual void draw(){}

protected:
	Vector2 position;
	double rotation;
	Vector2 scale;

public:
	GameObject( GameObject* parent = NULL, Vector2& pos = Vector2(), double rot = 0, Vector2& sc = Vector2( 1, 1 ) );
	virtual ~GameObject();

	void updateAll();
	void drawAll();

	void addChild( GameObject* child );
	GameObject* popChild( GameObject* child );
	void deleteChild( GameObject* child );
	void deleteChildren();

	GameObject* getParent();
	GameObject* getAncestor();
	std::vector<GameObject*>* getChildren();

	Vector2& pos();
	Vector2 absPos();
	double& rot();
	double absRot();
	Vector2& sc();
	Vector2 absSc();
};
