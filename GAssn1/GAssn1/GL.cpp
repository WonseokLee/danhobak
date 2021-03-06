#include "GL.h"
#include <GL/freeglut.h>
#include "configurations.h"
#include "Game.h"

GL* GL::gl = nullptr;

GL::GL( int argc, char* args[ ] ) : game( nullptr )
{
	//Initialize FreeGLUT
	glutInit( &argc, args );

	//Create OpenGL 2.1 context
	glutInitContextVersion( 2, 1 );

	//Create Double Buffered Window
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "GLUT" );

	//Do post window/context creation initialization
	if( !initGL( ) )
		return;

	gl = this;

	//Set reshape function
	glutReshapeFunc( reshapeF );

	//Set keyboard function
	//glutKeyboardFunc( keyboardF );
	//glutKeyboardUpFunc( keyboardUpF );

	//Set special function
	glutSpecialFunc( specialF );
	glutSpecialUpFunc( specialUpF );

	//Set rendering function
	glutDisplayFunc( displayF );

	//Set main loop
	glutTimerFunc( 1000 / SCREEN_FPS, mainLoopF, 0 );

	game = new Game();

	//Start GLUT main loop
	glutMainLoop( );
}
GL::~GL()
{
	if( game )
		delete game;
}
bool GL::initGL()
{
	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	
	glOrtho( -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	gluLookAt( 0.5f, 0.5f, 0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f );

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glShadeModel( GL_FLAT );

	//Check for error
	GLenum error = glGetError( );
	if( error != GL_NO_ERROR )
		return false;

	return true;
}
void GL::mainLoop( int val )
{
	//Frame logic
	update( );
	display( );

	//Run frame one more time
	glutTimerFunc( 1000 / SCREEN_FPS, mainLoopF, val );
}
void GL::update()
{
	game->update();
}
void GL::display()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_LINE_SMOOTH);
	
	game->display();

	glDisable (GL_BLEND);

	//Update screen
	glutSwapBuffers( );
}
void GL::keyboard( unsigned char key, int x, int y )
{
	game->keyboard( key );
}
void GL::keyboardUp( unsigned char key, int x, int y )
{
	game->keyboardUp( key );
}
void GL::special( int key, int x, int y )
{
	game->special( key );
}
void GL::specialUp( int key, int x, int y )
{
	game->specialUp( key );
}
void GL::reshape( int w, int h )
{
	glViewport(0, 0, w, h);
}
