#ifndef BOARD_H
#define BOARD_H

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Transform.hpp"
#include "BrickwareUtils\JSONParser.hpp"
#include "Dimple.h"
#include "Ball.h"
#include <list>

using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

class Ball;
class Dimple;
class Board : public Component
{

private:
	std::list<Ball*> balls;
	std::vector<Dimple*> dimples;
	Ball* selectedBall;
	Color getColorFromString(char* string);
public:
	Board();
	~Board();

	// add Ball to baord
	void addBall(Ball* b);
	void addDimple(Dimple* d);
	// get/selected selected 
	void setSelected(Ball b);
	void getSelected(Ball b);

	std::list<Ball*> getBalls();
	Dimple* getDimpleAtIndex(int index);

	void populateBoard(char* jsonFile, int players);

	void populateNeighbors();
};

#endif BOARD_H