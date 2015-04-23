#ifndef DIMPLE_H
#define DIMPLE_H

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Transform.hpp"

#include "Ball.h"
#include "Util.h"
#include "Board.h"
#include <list>
using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

struct Neighbor; 
class Dimple : public Component
{

private:
	Board* board;
	Material* color;
	std::list<Neighbor*> neighbors;
	Transform* position;
	bool occupied;


	Direction acrossFromDirection(Direction d);

public:
	Dimple();
	~Dimple();
	Dimple(Material* c, Transform* pos, Board* b);

	Dimple* getNeighborAtDirection(Direction d);

	bool toggleOccupied();
	bool isOccupied();

	Transform* getPos();

	void addNeighboringDimple(Neighbor* n);
	void addNeighboringDimple(Dimple* d, Direction dir);
}; 

struct Neighbor{
	Dimple* dimple;
	Direction direction;

};



#endif DIMPLE_H