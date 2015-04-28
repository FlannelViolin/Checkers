
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
	//std::vector<Utility::JSONObject*>* dimples = boardInfo->getValue<std::vector<Utility::JSONObject*>*>("Dimples");

	std::vector<Utility::JSONValue>* dimples = boardInfo->getValue<std::vector<Utility::JSONValue>*>("Dimples");

	/*for (unsigned int i = 0; i < dimples->size(); i++)
		std::cout << (int)dimples->at(i) << ',';
	std::cout << std::endl;*/

	

}