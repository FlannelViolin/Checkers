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

	CheckersGame::CheckersGame() : Game(800, 600)
	{	
		



	}

	bool CheckersGame::init()
	{
		bool good = Game::init();

		if (!good)
			return false;

		Shader* ballShader = new Shader("Shaders/VertexShader", "Shaders/PixelShader");
		Texture* testTexture = new Texture("Textures/lavaTexture.bmp");
		Texture* d20Texture = new Texture("Textures/D20FullUnwrap.bmp");
		//board->addBall(new Ball()
		Camera* camera = new Camera(50, 0.1f, 0.1f, 0.1f, 100.0f);
		camera->setLookAt(Vector3(0.0f, 0.0f, -5.0f));
		camera->setActive();

		GameObject* cameraObject = new GameObject();
		cameraObject->addComponent(camera);

		Material* boardMat = new Material(ballShader);
		boardMat->setTexture("diffuseTexture", d20Texture);

		Mesh* boardMesh = new Mesh("Models/d20Dimpled.obj");
		MeshRenderer* boardRenderer = new MeshRenderer(boardMesh, boardMat);

		GameObject* boardObject = new GameObject();
		boardObject->addComponent(boardRenderer);


		cameraObject->getTransform()->setPosition(Vector3(0.0f, 0.0f,0.0f));
		boardObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, -5.0f));

		
		//+-=-=-=-=-=-=-=+ Lights! +-=-=-=-=-=-=-=-=+
		GameObject* lightObject2 = new GameObject();
		PointLight* light2 = new PointLight();
		light2->setDiffuseColor(Vector3(1.0f, 1.0f, 1.0f));
		light2->setSpecularColor(Vector3(.3f, .3f, .3f));
		lightObject2->getTransform()->setPosition(Vector3(0.0f, 10.0f, 0.0f));
		lightObject2->addComponent(light2);

		GameObject* lightObject1 = new GameObject();
		PointLight* light1 = new PointLight();
		light1->setDiffuseColor(Vector3(1.0f, 1.0f, 1.0f));
		light1->setSpecularColor(Vector3(.3f, .3f, .3f));
		lightObject1->getTransform()->setPosition(Vector3(0.0f, -10.0f, 0.0f));
		lightObject1->addComponent(light1);

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