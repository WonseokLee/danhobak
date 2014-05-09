#pragma once
#include "GameObject.h"

class HelpText : public GameObject
{
public:
	HelpText( GameObject* parent );
	void update();
	void draw();
};