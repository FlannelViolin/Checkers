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

// change material color based on selection state
void Ball::Update(){
	switch (state){
		case HIGHLIGHTED:
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
					
					GameObject* clickable = new GameObject();
					SphereCollider* clickableCollider = new SphereCollider(Vector3(), 0.11f);
					clickable->addComponent(clickableCollider);
					clickable->addComponent(new Clickable(neighbor));
					clickable->addComponent(new MeshRenderer(new Mesh("Models/BallSmall.obj"), new Material(new Shader("Shaders/VertexShader", "Shaders/PixelShader"))));
					clickable->getTransform()->setPosition(*neighbor->dimple->getPos());
					clickable->getTransform()->setScale(Vector3(1.1f, 1.1f, 1.1f));
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

Vector3* Ball::getPosition(){
	return position;
}