#include <iostream>
#include <gl/freeglut.h>
#include <gl/GL.h> 
#include <gl/GLU.h> 
using namespace std; 
 
void renderScene(void) { 
 glClear(GL_COLOR_BUFFER_BIT); 
 glBegin(GL_TRIANGLES); 
 glVertex3f(0.5,0.5,0.0f); 
 glVertex3f(0.5,0.0,0.0); 
 glVertex3f(0.0,0.5,0.0); 
 glEnd(); 
 glFlush(); 
} 
void main(int argc, char **argv) { 
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA); 
 glutInitWindowPosition(100,100); 
 glutInitWindowSize(320,320); 
 glutCreateWindow("Hello OpenGL"); 
 glutDisplayFunc(renderScene); 
 glutMainLoop(); 
}