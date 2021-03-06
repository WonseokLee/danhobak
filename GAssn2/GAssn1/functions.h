#pragma once
#include <GL/freeglut.h>
#include "configurations.h"
#include "colors.h"

#define setWindowTitle(x) glutSetWindowTitle(x)

#define drawBegin(x) glBegin(x)
#define drawEnd() glEnd()

#define setLineWidth(x) glLineWidth(x)

#define drawVertex2f(x,y) glVertex2f(x,y)

inline void drawLine( float x1, float y1, float x2, float y2 );

inline void drawRect( float x, float y, float w, float h, bool fill );
#define drawRectFill( x, y, w, h ) drawRect( x, y, w, h, true )
#define drawRectStroke( x, y, w, h ) drawRect( x, y, w, h, false )

inline void drawElipse( float x, float y, float w, float h, bool fill );
#define drawElipseFill( x, y, w, h ) drawElipse( x, y, w, h, true )
#define drawElipseStroke( x, y, w, h ) drawElipse( x, y, w, h, false )

inline void drawCircle( float cx, float cy, float rad, bool fill );
#define drawCircleFill( cx, cy, rad ) drawCircle( cx, cy, rad, true )
#define drawCircleStroke( cx, cy, rad ) drawCircle( cx, cy, rad, false )

inline void drawString( float x, float y, char* textString );

//#define RGB(r, g, b) ((r) << 16 | (g) << 8 | (b) | (0xFF) << 24)
//#define RGBA(r, g, b, a) ((r) << 16 | (g) << 8 | (b) | (a) << 24)
#define drawClearColor(x) glClearColor(x);
#define setColor3f(r,g,b) glColor3f(r,g,b)

inline void setColor( COLOR c );
inline void setCamera( float x, float y );

///////////////////////////////////////////////////////////////

inline void drawString( float x, float y, char* textString )
{
	int textLength = (int)strlen(textString);
	for(int count = 0; count < textLength; count++)
	{
		float glX = ( x + 9 * count );
		float glY = y;
		glRasterPos2f(glX, glY);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, textString[count]);
	}
}

inline void drawLine( float x1, float y1, float x2, float y2 )
{
	drawBegin( GL_LINES );
	drawVertex2f( x1, y1 );
	drawVertex2f( x2, y2 );
	drawEnd();
}
inline void drawRect( float x, float y, float w, float h, bool fill )
{
	float left = x;
	float top = y;
	float right = x + w;
	float bottom = y + h;
	GLenum mode = fill ? GL_QUADS : GL_LINE_LOOP;
	drawBegin( mode );
	drawVertex2f( left, top );
	drawVertex2f( left, bottom );
	drawVertex2f( right, bottom );
	drawVertex2f( right, top );
	drawEnd();
}
inline void drawElipse( float x, float y, float w, float h, bool fill )
{
	const int n = 32;
	const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;
	float radX = w / 2;
	float radY = h / 2;
	float centerX = x + radX;
	float centerY = y + radY;
	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;
	drawBegin( mode );
    for(int k = 0; k < n; k++)
    {
        float circleX = centerX + radX * cos(k * PI*2/n);
        float circleY = centerY + radY * sin(k * PI*2/n);
        drawVertex2f( circleX, circleY );
    }
	drawEnd();
}

inline void drawElipseRight( float x, float y, float w, float h, bool fill )
{
	const int n = 32;
	const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;
	float radX = w / 2;
	float radY = h / 2;
	float centerX = x + radX;
	float centerY = y + radY;
	GLenum mode = fill ? GL_POLYGON : GL_LINE_STRIP;
	drawBegin( mode );
	for( int k = 0; k <= n; k++ )
	{
		float circleX = centerX + radX * cos( -PI/2 + k * PI / n );
		float circleY = centerY + radY * sin( -PI/2 + k * PI / n );
		drawVertex2f( circleX, circleY );
	}
	drawEnd( );
}
inline void drawElipseLeft( float x, float y, float w, float h, bool fill )
{
	const int n = 32;
	const float PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899348253421170679f;
	float radX = w / 2;
	float radY = h / 2;
	float centerX = x + radX;
	float centerY = y + radY;
	GLenum mode = fill ? GL_POLYGON : GL_LINE_STRIP;
	drawBegin( mode );
	for( int k = n; k <= 2*n; k++ )
	{
		float circleX = centerX + radX * cos( -PI/2 + k * PI / n );
		float circleY = centerY + radY * sin( -PI/2 + k * PI / n );
		drawVertex2f( circleX, circleY );
	}
	drawEnd( );
}
inline void drawCircle( float cx, float cy, float rad, bool fill )
{
	drawElipse( cx - rad, cy - rad, rad * 2, rad * 2, fill );
}

inline void drawColor( COLOR c ){
	float af = ((c & 0xFF000000) >> 24) / 255.f;
	float rf = ((c & 0x00FF0000) >> 16) / 255.f;
	float gf = ((c & 0x0000FF00) >> 8) / 255.f;
	float bf = ((c & 0x000000FF) >> 0) / 255.f;
	glClearColor( rf, gf, bf, af );
}
inline void setColor( COLOR c )
{
	float af = ((c & 0xFF000000) >> 24) / 255.f;
	float rf = ((c & 0x00FF0000) >> 16) / 255.f;
	float gf = ((c & 0x0000FF00) >> 8) / 255.f;
	float bf = ((c & 0x000000FF) >> 0) / 255.f;
	setColor3f( rf, gf, bf );
}
inline void setCamera( float x, float y )
{
	/*
	float xf = x / SCREEN_WIDTH + 0.5f;
	float yf = y / SCREEN_HEIGHT + 0.5f;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	glOrtho( 0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	gluLookAt( xf, yf, 0.0f, xf, yf, -1.0f, 0.0f, 1.0f, 0.0f );
	*/

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho(  -SCREEN_WIDTH/2.f, SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, -SCREEN_HEIGHT/2.f , 0.0f, 1.0f);
	gluLookAt( SCREEN_WIDTH/2.f + x , SCREEN_HEIGHT/2.f + y, 0.0f, SCREEN_WIDTH/2.f + x , SCREEN_HEIGHT/2.f + y, -1.0f, 0.0f, 1.0f, 0.0f );
}
