#ifndef DIMPLE_H
#define DIMPLE_H
#include "Ball.h"
#include "Util.h"
#include "Board.h"
#include <list>

/*using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;*/
struct Neighbor;
class Dimple
{

private:
	Board* board;
	std::list<Neighbor> neighbors;
public:
	Dimple();
	~Dimple();
}; 
struct Neighbor{
	Dimple dimple;
	Direction direction;

};


#endif DIMPLE_H