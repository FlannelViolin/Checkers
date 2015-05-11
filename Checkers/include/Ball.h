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
	Color color;
	Dimple* currentDimple;
	SelectionState state;
	Vector3* position;

	// board will have a list of ALL BALLS ON THE BAORD apaprently and which ball is currently selected
	Board* board;

public:
	Ball();
	~Ball();

	Ball(Color c, Dimple* startDimple, Board* b, Vector3* pos);
	
	virtual void Update();
	virtual void OnMouseOver();
	virtual void OnMouseExit();
	
	bool moveBall(Direction d);
	Vector3* getPosition();
};

#endif BALL_H