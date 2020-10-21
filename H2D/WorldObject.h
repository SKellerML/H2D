#pragma once
/*
#include <vector>

#include "Game.h"
#include "Texture2D.h"
#include "GameState.h"
#include "LevelContactListener.h"
#include "ObjectBase.h"
#include "pObject.h"
#include <Box2D\Box2D.h>
#include <boost\ptr_container\ptr_vector.hpp>

class pObject;

class WorldObject
{
public:
	WorldObject(void);
	~WorldObject(void);

	pObject* addObject(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT);
	pObject* addPolygon(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT);
	pObject* addCircle(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT);

	void update();
	void renderObjects();

	b2Vec2 getGravity();
	void setGravity(b2Vec2 gravity);


	b2World* world;
private:
	boost::ptr_vector<pObject> objects;

	GLint velocityIterations, positionIterations;
};
*/
