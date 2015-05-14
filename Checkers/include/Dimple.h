#ifndef DIMPLE_H
#define DIMPLE_H

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Transform.hpp"

#include "Ball.h"
#include "Util.h"
#include "Board.h"
#include <vector>
using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

struct Neighbor; 
class Dimple : public Component
{

private:
	Board* board;
	Color color;
	std::vector<Neighbor*> neighbors;
	Vector3* position;
	bool occupied;
	int index;
	std::vector<Utility::JSONValue>* neighborsIndeces;
	Direction acrossFromDirection(Direction d);
	//Color getColorFromString(char* string);

public:
	Dimple();
	~Dimple();
	Dimple(Color c, Vector3* pos, Board* b, int i);

	Dimple* getNeighborAtDirection(Direction d);

	bool toggleOccupied();
	bool isOccupied();

	std::vector<Neighbor*> getNeighbors();
	int getIndex();

	Vector3* getPos();

	void addNeighboringDimple(Neighbor* n);
	void addNeighboringDimple(Dimple* d, Direction dir);

	void setIndeces(std::vector<Utility::JSONValue>* n);
	std::vector<Utility::JSONValue>* getIndeces();
}; 

struct Neighbor{
	Dimple* dimple;
	Direction direction;
};



#endif DIMPLE_H