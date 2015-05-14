#include "Clickable.h"
#include "Dimple.h"

//Statics
Clickable* Clickable::Clicked = nullptr;
std::vector<Clickable*> Clickable::clickables;

void Clickable::ClearClickables()
{
	//Delete all clickable game objects
	for (unsigned int i = 0; i < clickables.size(); i++)
	{
		clickables.at(i)->toDelete = true;
	}
	
	clickables.clear();
}

Clickable::Clickable(Neighbor* parentNeighbor)
{
	this->parentNeighbor = parentNeighbor;
	clickables.push_back(this);

	mouseOver = false;
	toDelete = false;
}

Neighbor* Clickable::getParentNeighbor(){ return this->parentNeighbor; }

void Clickable::Start(){}

void Clickable::Update()
{
	if (toDelete)
		return;

	if (mouseOver)
	{
		if (Input::getMouseButtonDown(MouseButton::leftButton))
		{
			Clicked = this;
		}
	}

	if (Input::getMouseButtonDown(MouseButton::rightButton))
	{
		std::cout << "Cancel" << std::endl;
	}
}

void Clickable::OnMouseOver()
{
	mouseOver = true;
}

void Clickable::OnMouseStay()
{
	mouseOver = true;
}

void Clickable::OnMouseExit()
{
	if (toDelete)
		delete this->getGameObject();
}

Clickable::~Clickable()
{

}