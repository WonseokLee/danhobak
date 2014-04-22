#include "CenterBlock.h"
#include "Game.h"
CenterBlock::CenterBlock( GameObject* parent, int lane )
	: Block( parent, lane, 0 )
{
}
void CenterBlock::update()
{
	scale = Vector2( z + getParent()->base + getParent()->centerBase );
}
void CenterBlock::draw()
{
	float thick1 = 1 + 36/scale.size()*sqrt(2.f);
	float thick2 = 1 + 27/scale.size()*sqrt(2.f);

	setColor( getParent()->foreColor );
	drawBegin( GL_POLYGON );
	drawVertex2f( -thick2* 0.57735f, -thick2 );
	drawVertex2f( +thick2* 0.57735f, -thick2 );
	drawVertex2f( +thick1* 0.57735f, -thick1 );
	drawVertex2f( -thick1* 0.57735f, -thick1 );
	drawEnd();

	setColor( getParent()->foreColor2 );
	drawBegin( GL_TRIANGLES );
	drawVertex2f( 0, 0 );
	drawVertex2f( +thick2*0.57735f, -thick2 );
	drawVertex2f( -thick2*0.57735f, -thick2 );
	drawEnd();
}