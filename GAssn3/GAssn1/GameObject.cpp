#include "GameObject.h"
#include <GL/freeglut.h>

GameObject::GameObject( GameObject* parent, Vector2& position, double rotation )
	: parent( parent ), position( position ), rotation( rotation )
{
	
}
GameObject::~GameObject()
{
	for each( auto child in children )
	{
		delete child;
	}
}
void GameObject::updateAll()
{
	this->update();
	for( auto objectIter = children.begin(); objectIter != children.end(); ++objectIter )
	{
		GameObject* object = *objectIter;
		object->updateAll();
	}
}
void GameObject::drawAll()
{
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glTranslated( pos().x, pos().y, 0 );
	glRotated( rotation, 0, 0, -1 );
	this->draw();
	for( auto objectIter = children.begin(); objectIter != children.end(); ++objectIter )
	{
		GameObject* object = *objectIter;
		object->drawAll();
	}
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}
void GameObject::addChild( GameObject* child )
{
	children.push_back( child );
}
GameObject* GameObject::popChild( GameObject* child )
{
	for( auto objectIter = children.begin(); objectIter != children.end(); ++objectIter )
	{
		GameObject* object = *objectIter;
		if( object == child )
		{
			children.erase( objectIter );
			return object;
			break;
		}
	}
	return NULL;
}
void GameObject::deleteChild( GameObject* child )
{
	if( popChild( child ) != NULL )
		delete child;
}
void GameObject::deleteChildren()
{
	for( auto objectIter = children.begin(); objectIter != children.end(); ++objectIter )
	{
		GameObject* object = *objectIter;
		delete object;
	}
	children.clear();
}
GameObject* GameObject::getParent()
{
	return parent;
}
GameObject* GameObject::getAncestor()
{
	GameObject* object = this;
	while( object->getParent() != NULL )
		object = object->parent;
	return object;
}
std::vector<GameObject*>* GameObject::getChildren()
{
	return &children;
}
Vector2& GameObject::pos()
{
	return position;
}
Vector2 GameObject::absPos()
{
	Vector2 abs = position;
	if( parent != NULL )
		abs += parent->absPos();
	return abs;
}
double& GameObject::rot()
{
	return rotation;
}
double GameObject::absRot()
{
	double abs = rotation;
	if( parent != NULL )
		abs += parent->absRot();
	return abs;
}