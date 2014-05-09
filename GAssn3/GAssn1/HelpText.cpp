#include "HelpText.h"
#include "frame.h"
#include "Game.h"

HelpText::HelpText( GameObject* parent ) : GameObject( parent )
{

}
void HelpText::update()
{
	Game* parent = static_cast<Game*>( getAncestor() );
	float camera = parent->camera;
	switch(parent->game_state){
	case GAME_START:
	case GAME_ING:
		position = Vector3( -90, 100, 100 );
		break;
	case GAME_CLEAR:
	case GAME_OVER:
		position = Vector3( -90, 100, camera + 100 );
		break;
	}
}
void HelpText::draw()
{
	setColor( WHITE );
	Game* parent = static_cast<Game*>( getAncestor() );
	switch(parent->game_state){
	case GAME_START:
		drawString( 0, 0, "===================");
		drawString( 0, 20, "Press 'F1' to start");
		drawString( 0, 40, "===================");
		break;
	case GAME_ING:
		drawString( 0, 0, ">>>>>>>>>>>>>>>>>>>>>>");
		drawString( 0, 20, "REACH THE FINISH LINE!" );
		drawString( 0, 40, ">>>>>>>>>>>>>>>>>>>>>>");
		break;
	case GAME_CLEAR:
		drawString( 0, 0, "-------------------");
		drawString( 0, 20, "GAME CLEAR!");
		drawString( 0, 40, "Press 'F1' to retry");
		drawString( 0, 60, "-------------------");
		break;
	case GAME_OVER:
		drawString( 0, 0, "-------------------");
		drawString( 0, 20, "GAME OVER!");
		drawString( 0, 40, "Press 'F1' to retry");
		drawString( 0, 60, "-------------------");
		break;
	}
}