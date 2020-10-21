#pragma once

#include "OpenGLH.h"
#include "Animation.h"
#include "SimpleParticleEmitter.h"

enum EffectType
{
	EFFECT_EXPLOSION_SMALL,
	EFFECT_GAUSS_DISCHARGE,
	EFFECT_EXPLOSION_BIG,
};


class Effect
{
public:
	Effect(void);
	~Effect(void);

	void loadEffect(GLuint effectType, b2Body* parentBody,b2Vec2 offset= b2Vec2(0.f,0.f) );
	void loadEffect(GLuint effectType, b2Vec2 emitterPosition, b2Vec2 emitterVelocity, b2Vec2 offset, b2Vec2 direction=b2Vec2(0.f,0.f));
	void updateEffect(bool render);
	void renderEffect(b2Vec2 renderPos = b2Vec2(0.f,0.f),GLfloat angle=0.f,b2Vec2 rotationOffset=b2Vec2(0.f,0.f));
	void resetEffect();

	bool isFinished() {return !active;};

private:
	enum EmitterType
	{
		EMITTERTYPE_SIMPLE,
		EMITTERTYPE_COMPLEXTEXTURED,
		EMITTERTYPE_COMPLEXPLAIN,
	};

	Animation animation;
	GLfloat m_animationSpeed;
	ParticleEmitter* particleEmitter;

	bool containsAnimation;

	// Variables
	GLuint m_emitterType;
	GLfloat m_effectDuration;
	TickCounter effectTimer;
	
	b2Vec2 m_effectPosition;
	b2Vec2 m_effectVelocity;

	bool active;
	bool wasRendering;
};





enum StationaryEffectType
{
	EFFECT_STATIONARY_ENGINES_SMALL,
};

class StationaryEffect
{
public:
	StationaryEffect();
	~StationaryEffect();

	void loadEffect(GLuint effectType, b2Body* parentBody,b2Vec2 offset=b2Vec2(0.f,0.f));
	void loadEffect(GLuint effectType, b2Vec2 emitterPosition, b2Vec2 emitterVelocity, b2Vec2 offset, b2Vec2 direction);
	void updateEffect(bool emitting, b2Body* body, GLfloat emittedParticleModifier=1.f);
	void renderEffect(b2Vec2 renderPos = b2Vec2(0.f, 0.f), GLfloat angle = 0.f, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f));
private:
	enum EmitterType
	{
		EMITTERTYPE_SIMPLE,
		EMITTERTYPE_COMPLEXTEXTURED,
		EMITTERTYPE_COMPLEXPLAIN,
	};

	Animation animation;
	GLfloat m_animationSpeed;
	std::shared_ptr<ParticleEmitter> particleEmitter;
	b2Vec2 m_emitterOffset;

	// Variables
	GLuint m_emitterType;

	b2Vec2 m_particleDirectionAA;	// Particle Direction Axis Aligned
	TickCounter effectTimer;
	
	b2Vec2 m_effectPosition;

	bool active;
	bool wasRendering;
};