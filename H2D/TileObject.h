#pragma once

#include "OpenGLH.h"
#include <Box2D\Box2D.h>
#include "BaseObject.h"
#include "Wall.h"

#define TILE_WIDTH 64.f
#define TILE_WIDTH_B2 TILE_WIDTH/100.f

const int transparent = 1;

enum TileType
{
	TILE_WALL,
	TILE_FLOOR,
};

enum Directions
{
	DIRECTION_NONE,
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_RIGHT,
};

struct TileObject
{
	TileObject()	{}
	TileObject(b2Vec2 pos, GLuint id)	{ init(pos, id); }
	~TileObject()	{}
	
	void init(b2Vec2 pos, GLuint id)
	{
		if (id == 0)
		{				
			passable = true;
			isWall = false;
		}
		else
		{
			passable = false;
			isWall = true;		
		}

		position = pos;
		//obj->initObject(COLLISIONOBJECTTYPE_WALL, pos, 0.f, b2_staticBody, 1.f, 1.f, 0.f, true, &obj, 0);
		spriteID = id;

	}
	
	void setWallObject(GLuint wo)	{ wallObject = wo; }
	GLuint getWallObject()	{ return wallObject; }
	bool isPassable() { return passable; }

	GLuint isWall;
	GLuint wallObject;
	b2Vec2 position;
	bool passable;
	bool isTransparent;	
	GLuint spriteID;
};

//
//struct TileObject
//{
//	TileObject()	{}
//	TileObject(b2Vec2 pos, GLuint id)	{ init(pos, id); }
//	~TileObject()	{}
//
//	virtual void init(b2Vec2 pos, GLuint id) = 0;
//
//	GLuint isWall;
//	b2Vec2 position;
//	bool isPassable;
//	bool isTransparent;	
//	GLuint spriteID;
//};
//
//struct WallTile : public TileObject
//{
//	void init(b2Vec2 pos, GLuint id) override
//	{	
//		isWall = true;
//		isTransparent = true;
//		position = pos;
//
//		pos *= (1.f / 100.f);
//		//pos -= b2Vec2(TILE_WIDTH / 200, TILE_WIDTH / 200);
//		//obj = new BaseObject();
//		//obj->initObject(COLLISIONOBJECTTYPE_WALL, pos, 0.f, b2_staticBody, 1.f, 1.f, 0.f, true, &obj, 0);
//		printf("Pos: %f || %f \n", pos.x, position.x); 
//		b2BodyDef bodyDefinition;
//		bodyDefinition.type = b2_staticBody;
//
//		bodyDefinition.position.Set(pos.x, pos.y);
//		bodyDefinition.userData = (void*)this;//data;
//
//		bodyDefinition.angle = 0.f;
//		body = BaseObject::getWorld()->CreateBody(&bodyDefinition);
//
//		// Fixture
//		b2FixtureDef fixture;
//		fixture.density = 0.5;
//		fixture.friction = .5f;
//		fixture.restitution = .0f;
//		//fixture.filter.categoryBits = 0x0010;
//		//fixture.userData = &standardFixtureValue;
//		b2PolygonShape box;
//		GLfloat size = TILE_WIDTH / 200;
//		box.SetAsBox(size, size);
//		fixture.shape = &box;
//		body->CreateFixture(&fixture);
//
//		spriteID = 1;
//		isPassable = false;
//	}
//	Wall w;
//	b2Body* body;
//	//std::shared_ptr<BaseObject> obj;
//};
//
//struct FloorTile : public TileObject
//{
//	void init(b2Vec2 pos, GLuint id) override
//	{
//		isWall = false;
//		position = pos;
//		//obj->initObject(COLLISIONOBJECTTYPE_WALL, pos, 0.f, b2_staticBody, 1.f, 1.f, 0.f, true, &obj, 0);
//		spriteID = 0;
//		isPassable = true;
//	}
//};