#pragma once

#include "BaseObject.h"
#include "Element2D.h"

#include <set>

class Wall : public BaseObject
{
public:
	Wall();
	~Wall();

	// Create Wall from starpos to targetPos as squares, but pyhsics coordinates
	void init(b2Vec2 startPos,b2Vec2 targetPos);

	virtual void update() override;
	virtual void render() override;
	virtual void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture) override	{}
	
	void addTile(int tile)	{ tiles.insert(tile); }
	void removeTile(int tile) { tiles.erase(tile); }

	void destroyWall()	{ world->DestroyBody(body); }

	b2Vec2 getStartPos(){ return m_startPos; }
	b2Vec2 getEndPos(){ return m_endPos; }

	void setActive(bool a)	{ active = a; }

private:
	static GLuint gameobjectType;

	bool active;
	ElementPolygon polpol;

	b2Vec2 m_startPos;
	b2Vec2 m_endPos;

	std::set<int> tiles;
};

