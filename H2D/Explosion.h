#pragma once

#include "BaseObject.h"
#include "Effect.h"
#include "OpenGLH.h"
#include "TickCounter.h"

#include <Box2D\Box2D.h>
#include <memory>
#include <vector>
#include <array>

#define maxParticles 40

class Explosion
{
public:
	Explosion();
	~Explosion();

	void createExplosion(std::shared_ptr<b2World> world, b2Vec2 pos)
	{
		if (isActive)	return;
		animPos = pos;
		printf("Boom!\n");
		world->SetGravity(b2Vec2(0.f, 0.f));

		b2CircleShape* shape = new b2CircleShape();
		shape->m_radius = .1f;
		GLfloat blastPower = 10.f;
		for (int i = maxParticles-1; i>=0; --i)
		{
			GLfloat ang = toRad(360.f / maxParticles*i);
			b2BodyDef def;
			def.type = b2_dynamicBody;
			def.position = pos;

			def.fixedRotation = true; // rotation not necessary
			def.bullet = true; // prevent tunneling at high speed
			def.linearDamping = 2; // drag due to moving through air
			def.linearVelocity = blastPower * b2Vec2(sin(ang), cos(ang));
			bodyContainer[i] = world->CreateBody(&def);


			b2FixtureDef fd;
			fd.filter.groupIndex = -1;
			fd.filter.categoryBits = COLLISIONOBJECTTYPE_PARTICLE;
			//fd.filter.maskBits = 
			fd.density = 2.0f;
			fd.restitution = 0.99f;
			fd.shape = shape;
			fd.friction = 0;
			fd.userData.pointer = uintptr_t(&objectID);

			bodyContainer[i]->CreateFixture(&fd);
		}
		timer.start();
		isActive = true;
		expEffect.loadEffect(EFFECT_EXPLOSION_BIG, pos, b2Vec2(0.f, 0.f), b2Vec2(0.f, 0.f));// loadAnimation(ANIMATION_EXPLOSION_1);
	}

	bool updateExplosion()
	{
		if (isActive)	expEffect.updateEffect(true);
		if (isActive && expEffect.isFinished())//timer.hasPassed(1))
		{
			
			b2World* w = bodyContainer[0]->GetWorld();
			for (int i = maxParticles-1; i; --i)
			{
				w->DestroyBody(bodyContainer[i]);
			}
			isActive = false;
			return true;
		}
		return false;
	}

	void render()
	{
		if (isActive) expEffect.renderEffect();
	}

private:
	TickCounter timer;
	b2Body* bodyContainer[maxParticles];
	bool isActive;
	Effect expEffect;
	b2Vec2 animPos;

	static int objectID;
};

