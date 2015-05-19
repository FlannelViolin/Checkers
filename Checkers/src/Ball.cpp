#include "Ball.h"

//Statics
Ball* Ball::SelectedBall = nullptr;

Ball::Ball()
{

}

Ball::Ball(Color c, Dimple* startDimple, Board* b, Vector3* pos){
	position = pos;
	color = c;
	currentDimple = startDimple;
	board = b;

	// add ball to board
	board->addBall(this);
	// this shouuld be offset by the dimple object's normal
//	position = currentDimple->getPos();
	state = NONE;

	createdClickables = false;
}

Ball::~Ball()
{
}

void Ball::Start()
{
	material = getGameObject()->getComponent<MeshRenderer>()->getMaterial();
}

// change material color based on selection state
void Ball::Update(){
	Vector4 tempColor = board->getVectorFromColor(color);

	switch (state){
		case HIGHLIGHTED:
			material->setTexture("diffuseTexture", Utils::highlightTexture);

			tempColor = Vector4(tempColor[0] * .6, tempColor[1] * .6, tempColor[2] * .6, tempColor[3]);
			material->setVector4("tintColor",tempColor);

			if (Input::getMouseButtonDown(MouseButton::leftButton) && Ball::SelectedBall == nullptr && !Clickable::GraceFrame)
			{
				state = SelectionState::SELECTED;
				Ball::SelectedBall = this;
			}

			//After clicking on a "clickable" we don't want that mouse press to twice
			if (Input::getMouseButtonUp(MouseButton::leftButton))
				Clickable::GraceFrame = false;
		break;
		case SELECTED:
			//If the ball is selected, fill all of its empty neighbors with empty game objects with colliders and "clickable" components
			//If the clickable gets clicked then we'll know which direction we want to move the ball in
			if (!createdClickables)
			{
				std::vector<Neighbor*> neighbors = this->currentDimple->getNeighbors();
				for (unsigned int i = 0; i < neighbors.size(); i++)
				{
					Neighbor* neighbor = neighbors.at(i);
					Dimple* nDimple = neighbor->dimple;
					Vector3 actualNeighborPosition = *neighbor->dimple->getPos(); 
					bool validNeighbor = true;
					if (nDimple->isOccupied()){
						// check jump dimple
						Dimple* checkDimple = nDimple->getNeighborAtDirection(neighbor->direction);
						// if there is a neighbor
						if (checkDimple != nullptr){
							// if its occupied
							if (!checkDimple->isOccupied()){
								actualNeighborPosition = *nDimple->getNeighborAtDirection(neighbor->direction)->getPos();
							}
							else{
								validNeighbor = false;
							}
						}
						else{
							validNeighbor = false;
						}
						
						
						
					}

					if (validNeighbor){
						GameObject* clickable = new GameObject();
						SphereCollider* clickableCollider = new SphereCollider(Vector3(), 0.11f);
						clickable->addComponent(clickableCollider);
						clickable->addComponent(new Clickable(neighbor));

						Material* clickableMaterial = new Material(Utils::highlightShader);
						clickableMaterial->setTexture("diffuseTexture", Utils::highlightTexture);
						clickable->addComponent(new MeshRenderer(Utils::ballMesh, clickableMaterial));
						clickable->getTransform()->setPosition(actualNeighborPosition);
						clickable->getTransform()->setScale(Vector3(1.1f, 1.1f, 1.1f));

						//Gotta start the clickable
						clickable->Start();
					}

					
				}

				createdClickables = true;
			}

			if (Input::getMouseButtonDown(MouseButton::rightButton))
			{
				Clickable::ClearClickables();
				Clickable::Clicked = nullptr;

				createdClickables = false;
				state = SelectionState::NONE;
				Ball::SelectedBall = nullptr;
				Clickable::GraceFrame = false;

			}

			if (Clickable::Clicked != nullptr)
			{
				moveBall(Clickable::Clicked->getParentNeighbor()->direction);

				Clickable::ClearClickables();
				Clickable::Clicked = nullptr;

				createdClickables = false;
				state = SelectionState::NONE;
				Ball::SelectedBall = nullptr;

				Clickable::GraceFrame = true;
			}
		break;
		default:
			material->setTexture("diffuseTexture", startTexture);
			
			material->setVector4("tintColor", Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
}

Color Ball::getColor(){
	return color;
}

void Ball::OnMouseOver()
{
	if (Ball::SelectedBall == nullptr)
		state = SelectionState::HIGHLIGHTED;
}
void Ball::OnMouseExit()
{
	if (Ball::SelectedBall != this)
		state = SelectionState::NONE;
}

bool Ball::moveBall(Direction d){
	Dimple* moveTo = currentDimple->getNeighborAtDirection(d);
	if (moveTo == nullptr){
		// not a valid move
		return false;
	}

	//check for jump, 
	if (moveTo->isOccupied()){
		// checknext dimple
		moveTo = moveTo->getNeighborAtDirection(d);
		if (moveTo == nullptr || moveTo->isOccupied()){
			//if we cant jump return false again
			return false;
		}
	}

	//this dimple is no longer occupied
	currentDimple->toggleOccupied();

	// update current
	currentDimple = moveTo;
	currentDimple->toggleOccupied();

	//update transform;
	getGameObject()->getTransform()->setPosition(*currentDimple->getPos());
	//Hack to make sure collider updates position
	getGameObject()->getComponent<Collider>()->isColliding(getGameObject()->getComponent<Collider>(), NULL);

	return true;
}

Vector3* Ball::getPosition()
{
	return position;
}

void Ball::setStartTexture(Texture* startTexture)
{
	this->startTexture = startTexture;
}