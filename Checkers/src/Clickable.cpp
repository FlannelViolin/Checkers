#include "Clickable.h"
#include "Dimple.h"

//Statics
Clickable* Clickable::Clicked = nullptr;
std::vector<Clickable*> Clickable::clickables;
bool Clickable::GraceFrame = false;

void Clickable::ClearClickables()
{
	//Delete all clickable game objects
	for (unsigned int i = 0; i < clickables.size(); i++)
	{
		GameObject::Destroy(clickables.at(i)->getGameObject());
	}
	
	clickables.clear();
}

Clickable::Clickable(Neighbor* parentNeighbor)
{
	this->parentNeighbor = parentNeighbor;
	clickables.push_back(this);

	Clickable::Clicked = nullptr;

	mouseOver = false;
}

Neighbor* Clickable::getParentNeighbor(){ return this->parentNeighbor; }

void Clickable::Start(){}

void Clickable::Update()
{
	if (mouseOver)
	{
		if (Input::getMouseButtonDown(MouseButton::leftButton) && !Clickable::GraceFrame)
		{
			Clicked = this;
			Clickable::GraceFrame = true;
		}

		if (Input::getMouseButtonUp(MouseButton::leftButton))
			Clickable::GraceFrame = false;
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
	mouseOver = false;
}

Clickable::~Clickable()
{

}