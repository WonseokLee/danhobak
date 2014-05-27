#pragma once
#include "MLion.h"
#include "frame.h"
#include "Game.h"

MLion::MLion( GameObject* parent, float z)
	: GameObject( parent, Vector3(0, 30, z), Vector3(1,1,1), 0, Vector3(0, 1, 0))
{
	myLoader.Load("LION_M.obj", "LION_M.mtl");
}

void MLion::draw()
{
	myLoader.Draw(20);
}