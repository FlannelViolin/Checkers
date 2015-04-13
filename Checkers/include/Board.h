#ifndef BOARD_H
#define BOARD_H
#include "Component.h"
#include "Transform.h"
#include "Dimple.h"
#include "Ball.h"
#include <list>

using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

class Ball;
class Dimple;
class Board
{

private:
	std::list<Ball*> balls;
	std::list<Dimple*> dimples;
	Ball* selectedBall;
public:
	Board();
	~Board();

	// add Ball to baord
	void addBall(Ball* b);
	void addDimple(Dimple* d);
	// get/selected selected 
	void setSelected(Ball b);
	void getSelected(Ball b);




};

#endif BOARD_H