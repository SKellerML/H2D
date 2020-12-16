#include "LevelContactListener.h"
#include "pObject.h"
#include "Sound.h"
#include "BaseObject.h"


LevelContactListener::LevelContactListener(void)
{
}


LevelContactListener::~LevelContactListener(void)
{
}

void LevelContactListener::BeginContact(b2Contact* contact)
{
	//b2Fixture* fixtureA= contact->GetFixtureA();	// A is set to be the sensor later
	//b2Fixture* fixtureB= contact->GetFixtureB();

	//// Check for sensors
	//bool sensor=false;
	//if(fixtureA->IsSensor())	sensor=true;
	//else if(fixtureB->IsSensor())	
	//{
	//	sensor=true;
	//	std::swap(fixtureA,fixtureB);
	//}
	//
	//if(sensor)
	//{
	//	Sensor* sensorObject = (Sensor*)fixtureA->GetUserData();
	//	BaseObject* object2 = (BaseObject*)fixtureB->GetBody()->GetUserData();
	//	
	//	sensorObject->objectIsInSensor(object2);
	//	/*
	//	GLuint sensorObjectType=objectSensor->baseObjectID;
	//	if( sensorObjectType == GAMEOBJECTTYPE_SHIP || sensorObjectType == GAMEOBJECTTYPE_PLAYER )
	//	{
	//		Ship* s = (Ship*)objectSensor;
	//		s->isInSensor(fixtureB->GetBody());
	//		printf("Sensor!\n");
	//	}
	//	*/
	//}


	/*
	handle begin event
	*/
}
void LevelContactListener::EndContact(b2Contact*contact)
{
	//b2Fixture* fixtureA= contact->GetFixtureA();	// A is set to be the sensor later
	//b2Fixture* fixtureB= contact->GetFixtureB();

	//// Check for sensors
	//bool sensor=false;
	//if(fixtureA->IsSensor())	sensor=true;
	//else if(fixtureB->IsSensor())	
	//{
	//	sensor=true;
	//	std::swap(fixtureA,fixtureB);
	//}
	//
	//if(sensor)
	//{
	//	int fixtureID = *(int*)fixtureB->GetUserData();
	//	if(fixtureID == 7) return;
	//	Sensor* sensorObject = (Sensor*)fixtureA->GetUserData();
	//	BaseObject* object2 = (BaseObject*)fixtureB->GetBody()->GetUserData();
	//	
	//	sensorObject->objectLeftSensor(object2);
	//	/*
	//	GLuint sensorObjectType=objectSensor->baseObjectID;
	//	if( sensorObjectType == GAMEOBJECTTYPE_SHIP || sensorObjectType == GAMEOBJECTTYPE_PLAYER )
	//	{
	//		Ship* s = (Ship*)objectSensor;
	//		s->isInSensor(fixtureB->GetBody());
	//		printf("Sensor!\n");
	//	}
	//	*/
	//}

	/*
	handle end event
	*/
}
void LevelContactListener::PreSolve(b2Contact*contact, const b2Manifold* oldManifold)
{


	/*
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Body* bodyA = fixtureA->GetBody();
		b2Fixture* fixtureB = contact->GetFixtureA();
		b2Body* bodyB = fixtureA->GetBody();

		if(contact->IsTouching())
		{
			// Do stuff
		}

		//void *x = bbb->GetUserData();

		//pObject* obj = (pObject*)bbb->GetUserData();

		//printf("User Data: %i \n",obj->getMaterialType());
		//pObject::getWorld()->

	/*
	handle pre-solveevent
	*/
}
void LevelContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse* impulse)
{
	b2WorldManifold* manifold = new b2WorldManifold();
	contact->GetWorldManifold(manifold);

	// Object ID's
	int* objIDA = (int*)contact->GetFixtureA()->GetUserData().pointer;
	int* objIDB = (int*)contact->GetFixtureB()->GetUserData().pointer;



	if (objIDA != nullptr && objIDB != nullptr)
	{

		BaseObject* bbA = (BaseObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		BaseObject* bbB = (BaseObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
		// Particle Hit
		if (*objIDB == GAMEOBJECTTYPE_PARTICLE)
		{
			std::swap(bbA, bbB);
			std::swap(objIDB, objIDA);
		}

		if (*objIDA == GAMEOBJECTTYPE_PARTICLE)
		{
			if(bbB != nullptr) bbB->isHit(&HitData(0, impulse->normalImpulses, 1.f), manifold->points[1], 0);
		}


		if (bbB != nullptr && bbA != nullptr)
		{
			
		}
	}
	// Ignore Particles here!


	//int* objTypeA = (int*)contact->GetFixtureA()->GetUserData();
	//int* objTypeB = (int*)contact->GetFixtureB()->GetUserData();
	//
	//if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())	return;

	//BaseObject* baseA = (BaseObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	//BaseObject* baseB = (BaseObject*)contact->GetFixtureB()->GetBody()->GetUserData();	
	//
	//
	//if(contact->IsTouching())
	//{		
	//	// Missile Impact
	//	if((GLuint)baseA->baseObjectID == GAMEOBJECTTYPE_MISSILE )
	//	{
	//		
	//		Missile* missile = (Missile*)baseA;
	//		HitData* hd=missile->getImpactData(true);
	//		b2WorldManifold manifold;
	//		contact->GetWorldManifold(&manifold);
	//		
	//		if(hd!=NULL)	baseB->isHit(hd,manifold.points[0],*(GLuint*)contact->GetFixtureB()->GetUserData());
	//						
	//	}
	//	else if((GLuint)baseB->baseObjectID == GAMEOBJECTTYPE_MISSILE )
	//	{
	//		Missile* missile = (Missile*)baseB;
	//		HitData* hd=missile->getImpactData(true);
	//		b2WorldManifold manifold;
	//		contact->GetWorldManifold(&manifold);
	//		if(hd!=NULL)	baseA->isHit(hd,manifold.points[0],*(GLuint*)contact->GetFixtureA()->GetUserData());
	//	}
	//}


	//printf("Collision! %i || %i \n",(int)baseA->baseObjectID,(int)baseB->baseObjectID);

	//if(*objTypeA == GAMEOBJECTTYPE_ENTITY)	baseA = (Entity*) contact->GetFixtureA()->GetBody()->GetUserData();
	//else return;




	/*
	float x = *impulse->normalImpulses;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Body* bodyA = fixtureA->GetBody();
	b2Fixture* fixtureB = contact->GetFixtureA();
	b2Body* bodyB = fixtureA->GetBody();

	if(x > .1f)
	{
		printf("Impulse: %f \n",x);
	}

	if(contact->IsTouching())
	{
		pObject* A = (pObject*)bodyA->GetUserData();
		
		if(A->collision())
		{
			pObject* B = (pObject*)bodyB->GetUserData();
			B->collision();
		}
	}
	/*
	handle post-solve event
	*/
}