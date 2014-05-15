#pragma once
#include "GameTemplate.h"

class GL
{
public:
	GL( int argc, char* args[ ] );
	~GL();
	void start( GameTemplate& game );

	bool initGL();
	void mainLoop( int );
	void update();
	void display();
	void keyboard( unsigned char key, int x, int y );
	void keyboardUp( unsigned char key, int x, int y );
	void special( int key, int x, int y );
	void specialUp( int key, int x, int y );
	void reshape( int x, int y );

	static void displayF() { gl->display(); }
	static void mainLoopF( int val ) { gl->mainLoop( val ); }
	static void keyboardF( unsigned char key, int x, int y ) { gl->keyboard( key, x, y ); }
	static void keyboardUpF( unsigned char key, int x, int y ) { gl->keyboardUp( key, x, y ); }
	static void specialF( int key, int x, int y ) { gl->special( key, x, y ); }
	static void specialUpF( int key, int x, int y ) { gl->specialUp( key, x, y ); }
	static void reshapeF( int x, int y ) { gl->reshape( x, y ); }

private:
	static GL* gl;
	GameTemplate* game;
};
