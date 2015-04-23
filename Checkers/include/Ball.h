#ifndef BALL_H
#define BALL_H
#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Transform.hpp"

#include "Dimple.h"
#include "Util.h"
#include "Board.h"
using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

class Board;
class Dimple;
class Ball : public Component
{

private:
	Material* color;
	Dimple* currentDimple;
	SelectionState state;
	Transform* position;

	// board will have a list of ALL BALLS ON THE BAORD apaprently and which ball is currently selected
	Board* board;

public:
	Ball();
	~Ball();

	Ball(Material* c, Dimple* startDimple, Board* b);
	void updateBall();
	bool moveBall(Direction d);

};

#endif BALL_H