
#include "Board.h"

Board::Board()
{
	dimples.assign(200, nullptr);
}


Board::~Board()
{
}

void Board::addBall(Ball* b){
	balls.push_back(b);
}
void Board::addDimple(Dimple* d){
	
	dimples.at(d->getIndex()) = d;
	
}

Dimple* Board::getDimpleAtIndex(int index){
	// 200 being the amount of the dimples
	if (index < (int)(dimples.size())){
		return dimples[index];
	}
	return nullptr;
}

void Board::populateBoard(char* json, int players){
	

	Utility::JSONParser* parser = new Utility::JSONParser();
	Utility::JSONObject* boardInfo = parser->DecodeJSONFromFile(json);	
	std::vector<Utility::JSONValue>* info = boardInfo->getValue<std::vector<Utility::JSONValue>*>("Dimples");
	
	Utility::JSONObject* tempObject;
	Dimple* tempDimple;
	Ball* tempBall;
	Transform* tempTransform;

	//int index;
	char* start;
	char* end;
	std::vector<Utility::JSONValue>* positions;

	std::vector<Utility::JSONValue>* neighbors;

	
	Vector3* pos;


	
	for (unsigned int i = 0; i < info->size(); i++){

	
		tempObject = info->at(i).object;

		int index = tempObject->getValue<int>("Index");

		start = tempObject->getValue<char*>("StartTeam"); 
		end = tempObject->getValue<char*>("EndTeam");

		positions = tempObject->getValue<std::vector<Utility::JSONValue>*>("Coords");
		pos = new Vector3(positions->at(0), positions->at(1), positions->at(2));
		
		neighbors = tempObject->getValue<std::vector<Utility::JSONValue>*>("AdjacentIndicies");
	
		if (start == nullptr){
			start = "None";
		}
		tempDimple = new Dimple(getColorFromString(start), pos, this, index);
		tempDimple->setIndeces(neighbors);
		
		// DImple population up, Ball population down
		if (end != nullptr){
			tempBall = new Ball(CYAN, tempDimple, this, pos);
		}
		//GameObject* ballObject = new GameObject();
		//ballObject->addComponent(ballRenderer);
		//ballObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 0.0f));


		
	}


}
Utility::JSONValue value;
std::vector<Utility::JSONValue>* indeces;

// populates neighbors
void Board::populateNeighbors(){
	// loop through neighbors
	for (Dimple* d : dimples){
		indeces = d->getIndeces();
		//loop though indeces of neighbors
		for ( int i = 0; i < indeces->size(); i++){
			// get json value of indexes
			value = indeces->at(i);
			// is this value is a thing
			if (value.boolean){
				// get neighbor at index, and then cast direction 
				d->addNeighboringDimple(getDimpleAtIndex(value.integer), (Direction)i);
			}
		}
	}
}

Color Board::getColorFromString(char* string){
	if (strcmp(string,"Lime")==0){
		return LIME;
	}
	else if (strcmp(string,"Green") == 0){
		return GREEN;
	}
	else if (strcmp(string, "Black") == 0){
		return BLACK;
	}
	else if (strcmp(string, "White") == 0){
		return WHITE;
	}
	else if (strcmp(string, "Violet") == 0){
		return VIOLET;
	}
	else if (strcmp(string, "Purple") == 0){
		return PURPLE;
	}
	else if (strcmp(string, "Yellow") == 0){
		return YELLOW;
	}
	else if (strcmp(string, "Cyan") == 0){
		return CYAN;
	}
	else if (strcmp(string, "Red") == 0){
		return RED;
	}
	else if (strcmp(string, "Blue") == 0){
		return BLUE;
	}
	return GRAY;
}

std::list<Ball*> Board::getBalls(){
	return balls;
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