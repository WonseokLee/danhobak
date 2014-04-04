#include "GameObject.h"

GameObject::GameObject( GameObject* parent, Vector2& pos )
	: parent( parent ), pos( pos )
{

}
GameObject::~GameObject()
{

}
void GameObject::drawAll()
{
	this->draw();
	for( auto objectIter = children.begin(); objectIter != children.end(); ++objectIter )
	{
		GameObject* object = *objectIter;
		object->drawAll();
	}
}
