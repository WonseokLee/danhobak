#include <glew.h>
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
	glutKeyboardFunc( keyboardF );
	glutKeyboardUpFunc( keyboardUpF );

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

	if (glewInit() != GLEW_OK)
		printf("glew is not supported\n%s\n", glewGetErrorString(glewInit()));
	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	
	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	//Initialize clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); 
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glShadeModel( GL_FLAT );

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_COLOR_MATERIAL);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightd0_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightd0_diffuse);
			glLightfv(GL_LIGHT0, GL_POSITION, lightd0_position);
			glLightfv(GL_LIGHT1, GL_AMBIENT, lightd1_ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lightd1_diffuse);
			glLightfv(GL_LIGHT1, GL_POSITION, lightd1_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	game->drawAll();

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
