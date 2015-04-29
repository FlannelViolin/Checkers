
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
	dimples[d->getIndex()] = d;
}

Dimple* Board::getDimpleAtIndex(int index){
	// 200 being the amount of the dimples
	if (index < 200){
		return dimples[index];
	}
	return nullptr;
}

void Board::populateBoard(char* json){
	

	Utility::JSONParser* parser = new Utility::JSONParser();
	Utility::JSONObject* boardInfo = parser->DecodeJSONFromFile(json);	
	std::vector<Utility::JSONValue>* info = boardInfo->getValue<std::vector<Utility::JSONValue>*>("Dimples");
	
	Utility::JSONObject* tempObject;
	Dimple tempDimple;
	Transform* tempTransform;

	int index;
	char* start;
	char* end;
	std::vector<Utility::JSONValue>* positions;

	std::vector<Utility::JSONValue>* neighbors;

	
	Vector3* pos;


	
	for (unsigned int i = 0; i < info->size(); i++){
		tempObject = info->at(i).object;

		index = tempObject->getValue<int>("Index");

		/*start = tempObject->getValue<char*>("StartTeam"); 
		end = tempObject->getValue<char*>("EndTeam");*/

		positions = tempObject->getValue<std::vector<Utility::JSONValue>*>("Coords");
		pos = new Vector3(positions->at(0), positions->at(1), positions->at(2));
		
		neighbors = tempObject->getValue<std::vector<Utility::JSONValue>*>("AdjacentIndicies");
		//tempDimple = new Dimple(getColorFromString(start)
		//std::cout << index << ":" << start << std::endl;
	}


}

Color Board::getColorFromString(char* string){
	if (string == "Lime"){
		return LIME;
	}
	else if (string == "Green"){
		return GREEN;
	}
	else if (string == "Black"){
		return BLACK;
	}
	else if (string == "White"){
		return WHITE;
	}
	else if (string == "Violet"){
		return VIOLET;
	}
	else if (string == "Purple"){
		return PURPLE;
	}
	else if (string == "Yellow"){
		return YELLOW;
	}
	else if (string == "Cyan"){
		return CYAN;
	}
	else if (string == "Red"){
		return RED;
	}
	else if (string == "Blue"){
		return BLUE;
	}
}

/*"Index" : 0,
"StartTeam" : "Lime",
"EndTeam" : "Green",
"Coords" : [
	-0.15, 0.89, 0
],
"AdjacentIndicies" : [
	null, null, null, 2, 1, null
]*/