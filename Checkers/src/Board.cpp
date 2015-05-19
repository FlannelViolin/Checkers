
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

	//int index;
	char* start;
	char* end;
	std::vector<Utility::JSONValue>* positions;

	std::vector<Utility::JSONValue>* neighbors;

	
	Vector3* pos;

	balls.clear();
	
	for (unsigned int i = 0; i < info->size(); i++){

		std::cout << i << std::endl;
		tempObject = info->at(i).object;

		int index = tempObject->getValue<int>("Index");

		start = tempObject->getValue<char*>("StartTeam"); 
		end = tempObject->getValue<char*>("EndTeam");

		positions = tempObject->getValue<std::vector<Utility::JSONValue>*>("Coords");
		pos = new Vector3(positions->at(0), positions->at(1), positions->at(2));
		
		neighbors = tempObject->getValue<std::vector<Utility::JSONValue>*>("AdjacentIndicies");
		
		if (end == nullptr){ end = "None"; }
		if (start == nullptr){start = "None";}

		Color cs = getColorFromString(start);
		Color ce = getColorFromString(end);
		tempDimple = new Dimple(ce, pos, this, index);
		tempDimple->setIndices(neighbors);
		
		// DImple population up, Ball population down
		if (strcmp(end, "None") != 0){
			if (int(cs) < players){
				tempDimple->toggleOccupied();
				tempBall = new Ball(cs, tempDimple, this, pos);
			}
		}
		//GameObject* ballObject = new GameObject();
		//ballObject->addComponent(ballRenderer);
		//ballObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 0.0f));


		
	}


}
Utility::JSONValue value;
std::vector<Utility::JSONValue>* indices;

// populates neighbors
void Board::populateNeighbors(){
	// loop through neighbors
	for (Dimple* d : dimples){
		indices = d->getIndices();
		//loop though indices of neighbors
		for (unsigned int i = 0; i < indices->size(); i++){
			// get json value of indexes
			value = indices->at(i);
			// is this value a thing
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


Vector4 Board::getVectorFromColor(Color c){
	
	switch(c){
	case LIME:
		return Vector4(0.0, 1.0, 0.0, 1.0);
		break;
	case GREEN:
		return Vector4(0.0, .35f, .15f, 1.0);
		break;
	case BLACK:
		return Vector4(0.0, 0.0, 0.0, 0.0);
		break;
	case WHITE:
		return Vector4(1.0, 1.0f, 1.0f, 1.0);
		break;
	case VIOLET:
		return Vector4(0.63, .52f, .75f, 1.0);
		break;
	case PURPLE:
		return Vector4(0.20, .00f, .30f, 1.0);
		break;
	case YELLOW:
		return Vector4(1.0, 1.00f, .00f, 1.0);
		break;
	case CYAN:
		return Vector4(0.0, .68f, .93f, 1.0);
		break;
	case RED:
		return Vector4(1.0, .00f, 0.0f, 1.0);
		break;
	case BLUE:
		return Vector4(0.00, .00f, 1.0f, 1.0);
		break;
	case GRAY:
		return Vector4(0.5, 0.5f, 0.5f, 1.0);
		break;
	default:
		return Vector4(0.5, 0.5, 0.5, 0.0);

	}

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