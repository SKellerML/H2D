#pragma once


#include "GameState.h"
#include "GUI_H.h"
#include "Light.h"
#include "ObjectList.h"
#include "OpenGLH.h"
#include "TileObject.h"
#include "TileMap.h"


#include "GUI_H.h"
#include "Font2D.h"

class Editor : public GameState
{
public:
	Editor()	{ init(0); }
	Editor(GLuint levelType);
	~Editor(void);

	void init(GLuint levelType);
	void update();
	void renderBackground();
	void render();
	void updateRender();
	void renderFinal();

	//boost::ptr_vector<pObject>* getObjects();
	void loadLevel(const char* name);
	void loadEmptyLevel(int numberOfFloors);
	void saveLevel();
	void setCurrentFloor(GLuint floor);

protected:

	//TileMap tm;

	Texture2D tex;
	Wall w[4];

	ElementPolygon elem;
	ElementPolygon elemB;

	MaskProgram maskP;

	Texture2D bgTex, maskTex;
	GLuint backBuf, maskBuf;// , foreBuf;


	Texture2D testTexB, testTexM, TestTexF;
	GLuint renderedTexture;
	GLuint backRenderTexture;

	PointLight testLight;

	ElementPolygon background;

	// current Tile
	ElementPolygon currentTileRenderSquare;
	b2Vec2 currentTileRenderPos;

	// Setup
	GUIPanel setupPanel;
	bool setupPanelActive;

	// ui
	bool isInGUI;
	GUIButtonPlain btn_save;
	GUIButtonPlain btn_clear;
	GUIButtonPlain btn_load;
	ElementPolygon uiBackground;

	FontObject floorText;


	// Floor management
	GLuint currentFloor;
	std::vector<TileMap> tm;

	GLuint sizeX;
	GLuint sizeY;
	GLuint sizeOverall;
};

