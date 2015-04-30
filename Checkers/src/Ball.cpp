
#include "Ball.h"


Ball::Ball()
{

}

Ball::Ball(Color c, Dimple* startDimple, Board* b, Vector3* pos){
	position = pos;
	color = c;
	currentDimple = startDimple;
	board = b;

	// add ball to board
	board->addBall(this);
	// this shouuld be offset by the dimple object's normal
//	position = currentDimple->getPos();
	state = NONE;
}

Ball::~Ball()
{
}

// change material color based on selection state
void Ball::updateBall(){
	switch (state){
		case HIGHLIGHTED:
		
		break;
		case SELECTED:
		
		break;
		default:
		
		break;
	}
}

bool Ball::moveBall(Direction d){
	Dimple* moveTo = currentDimple->getNeighborAtDirection(d);
	if (moveTo == nullptr){
		// not a valid move
		return false;
	}

	//check for jump, 
	if (moveTo->isOccupied()){
		// checknext dimple
		moveTo = moveTo->getNeighborAtDirection(d);
		if (moveTo == nullptr || moveTo->isOccupied()){
			//if we cant jump return false again
			return false;
		}
	}

	//this dimple is no longer occupied
	currentDimple->toggleOccupied();

	// update current
	currentDimple = moveTo;
	currentDimple->toggleOccupied();

	//#TODO update transform;
	//position = currentDimple->getPos();

	

	return true;
}

Vector3* Ball::getPosition(){
	return position;
}