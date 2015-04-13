#ifndef BALL_H
#define BALL_H
/*#include "Component.h"
#include "Transform.h"*/
#include "Dimple.h"
#include "Util.h"
#include "Board.h"
/*using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;*/

class Board;
class Dimple;
class Ball
{

private:
	//Material* color;
	Dimple* currentDimple;
	SelectionState state;
	// board will have a list of ALL BALLS ON THE BAORD apaprently and which ball is currently selected
	Board* board;

public:
	Ball();
	~Ball();

	//Ball(Material* c, Dimple* startDimple, Board* b);

};

#endif BALL_H