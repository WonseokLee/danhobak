#pragma once
#include "GameObject.h"
#include "ObjLoader.h"

class MLion : public GameObject
{
public:
	MLion( GameObject* parent, float z);
	virtual void draw();
	
	CObjLoader myLoader;
};