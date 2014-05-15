#pragma once
#include <vector>
#include "Vector3.h"

class GameObject
{
private:
	GameObject* parent;
	std::vector<GameObject*> children;
	virtual void update(){}
	virtual void draw(){}

protected:
	Vector3 position;
	double rotation;
	Vector3 rotationV;
	Vector3 scale;

public:
	GameObject( GameObject* parent = NULL, Vector3& pos = Vector3(), Vector3& scale = Vector3( 1, 1, 1 ), double rot = 0, Vector3& rotv = Vector3() );
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

	Vector3& pos();
	Vector3 absPos();
	Vector3& sc();
	double& rot();
	Vector3& rotv();
};
