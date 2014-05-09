#include "GL.h"
#include "Game.h"

int main( int argc, char* args[] )
{
	GL gl( argc, args );
	gl.start( Game() );
	return 0;
}
