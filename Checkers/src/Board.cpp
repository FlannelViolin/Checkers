
#include "Board.h"


Board::Board()
{
}


Board::~Board()
{
}

void Board::addBall(Ball* b){
	balls.push_back(b);
}
void Board::addDimple(Dimple* d){
	dimples.push_back(d);
}