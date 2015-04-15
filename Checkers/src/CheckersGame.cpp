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

	Material* boardMat;
	Shader* ballShader;
	Camera* camera;
	GameObject* cameraObject;

	GameObject* boardObject;
	Mesh* boardMesh;
	MeshRenderer* boardRenderer;
	Texture* testTexture;
	CheckersGame::CheckersGame() : Game(800, 600)
	{	
		



	}

	bool CheckersGame::init()
	{
		bool good = Game::init();

		if (!good)
			return false;

		ballShader = new Shader("Shaders/VertexShader", "Shaders/PixelShader");
		testTexture = new Texture("Textures/boardTextureTest.bmp");
		//board->addBall(new Ball()
		camera = new Camera(50, 0.1f, 0.1f, 0.1f, 100.0f);
		camera->setLookAt(Vector3(0.0f, 0.0f, 0.0f));
		camera->setActive();
		cameraObject = new GameObject();
		cameraObject->addComponent(camera);


		boardMat = new Material(ballShader);

		boardMesh = new Mesh("Models/d20Dimpled.obj");
		boardMat->setTexture("diffuseTexture", testTexture);
		boardRenderer = new MeshRenderer(boardMesh, boardMat);
		boardObject = new GameObject();
		boardObject->addComponent(boardRenderer);
		cameraObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 5.0f));
		boardObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 0.0f));




		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->Start();


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