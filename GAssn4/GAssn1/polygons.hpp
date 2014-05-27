#pragma once
#include "GameObject.h"
#include "frame.h"

class CubeWire : public GameObject
{
public:
	CubeWire( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double drawWidth )
		: GameObject( parent, position, scale ),
		color( color )
	{
	}
	void draw()
	{
		setLineWidth( (float)drawWidth );
		setColor( static_cast<COLOR>(color) );
		glutWireCube( 1 );
	}
	COLOR color;
	double drawWidth;
};

class CubeSolid : public GameObject
{
public:
	CubeSolid( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double size = 1 )
		: GameObject( parent, position, scale ),
		color( color ), size( size )
	{
	}
	void draw()
	{
		setColor( static_cast<COLOR>(color) );
		glutSolidCube( size );
	}
	COLOR color;
	double size;
};

class CubeSolidT : public GameObject
{
public:
	CubeSolidT( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double size = 1 )
		: GameObject( parent, position, scale ),
		color( color ), size( size )
	{
		loadTexture("Rock-Texture-Surface.jpg", &texture);
	}
	void draw()
	{
		setColor( static_cast<COLOR>(color) );
		
		if (texture) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture (GL_TEXTURE_2D, texture);
		}
		
		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
			// Back Face
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
			// Top Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
			// Bottom Face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
			// Right face
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
		glEnd();
	}
	COLOR color;
	double size;
	unsigned int texture;
};

class SphereWire : public GameObject
{
public:
	SphereWire( GameObject* parent, Vector3 position, Vector3 scale, COLOR color, double drawWidth )
		: GameObject( parent, position, scale ),
		color( color )
	{
	}
	void draw()
	{
		setLineWidth( (float)drawWidth );
		setColor( static_cast<COLOR>(color) );
		glutWireSphere( 1, 16, 16 );
	}
	COLOR color;
	double drawWidth;
};

class SphereSolid : public GameObject
{
public:
	SphereSolid( GameObject* parent, Vector3 position, Vector3 scale, COLOR color )
		: GameObject( parent, position, scale ),
		color( color )
	{
	}
	void draw()
	{
		setColor( static_cast<COLOR>(color) );
		glutSolidSphere( 1, 16, 16 );
	}
	COLOR color;
	double drawWidth;
};