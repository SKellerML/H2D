#pragma once

#include "BaseObject.h"
#include "GameState.h"
#include "Explosion.h"
#include "Mask.h"
#include "TileObject.h"

class objQuery : public b2QueryCallback
{
public:
	objQuery() { hit = false; }
	~objQuery() {}
	bool ReportFixture(b2Fixture* fixture)
	{
		hit = true;
		return false;
	}
	bool hit;
};

class Person : public BaseObject
{
public:
	Person();
	~Person();

	void init(b2Vec2 pos, GLfloat floor = -1);
	virtual void reInit();
	void moveTo(b2Vec2 pos_w, bool calculatePath);
	void move();

	virtual void update() override;
	virtual void render() override;
	virtual void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture) override;

	static void setTileMap(std::vector< TileObject >* vecTileMap, GLuint sX, GLuint sY);

	static bool findPath(std::vector<b2Vec2>* pathVector, b2Vec2 startPos, b2Vec2 targetPos, GLuint sizeX, GLuint sizeY);	// maybe add vector as param and change the vector according

	virtual void listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious);

protected:

	bool isMoving;
	std::vector<b2Vec2> pathToMove;

	b2Vec2 movingToPos;

	b2Vec2 targetPos, targetTile;
	GLuint targetTileID;

	b2Vec2 renderPos;

	static std::vector< TileObject >* tileMap;

	static GLuint sizeX, sizeY;

	bool inRagdoll;
	TickCounter ragdollTimer;
	GLfloat ragdollTime;

	ElementLines line;
};


class Civilian : public Person
{
	//virtual void update() override;
	//virtual void render() override;
	virtual void listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious);

protected:


};

class Guard : public Person
{
	//virtual void update() override;
	//virtual void render() override;
	virtual void listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious);

protected:


};