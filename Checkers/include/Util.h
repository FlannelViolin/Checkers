#ifndef UTIL_H
#define UTIL_H

enum SelectionState{
	HIGHLIGHTED,
	SELECTED,
	NONE

};

enum Direction{
	LEFT = 0,
	UP_LEFT = 1,
	UP_RIGHT = 2,
	RIGHT = 3,
	DOWN_RIGHT = 4,
	DOWN_LEFT = 5
};

enum Color{
	LIME,
	GREEN,
	BLACK,
	WHITE,
	VIOLET,
	PURPLE,
	YELLOW,
	CYAN,
	RED,
	BLUE,
	GRAY
};

//Just going to store some static data here
class Utils
{
public:
	static Brickware::Graphics::Mesh* ballMesh;
	static Brickware::Graphics::Shader* highlightShader;
	static Brickware::Graphics::Texture* whiteTexture;
	static Brickware::Graphics::Texture* highlightTexture;
};


#endif UTIL_H