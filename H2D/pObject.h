#pragma once
/*
#include <vector>
#include <math.h>

#include "Game.h"
#include "Texture2D.h"
#include "GameState.h"
#include "LevelContactListener.h"
#include "TickCounter.h"
#include "ObjectBasePolymorphism.h"

#include "Audio.h"

#include <Box2D\Box2D.h>
#include <boost\ptr_container\ptr_vector.hpp>

#define toAngle(rad) (rad*360)/(2*b2_pi) // rad = 2*pi*alpha/360
#define toRad(a) (a*2*b2_pi)/360 // rad = (a*2*b2_pi)/360 => rad*360=a*2*pi => a=


//Physics Object


enum objectSheet
{
	SHEET_DEBUG,

};

class pObject
{
public:
	pObject(void);
	~pObject(void);

	b2Body* init(GLfloat x, GLfloat y,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,pObject* data,GLuint materialT);
	b2Body* initCircle(GLfloat x, GLfloat y,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,pObject* data,GLuint materialT, void* xxx);
	b2Body* initPolygon(GLfloat x, GLfloat y,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,pObject* data,GLuint materialT);

	void destroyBody();

	void createDebris();


	void applyForce(const b2Vec2 &force);
	void applyLinearImpulse(const b2Vec2 &impulse);
	void applyAngularImpulse(GLfloat &impulse);
	b2Body* getBody();

	void render();

	b2Vec2 getHalfSize();

	GLuint getMaterialType();

	bool collision();

	static void update();

	static GLuint addSheet(std::string *sheetLocation);
	static void deleteSheets();
	static GLuint addSprite(Rect &obj,GLuint sheet);
	static SpriteSheet2D* getSpriteSheet(int id);

	enum MaterialTypes
	{
		MATERIAL_METAL,
		MATERIAL_WOOD,
		MATERIAL_CHEESE
	};

	static void setWorldPos(b2Vec2 pos);
	static b2Vec2 getWorldPos();
	
	static void setWorld(b2World* w);
	static b2World* getWorld();


	ObjectBasePolymorphism* baseObject;

protected:
	static b2World* world;
	static b2Vec2 worldPos;
	//GLint velocityIterations, positionIterations;
	static LevelContactListener contactL;

	static boost::ptr_vector<SpriteSheet2D> sheetList;

	



	b2Body* body;
	
	GLuint spriteSheet;
	GLuint spriteID;
	//Texture2D sprite;
	GLuint materialType;


	b2Vec2 halfSize;


	TickCounter collisionTimer;
	// Variablen Physik

	//boost::ptr_vector<b2Body> debris;
	//std::vector<GLuint> debrisVAO;

	//momentum: p=m*v
	//impulse: p=F*delta t (Kraftstoﬂ)
};

*/
