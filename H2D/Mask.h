#pragma once

#include "OpenGLH.h"
#include "Game.h"
#include "Element2D.h"
#include "Rect.h"
#include "VertexPos2D.h"
#include "MaskProgram.h"
#include "TickCounter.h"

#include "TileObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include <Box2D\Box2D.h>
#include <vector>
#include <map>
#include <unordered_map>

// Get Manhatten Distance between two points
GLuint manhattanDistance(b2Vec2 t1, b2Vec2 t2);

GLuint manhattanDistance(GLuint tileID_1, GLuint tileID_2, GLuint sizeX, GLuint sizeY);

// Get Position of Tile in Tilemap Coordinates
b2Vec2 getTilePos(b2Vec2 pos);
// Get Tile ID - Insert Tilemap Coordinates
GLuint getTile(b2Vec2 pos, GLuint sizeX);
// Get Position of Tile in Tilemap Coordinates
b2Vec2 getPos(GLuint tileID, GLuint sizeX);


class castcall : public b2RayCastCallback
{
public:
	castcall()	{ isHit = false; mfraction = 1.f; }

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		//TileObject* tt = (TileObject*)fixture->GetBody()->GetUserData();
		//int val = *(int*)fixture->GetUserData();
		//if (fixture->GetFilterData().categoryBits != 0x0010)	return mfraction;
		if (fixture->GetFilterData().categoryBits == COLLISIONOBJECTTYPE_WALL)
		{			
			isHit = true;
			hitPoint = point;
			hf = fixture;
			mfraction = fraction;

			return mfraction;
		}
		return mfraction;
	}

	bool isHit;
	b2Vec2 hitPoint;
	b2Fixture* hf;
	float mfraction;
};


class closeHitCall : public b2RayCastCallback
{
public:

	closeHitCall()	{ isHit = false; bod = nullptr; }

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		bod = fixture->GetBody();
		isHit = true;
		//mfraction = fraction;
		//isHit = true;
		return fraction;
	}

	bool isHit;
	b2Body* bod;
	float mfraction;
};

class querycall : public b2QueryCallback
{
public:
	bool ReportFixture(b2Fixture* fixture)
	{
		fixtureList.push_back(fixture);
		return true;
	}

	std::vector<b2Fixture*> fixtureList;
};

extern bool SortVector(b2Vec3 i, b2Vec3 j);//	{ return (i.z < j.z) && (-b2_pi >(i.z - j.z) < b2_pi); }	// b2_pi > (i.z - j.z) < b2_pi;
extern bool CompareVectorZ(b2Vec3 i, b2Vec3 j);//	{ return (i.z == j.z); }

class Mask
{
public:
	Mask();
	~Mask();


	static void updateMask(b2Vec2 centerPosition, std::shared_ptr<b2World> world);


	static void renderMask(b2Vec2 wp, GLuint backRenderTexture, GLuint frontRenderTexture);

	static void setTileMap(std::vector<TileObject>* vecTileMap, GLuint sX, GLuint sY);
	static void initMask();
	static void debugRender();
private:
	static bool tb;

	static Texture2D fovMap;

	static ElementPolygon maskPolygon;
	static std::vector<TileObject>* tileMap;
	static GLuint sizeX, sizeY;

	static GLuint maskBuf;
	static GLuint renderedTexture;
	static GLuint mVAOID;
	static MaskProgram maskP;

	static ElementLines faceLines;
	static b2Vec2 maskCenterPosition;

	static TickCounter tc;
};

