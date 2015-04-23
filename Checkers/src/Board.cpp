
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

void Board::populateBoard(char* json){
	Utility::JSONParser* parser = new Utility::JSONParser();


	Utility::JSONObject* boardInfo = parser->DecodeJSONFromFile(json);

	
}