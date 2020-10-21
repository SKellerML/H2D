#include "OpenGLH.h"

#include "Texture2D.h"
#include "Game.h"

#include "FontObject.h"
#include "BaseObject.h"
#include "RayCastCallbacks.h"

#include "tinyxml2.h"

#include "Audio.h"


#include <math.h>
#include <vector>
#include <valarray>
#include <boost/math/special_functions/round.hpp>
#include <boost\smart_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>

#include <boost\foreach.hpp>

class Sensor
{
public:
	Sensor() {testInt=22;}
	~Sensor() {}

	void createSenor(b2Body* parentBody, GLuint sensorID, GLfloat sensorRadius, GLfloat sensorAngle = 360.f) 
	{
		b2FixtureDef fixture;
		fixture.density=0.0;
		fixture.isSensor=true;
		fixture.userData=this;
		
		if(sensorAngle > 360.f)	sensorAngle=360.f;
		else if(sensorAngle < 0.f)	sensorAngle=0.f;

		if(sensorAngle == 360.f)
		{
			b2CircleShape shape;
			shape.m_radius=sensorRadius;
			fixture.shape=&shape;
			parentBody->CreateFixture(&fixture);
		}
		else
		{
			b2Vec2 y[8];
			GLfloat radius=sensorRadius;
			y[0].Set(0.f,0.f);


			float angle=toRad( (180.f-sensorAngle)/2.f );
			float angleDiff=toRad(sensorAngle/6.f);
			for(int i=0;i<7;i++)
			{
				y[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
				angle+=angleDiff;
			}	
	
			b2PolygonShape shape;
			shape.Set(y,8);
			//shape.SetAsBox(1.f,1.f);	
			fixture.shape=&shape;
			parentBody->CreateFixture(&fixture);
		}
				
	}

	int getSensorID()	{return sensorID;}
	void* getSensor() { return this; }

	
	virtual void objectIsInSensor(BaseObject* baseObj)
	{
		/*if(baseObj==NULL)	
		{
			printf("FUCK\n"); return;
		}*/
		if(baseObj->baseObjectID == GAMEOBJECTTYPE_MISSILE)	return;	// If this does not work, change objectID of missiles to something different, but consider the reusability of them
		
		objectMap.insert(std::pair<GLuint,b2Body*>(baseObj->getObjectID(),baseObj->body));
			//printf("Start!! Size: %i \n",objectMap.size());
		//objectMap.insert(std::pair<GLuint,GLuint>(baseObj->getObjectID(),baseObj->baseObjectID));
	}
	/*

		Use objectList get***Funktions to get the object in the sensor area and only save the id's

	*/
	virtual void objectLeftSensor(BaseObject* baseObj)
	{
		if(baseObj->baseObjectID == GAMEOBJECTTYPE_MISSILE)	return;

		GLuint id = baseObj->baseObjectID;

		objectMap.erase(baseObj->getObjectID());

	}

	bool isInSensor(GLuint objectID)
	{
		if(objectMap.count(objectID) > 0)	return true;
		else return false;

		/*
		objectIDMap::iterator it;

		it = objectMap.find(objectID);

		if(it != objectMap.end()) return true;

		else return false;
		*/
	}

private:
	GLuint sensorID; // body specific sensor ID

	
	typedef std::map<GLuint,b2Body*> objectIDMap;
	objectIDMap objectMap;
	//std::vector<b2Body*> objectList;


	int testInt;
};


class MissileSensor : public Sensor	// senses and saves incoming missiles
{
public:
	MissileSensor() {testInt=22;}
	~MissileSensor() {}


	
	void objectIsInSensor(BaseObject* baseObj)
	{
		/*if(baseObj==NULL)	
		{
			printf("FUCK\n"); return;
		}*/
		if(baseObj->baseObjectID != GAMEOBJECTTYPE_MISSILE)	return;	// If this does not work, change objectID of missiles to something different, but consider the reusability of them
			objectMap.insert(std::pair<GLuint,b2Body*>(baseObj->getObjectID(),baseObj->body));
			printf("Start!! Size: %i \n",objectMap.size());
		//objectMap.insert(std::pair<GLuint,GLuint>(baseObj->getObjectID(),baseObj->baseObjectID));
	}
	/*

		Use objectList get***Funktions to get the object in the sensor area and only save the id's

	*/
	void objectLeftSensor(BaseObject* baseObj)
	{
		if(baseObj->baseObjectID != GAMEOBJECTTYPE_MISSILE)	return;

		GLuint id = baseObj->baseObjectID;

		objectMap.erase(baseObj->getObjectID());

		printf("End! Size: %i \n",objectMap.size());
	}

	bool isInSensor(GLuint objectID)
	{
		if(objectMap.count(objectID) > 0)	return true;
		else return false;

		/*
		objectIDMap::iterator it;

		it = objectMap.find(objectID);

		if(it != objectMap.end()) return true;

		else return false;
		*/
	}

private:
	GLuint sensorID; // body specific sensor ID

	
	typedef std::map<GLuint,b2Body*> objectIDMap;
	objectIDMap objectMap;
	//std::vector<b2Body*> objectList;


	int testInt;
};