#pragma once

#include "BaseObject.h"
#include "OpenGLH.h"

#include "TickCounter.h"
#include "TileObject.h"
#include "TileProgram.h"
#include "Light.h"
#include "Mask.h"
#include "Person.h"
#include "Rect.h"
#include "SpriteSheet2D.h"
#include <vector>
#include <Box2D\Box2D.h>

struct TexCoords4
{
	b2Vec2 t0;
	b2Vec2 t1;
	b2Vec2 t2;
	b2Vec2 t3;
};

class TileMap
{
public:
	TileMap();
	TileMap(std::ifstream *myfile,GLuint sX, GLuint sY) { create(myfile,sX,sY); }
	~TileMap();

	static void loadTileMapBaseData();

	TileObject& getTileObject(GLuint tileID)	{ if (tileID < tileMap.size()) return tileMap[tileID]; }
	void create(std::ifstream *myfile, GLuint sX, GLuint sY);
	void changeTile(GLuint tileID, TileObject tileObj);
	void update();
	void render();

	void saveTileMap(std::ofstream &sstream);
	void loadTileMap(std::ifstream *myfile, GLuint sX, GLuint sY);

	void calculateWalls();
	void destroyWall(GLuint tile);

	GLuint getSizeX() {return sizeX;}

	void setTileMaps();

private:
	GLuint sizeX, sizeY, sizeOverall;
	GLuint tileMapVAO, tileMapVBO;
	static GLuint tileMapSheet;
	static GLuint tileMapSheetTextureID;

	GLuint mVAOID;
	GLuint vertexVBO; 
	GLuint textureVBO;

	std::vector<GLint> startCount;
	std::vector<GLsizei> count;

	static TileProgram tileProgram;

	std::vector< TileObject > tileMap;
	std::vector< Wall > wallVector;
	static std::vector< TexCoords4 > texCoords;


};

