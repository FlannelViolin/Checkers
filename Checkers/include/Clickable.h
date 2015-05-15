#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\SphereCollider.hpp"

struct Neighbor;

using namespace Brickware;
using namespace Core;
using namespace Math;

class Clickable : public Component
{
public:
	static Clickable* Clicked;
	static void ClearClickables();
	static bool GraceFrame;

	Clickable(Neighbor* parentNeighbor);

	Neighbor* getParentNeighbor();

	//Overrides
	virtual void Start();
	virtual void Update();

	virtual void OnMouseOver();
	virtual void OnMouseStay();
	virtual void OnMouseExit();

	~Clickable();

private:
	static std::vector<Clickable*> clickables;

	Neighbor* parentNeighbor;
	bool mouseOver;
};

#endif