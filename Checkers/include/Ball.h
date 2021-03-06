#ifndef BALL_H
#define BALL_H
#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Transform.hpp"
#include "BrickwareCore\GameObject.hpp"
#include "BrickwareCore\Collider.hpp"
#include "BrickwareCore\SphereCollider.hpp"

#include "Dimple.h"
#include "Util.h"
#include "Board.h"
#include "Clickable.h"

using namespace Brickware;
using namespace Core;
using namespace Math;
using namespace Graphics;

class Board;
class Dimple;
class Ball : public Component
{

private:
	static Ball* SelectedBall;

	Color color;
	Material* material;
	Texture* startTexture;
	Dimple* currentDimple;
	SelectionState state;
	Vector3* position;

	// board will have a list of ALL BALLS ON THE BAORD apaprently and which ball is currently selected
	Board* board;

	bool createdClickables;

public:
	Ball();
	~Ball();

	Ball(Color c, Dimple* startDimple, Board* b, Vector3* pos);

	virtual void Start();
	virtual void Update();
	virtual void OnMouseOver();
	virtual void OnMouseExit();
	
	bool moveBall(Direction d);
	Vector3* getPosition();
	void setStartTexture(Texture* startTexture);

	Color getColor();
};

#endif BALL_H