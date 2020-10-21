#pragma once

#include "OpenGLH.h"
#include "GameState.h"
#include "GUI_H.h"

#include "BaseObject.h"

//#include "Player.h"

#include "GUI_H.h"

#include "WorldObject.h"
#include "Sound.h"
#include "Animation.h"
#include "TickCounter.h"
#include "Item.h"

#include "Door.h"
#include "Wall.h"
#include "Person.h"

#include "SimpleParticleEmitter.h"

#include "GUIMap.h"
#include "TileProgram.h"

#include <unordered_map>
#include <Box2D\Box2D.h>
#include <boost\shared_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>
#include "TileObject.h"
#include "TileMap.h"
#include "Light.h"
#include "Player.h"
#include "Entity.h"
#include "ObjectList.h"
#include "MaskProgram.h"

#include <fstream>
#include <ostream>
#include <sstream>


enum LevelTypes
{
	LEVELTYPE_TUTORIAL,
	LEVELTYPE_BEACON,
	LEVELTYPE_L3,
	LEVELTYPE_MINING,
};

struct BackgroundData
{
	BackgroundData(	GLuint _spriteID,GLfloat _zIndex,b2Vec2 _position) : spriteID(_spriteID),zIndex(_zIndex),position(_position)	{}

	GLuint spriteID;
	GLfloat zIndex;
	b2Vec2 position;
};

class Level : public GameState
{
public:
	Level()	{ init(0); }
	Level(GLuint levelType);
	~Level(void);

	void init(GLuint levelType);
	void update();
	void renderBackground();
	void render();
	void updateRender();
	void renderFinal();

	//boost::ptr_vector<pObject>* getObjects();

	void loadLevel(const char* name);
	void saveLevel();
	void setCurrentFloor(GLuint floor);
protected:

	

	Texture2D tex;
	Wall w[4];
	Person p;
	Player player;
	//PoliceCar pc1;
	Entity ente;
	Item ii;
	GLuint door;
	
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

	//std::vector< std::shared_ptr<Item> > itemVector;

	//GLuint currentFloor;
	//std::vector<TileMap> tm;
	//std::vector<ObjectList> objectContainer;

	GLuint sizeX;
	GLuint sizeY;
	GLuint sizeOverall;
};

