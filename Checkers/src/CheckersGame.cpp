#include "BrickwareCore\Game.hpp"

#include "Board.h"
#include "Dimple.h"
#include "Ball.h"
#include "BoardControl.h"
#include "CameraControl.h"

using namespace Brickware;
using namespace Core;
using namespace Graphics;
using namespace Math;
using namespace Utility;

//Setup some stupid statics
Mesh* Utils::ballMesh;
Shader* Utils::highlightShader;
Texture* Utils::whiteTexture;
Texture* Utils::highlightTexture;

class CheckersGame : public Game
{

public:

	Board* board;
	int playerNum = 10; 
	bool PausedState = true;
	GameObject* CamLightObject;
	GameObject* cameraObject;


	CheckersGame::CheckersGame() : Game(800, 600)
	{	
		


	}

	bool CheckersGame::init()
	{
		bool good = Game::init();

		if (!good)
			return false;		

		Texture* lavaTexture = new Texture("Textures/lavaTexture.bmp");
		Texture* d20Texture = new Texture("Textures/D20FullUnwrap.bmp");
		Texture* UITexture = new Texture("Textures/UiUV.bmp");
		Texture* DragonTexture = new Texture("Textures/DragonUV.bmp");
		
		//color textures
		Texture* limeTexture = new Texture("Textures/lime.bmp");
		Texture* greenTexture = new Texture("Textures/green.bmp");
		Texture* blackTexture = new Texture("Textures/black.bmp");
		
		Utils::highlightTexture = new Texture("Textures/BallHighlighttexture.bmp");
		Utils::whiteTexture = new Texture("Textures/white.bmp");
		Texture* violetTexture = new Texture("Textures/violet.bmp");
		Texture* purpleTexture = new Texture("Textures/purple.bmp");
		Texture* yellowTexture = new Texture("Textures/yellow.bmp");
		Texture* cyanTexture = new Texture("Textures/cyan.bmp");
		Texture* redTexture = new Texture("Textures/red.bmp");
		Texture* blueTexture = new Texture("Textures/blue.bmp");

		Texture* texArray[10] = { limeTexture, greenTexture, lavaTexture, Utils::whiteTexture, 
			violetTexture, purpleTexture, yellowTexture, cyanTexture, redTexture, blueTexture};
		
		Shader* lavaShader = new Shader("Shaders/GlowVertexShader", "Shaders/GlowPixelShader");
		Utils::highlightShader = new Shader("Shaders/VertexShader", "Shaders/PixelHighlight");
		Shader* boardShader = new Shader("Shaders/VertexShader", "Shaders/PixelShader");

		Shader* shaderArray[10] = { Utils::highlightShader, Utils::highlightShader, lavaShader, Utils::highlightShader, Utils::highlightShader, Utils::highlightShader,
			Utils::highlightShader, Utils::highlightShader, Utils::highlightShader, Utils::highlightShader };

		setCursorVisible(true);
	
		//board->addBall(new Ball()
		Camera* camera = new Camera(90, 0.1f, 0.1f, 0.1f, 100.0f);
		camera->setLookAt(Vector3(0.0f, 0.0f, -3.0f));
		camera->setActive();

		CameraControl* cameraControl = new CameraControl(PausedState);
		//FirstPersonController* fpControl = new FirstPersonController();

		cameraObject = new GameObject();
		cameraObject->addComponent(camera);
		//cameraObject->addComponent(fpControl);
		cameraObject->addComponent(cameraControl);

		Mesh* DragonMesh = new Mesh("Models/UIDragon.obj");
		Material* dragonMat = new Material(boardShader);
		dragonMat->setTexture("diffuseTexture", DragonTexture);
		MeshRenderer* dragonRenderer = new MeshRenderer(DragonMesh, dragonMat);

		Mesh* UIMesh = new Mesh("Models/UIConsole.obj");
		Material* UIMat = new Material(boardShader);
		UIMat->setTexture("diffuseTexture", UITexture);
		MeshRenderer* UIRenderer = new MeshRenderer(UIMesh, UIMat);

		cameraControl->UI->addComponent(dragonRenderer);
		cameraControl->UI->addComponent(UIRenderer);

		Material* boardMat = new Material(boardShader);
		boardMat->setTexture("diffuseTexture", d20Texture);

		Mesh* boardMesh = new Mesh("Models/d20Dimpled.obj");
		MeshRenderer* boardRenderer = new MeshRenderer(boardMesh, boardMat);

		GameObject* boardObject = new GameObject();
		boardObject->addComponent(boardRenderer);
		

		cameraObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 3.0f));
		boardObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 0.0f));

		
		//+-=-=-=-=-=-=-=+ Lights! +-=-=-=-=-=-=-=-=+
		GameObject* lightObject1 = new GameObject();
		PointLight* light1 = new PointLight();
		light1->setDiffuseColor(Vector3(.5f, .5f, .5f));
		light1->setSpecularColor(Vector3(.3f, .3f, .3f));
		lightObject1->getTransform()->setPosition(Vector3(0.0f, -20.0f, 0.0f));
		lightObject1->addComponent(light1);

		GameObject* lightObject2 = new GameObject();
		PointLight* light2 = new PointLight();
		light2->setDiffuseColor(Vector3(.8f, .8f, .8f));
		light2->setSpecularColor(Vector3(.3f, .3f, .3f));
		lightObject2->getTransform()->setPosition(Vector3(0.0f, 10.0f, 0.0f));
		lightObject2->addComponent(light2);


		CamLightObject = new GameObject();
		PointLight* light3 = new PointLight();
		light3->setDiffuseColor(Vector3(.8f, .8f, .8f));
		light3->setSpecularColor(Vector3(.3f, .3f, .3f));
		CamLightObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));
		CamLightObject->addComponent(light3);


		//+ game object testing //

		//Material* ballMat = new Material(ballShader);
		//ballMat->setTexture("diffuseTexture", lavaTexture);
		//GameObject* ballObject = new GameObject();
		//ballObject->addComponent(ballRenderer);
		//ballObject->getTransform()->setPosition(Vector3(0.0f, 0.0f, 0.0f));
		

		Utils::ballMesh = new Mesh("Models/BallSmall.obj");

		board = new Board();
		board->populateBoard("Coords/Dimples.js",playerNum);
		board->populateNeighbors();
		boardObject->addComponent(board);

		for (Ball* b : board->getBalls()){
			GameObject* ballObject = new GameObject();
			int index = int(b->getColor());

			Material* tempMat = new Material(shaderArray[index]);
			tempMat->setTexture("diffuseTexture", texArray[index]);
			MeshRenderer* ballRenderer = new MeshRenderer(Utils::ballMesh, tempMat);
			b->setStartTexture(texArray[index]);
			ballObject->addComponent(b);
			ballObject->addComponent(ballRenderer);
			ballObject->getTransform()->setPosition(*b->getPosition());
			SphereCollider* collider = new SphereCollider(*b->getPosition(), .1f);
			ballObject->addComponent(collider);
		}

		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->Start();
		return true;
	}

	void CheckersGame::updateScene()
	{
		if (Input::getKeyDown(KeyCode::escape))
			running = false;

		//CamLightObject->getTransform()->setPosition(cameraObject->getTransform()->getPosition());
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