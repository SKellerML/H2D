#pragma once

#include "BaseObject.h"
#include "OpenGLH.h"
#include "Mask.h"
#include "Person.h"

#include <memory>

class SoundLogicListenerCallback : public b2QueryCallback
{
public:
	SoundLogicListenerCallback() {}
	~SoundLogicListenerCallback() {}

	bool ReportFixture(b2Fixture* fixture)
	{
		
		int* fixtureType = (int*)fixture->GetUserData();
		if (fixtureType != nullptr && *fixtureType == GAMEOBJECTTYPE_PERSON) { fixtureVector.push_back(std::make_shared<b2Fixture>(*fixture));  }// printf("EEEEEEEEEEE %i \n", *fixtureType);

		return true;
	}

	std::vector<std::shared_ptr<b2Fixture> > fixtureVector;

};

class SoundLogic : public Person // Derived from Person because of TileMap
{
public:
	SoundLogic();
	~SoundLogic();

	virtual void update() {}
	virtual void render() { lines.render(worldPos); }

	virtual void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint maxDistance = -1) {}
	// volume in tiles it can reach
	void createSound(b2Vec2 position, GLfloat volume,bool suspicious);
	// get Distance in accessible path, diagonal 1.4 instead of 2
	GLfloat pathDistance(GLuint maxDistance, b2Vec2 startPos, b2Vec2 targetPos, GLuint sizeX, GLuint sizeY, std::vector<b2Vec2>* pathVector = NULL);//b2Vec2 startPos, b2Vec2 targetPos, GLuint maxDistance, GLuint sizeX, GLuint sizeY, std::vector<b2Vec2>* pathVectorDebug = NULL);

private:
	ElementLines lines;


};

