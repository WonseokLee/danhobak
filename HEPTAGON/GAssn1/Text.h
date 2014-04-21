#pragma once
#include "GameObject.h"
#include <string>
#include "frame.h"

class TextDraw : public GameObject
{
public:
	TextDraw( GameObject* parent, Vector2 pos )
		: GameObject( parent, pos )
	{
	}
	void draw()
	{
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity( );
		glMatrixMode(GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity( );
		setColor( WHITE );
		glRasterPos2f(pos().x / SCREEN_WIDTH * 2, pos().y / SCREEN_HEIGHT * 2);
		glutBitmapString( GLUT_BITMAP_HELVETICA_18 , (const unsigned char*) str.c_str());
		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();
	}
	std::string str;
};

class Text : public GameObject
{
public:
	Text( GameObject* parent, Vector2 pos )
		: GameObject( parent )
	{
		textDraw = new TextDraw( this, pos );
		addChild( textDraw );
	}
	void update()
	{
		rotation = - getParent()->rot();
	}
	void setText( std::string& str )
	{
		textDraw->str = str;
	}

	TextDraw* textDraw;
};