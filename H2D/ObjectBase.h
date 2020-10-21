#pragma once
/*
#include "OpenGLH.h"
#include "Game.h"
#include "pObject.h"
#include "ObjectBasePolymorphism.h"
#include <Box2D\Box2D.h>
#include <boost\ptr_container\ptr_vector.hpp>

class ObjectBase : public ObjectBasePolymorphism
{
public:
	
	virtual ~ObjectBase(void);

	virtual void isHitByLaser() = 0;

	
	pObject* addObject(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT);
	pObject* addPolygon(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT);
	pObject* addCircle(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT, void* xxx);

	static void update();
	static void renderObjects();

	static b2Vec2 getGravity();
	static void setGravity(b2Vec2 gravity);

	static void setWorld(b2World* w);
	static b2World* getWorld();

	static void setWorldPos(b2Vec2 pos);
	static b2Vec2 getWorldPos();

	int testFunc();

protected:
	static b2World* world;
	static b2Vec2 worldPos;

	ObjectBase(void);

	
	pObject* object;
	b2Body* body;

private:

	static GLuint addObjectInternal(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT);
	static GLuint addPolygonInternal(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT);
	static GLuint addCircleInternal(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT, void* xxx);

	static boost::ptr_vector<pObject> objects;
	static GLint velocityIterations, positionIterations;
};

*/