#include "GL.h"
#include <GL/freeglut.h>
#include "configurations.h"

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
}
void GL::start( GameTemplate& game )
{
	this->game = &game;
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
	
	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	//Initialize clear color
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST); 
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
	//Run frame one more time
	glutTimerFunc( 1000 / SCREEN_FPS, mainLoopF, val );

	//Frame logic
	update( );
	display( );
}
void GL::update()
{
	game->updateAll();
}
void GL::display()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_LINE_SMOOTH);
	
	game->drawAll();

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
