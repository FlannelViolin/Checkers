#include "Game.h"
#include "Board.h"
#include "Dimple.h"
#include "Ball.h"
using namespace Brickware;
using namespace Core;
using namespace Graphics;
using namespace Math;
using namespace Utility;

class CheckersGame : public Game
{
public:
	Board* board;
	Material* mat;
	Shader* ballShader;
	Camera* camera;
	GameObject* cameraObject;
	CheckersGame::CheckersGame() : Game(800, 600)
	{	
		ballShader = new Shader("VertexShader.hlsl", "PixelShader.hlsl");
		//board->addBall(new Ball()
		camera = new Camera(50, 0.1f, 0.1f, 0.1f, 100.0f);
		camera->setActive();
		cameraObject = new GameObject();
		cameraObject->addComponent(camera);

		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->Start();

	}

	bool CheckersGame::init()
	{
		bool good = Game::init();

		if (!good)
			return false;

		return true;
	}

	void CheckersGame::updateScene()
	{
		if (Input::getKeyDown(KeyCode::escape))
			running = false;

		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->Update();
	}

	void CheckersGame::renderScene()
	{
		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->OnRender();
	}

	CheckersGame::~CheckersGame()
	{
	}
};

//ENTRY POINT
int main(int argc, char **argv)
{
	CheckersGame game;

	if (!game.init())
		return -1;

	return game.run();
}