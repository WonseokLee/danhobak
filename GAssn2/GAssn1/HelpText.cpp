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
		position = Vector2( 220, 140 );
		break;
	case GAME_CLEAR:
	case GAME_OVER:
		position = Vector2( 220 + camera, 140 );
		break;
	}
}
void HelpText::draw()
{
	
	Game* parent = static_cast<Game*>( getAncestor() );
	switch(parent->stage){
		case 0:
			setColor( BLACK );
			break;
		case 1:
			setColor( WHITE );
			break;
		case 2:
			setColor( WHITE );
			break;
		case 3:
			setColor( YELLOW );
			break;
		}
	switch(parent->game_state){
	case GAME_START:
		switch(parent->stage){
		case 0:
			drawString( 0, 20, "Stage 1. Press 'F1' to start");
			break;
		case 1:
			drawString( 0, 20, "Stage 2. Press 'F1' to start");
			break;
		case 2:
			drawString( 0, 20, "Stage 3. Press 'F1' to start");
			break;
		case 3:
			drawString( 0, 20, "Stage 4. Press 'F1' to start");
			break;
		}
		drawString( 0, 0, "===================");
		drawString( 0, 40, "===================");
		break;
	case GAME_ING:
		drawString( 0, 0, ">>>>>>>>>>>>>>>>>>>>>>");
		drawString( 0, 20, "REACH THE FINISH LINE!" );
		drawString( 0, 40, ">>>>>>>>>>>>>>>>>>>>>>");
		break;
	case GAME_CLEAR:
		drawString( 0, 0, "-------------------");
		switch(parent->stage){
		case 0:
			drawString( 0, 20, "Stage 1 Clear!");
			drawString( 0, 40, "Press 'F1' to go to next stage");
			break;
		case 1:
			drawString( 0, 20, "Stage 2 Clear!");
			drawString( 0, 40, "Press 'F1' to go to next stage");
			break;
		case 2:
			drawString( 0, 20, "Stage 3 Clear!");
			drawString( 0, 40, "Press 'F1' to go to next stage");
			break;
		case 3:
			drawString( 0, 20, "GAME CLEAR!");
			drawString( 0, 40, "Press 'F1' to retry");
			break;
		}
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