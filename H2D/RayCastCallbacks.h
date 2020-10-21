#pragma once



#include "OpenGLH.h"
//#include "Player.h"

#include "BaseObject.h"

#include <Box2D\Box2D.h>



class LaserRayCastCallback : public b2RayCastCallback
{
public:
	LaserRayCastCallback(void);
	~LaserRayCastCallback(void);

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		if(fixture->IsSensor())// || fixture->GetFilterData().categoryBits == 0)
		{
			return m_fraction;
		}
		int* gameobjecttype = (int*)fixture->GetUserData();
		if (gameobjecttype == nullptr || *gameobjecttype == GAMEOBJECTTYPE_PARTICLE)
		{
			return -1;
		}

		
			m_fraction=fraction;
			impactPoint=point;
			impactNormal = normal;
			hitObject = (BaseObject*)fixture->GetBody()->GetUserData();

			hitFixtureUserData = *gameobjecttype;//*(GLuint*)fixture->GetUserData();

		//baseObj->isHit(m_weaponType);
		//printf("Hit\n");
		
		//ObjectBasePolymorphism* objb = (ObjectBasePolymorphism*) fixture->GetBody()->GetUserData();
		//Entity* objb = (Entity*) fixture->GetBody()->GetUserData();
		
		/*
		switch(objb->getID())
		{
		case GAMEOBJECT_ENTITY:	objb=	(Entity*) objb;
			break;
		}
		*/
		/*
		switch(typeid(objb).name())
		{

		}
		*/
		//objb->isHitByLaser();
		//objb->getSpriteSheet(0)->renderSprite(0.f,20.f,20.f);
		
		/*
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f( point.x,point.y );
		glEnd();
		*/
		/*
		std::cout << "Test: " << objb->testFunc() << "|||" <<std::endl;
		int u=objb->getID();
			printf("blabla! %s || %i \n",typeid(objb).name(),u);

		delete objb;
*/	
		return fraction;
	
	}

	b2Vec2 getImpactPoint()
	{
		b2Vec2 hp=impactPoint;
		impactPoint.Set(0.f,0.f);
		return hp;
	}
	b2Vec2 getImpactNormal()
	{
		b2Vec2 hp = impactNormal;
		impactPoint.Set(0.f, 0.f);
		return hp;
	}

	BaseObject* getHitObject()
	{
		return hitObject;
	};

	void resetLaser()
	{
		hitObject=NULL;
		m_fraction=1.f;
	}

	void setWeaponData(GLuint weaponType)
	{
		m_weaponType=weaponType;
	}

	GLuint getHitFixtureUserData()
	{
		return hitFixtureUserData;
	}

private:
	b2Vec2 impactPoint;
	b2Vec2 impactNormal;
	BaseObject* hitObject;

	// Weapon Data
	GLuint m_weaponType;
	GLfloat m_fraction;

	GLuint hitFixtureUserData;

	// attacking ship has to read the variable!
	
};

// Callback 2 -----------------------------------------------------------------------------------------------------------------

class HitRayCastCallback : public b2RayCastCallback
{
public:
	HitRayCastCallback(void)	{ collision = false; }
	~HitRayCastCallback(void)	{}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		if(fixture->IsSensor() || fixture->GetFilterData().categoryBits == 0)
		{
			return 1;
		}
		if( *(int*)fixture->GetUserData() == 7 )
		{
			return -1;
		}
			collision=true;
		return 0;
	
	}

	bool isColliding()
	{
		bool c=collision;
		collision=false;

		return c;
	}

private:
	bool collision;

	// Weapon Data


	// attacking ship has to read the variable!
	
};
