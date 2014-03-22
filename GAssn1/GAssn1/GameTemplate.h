#pragma once

class GameTemplate
{
public:
	GameTemplate(){};
	virtual ~GameTemplate(){};
	virtual void update() = 0;
	virtual void keyboard( unsigned char key ){};
	virtual void keyboardUp( unsigned char key ){};
	virtual void special( int key ){};
	virtual void specialUp( int key ){};
	virtual void display() = 0;
private:
	
};
