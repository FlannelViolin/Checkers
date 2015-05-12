
#include "Dimple.h"

Dimple::Dimple()
{
}


Dimple::~Dimple()
{
}

Dimple::Dimple(Color c, Vector3* pos, Board* b, int i){
	color = c;
	position = pos;
	board = b;
	index = i;
	board->addDimple(this);
	occupied = false;
}

// get neighbor of a dimple at a certain direction
Dimple* Dimple::getNeighborAtDirection(Direction d){
	Dimple* moveTo = nullptr;
	for each (Neighbor* n in neighbors)
	{
		if (n->direction == d){
			moveTo = n->dimple;
			break;
		}
	}
	return moveTo;
}

bool Dimple::isOccupied(){ return occupied; }
bool Dimple::toggleOccupied() { 
	occupied = !occupied;
	return occupied;
}

Vector3* Dimple::getPos(){
	return position;
}

int Dimple::getIndex(){
	return index;
}

// TODO put in  a check to see if there is already a neighbor there
void Dimple::addNeighboringDimple(Neighbor* n){
	//if (getNeighborAtDirection(n->direction) != nullptr){
		neighbors.push_back(n);
	//}
	/* uncomment in times of great need, this adds itself to its own neighbors
	
	Dimple* neighborDimple = n->dimple;
	Direction across = this->acrossFromDirection(n->direction);

	if (neighborDimple->getNeighborAtDirection(across) == nullptr){
		neighborDimple->addNeighboringDimple(this, across);
	}
	
	*/
}

// overload that takes a dimple and direction and creates a neighbor
void Dimple::addNeighboringDimple(Dimple* d, Direction dir){
	Neighbor* n = new Neighbor;
	n->dimple = d;
	n->direction = dir;

	// call the actual method that takes a neighbor
	addNeighboringDimple(n);
}

Direction Dimple::acrossFromDirection(Direction d){
	if (d > 2){
		return Direction(d - 3);
	}
	return Direction(d + 3);
}

void Dimple::setIndeces(std::vector<Utility::JSONValue>* n){
	neighborsIndeces = n;
}

std::vector<Utility::JSONValue>* Dimple::getIndeces(){
	return neighborsIndeces;
}