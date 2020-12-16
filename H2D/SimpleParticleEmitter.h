#pragma once

#include "OpenGLH.h"
#include "TickCounter.h"
#include "ParticleProgram.h"
#include "ComplexTexturedParticleProgram.h"
#include "ComplexPlainParticleProgram.h"
#include "BaseObject.h"
#include "RayCastCallbacks.h"

#include <glm\gtx\transform.hpp>
#include <vector>
#include <random>

#define MAX_PARTICLE_COUNT 8000
#define MAX_PARTICLE_COUNT_PER_EMITTER 8000

#define toAngle(rad) (rad*180)/(b2_pi)
#define toRad(a) (a*b2_pi)/180 

class ParticleEmitter
{
public:
	virtual void renderParticles(b2Vec2 renderPos = b2Vec2(0.f, 0.f), GLfloat angle = 0.f, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f)) = 0;
	virtual void deleteEmitter()=0;
	virtual bool isActive()=0;
	virtual void update()=0;

	virtual void setParticleColor(Color4f startColor,Color4f endColor=Color4f(1.f,1.f,1.f,1.f))=0;
	virtual void setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction) = 0;

	void setEmittingData(bool isEmitting, GLfloat emittedParticleModifier = 1.f)	{
		m_isEmitting = isEmitting;
		m_emittedParticleModifier = emittedParticleModifier;
	}

protected:
	bool m_isEmitting;
	GLfloat m_emittedParticleModifier;
};



class SimpleParticleEmitter : public ParticleEmitter
{
public:
	SimpleParticleEmitter(void);
	~SimpleParticleEmitter(void);

	static void loadParticleProgram();

	void createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, bool particleRotation=true, bool ongoingEmitting=false, b2Vec2 direction=b2Vec2(0.f,0.f), GLuint particlesPerSecond=0);
	void setParticleColor(Color4f startColor,Color4f endColor=Color4f(1.f,1.f,1.f,1.f));
	void renderParticles(b2Vec2 renderPos = b2Vec2(0.f, 0.f), GLfloat angle = 0.f, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f));
	void deleteEmitter();
	void setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction);
	bool isActive();

	void update();

	static bool addParticles(GLuint count);
	static bool removeParticles(GLuint count);

private:
	static GLuint particleCount;

	static ParticleProgram particleProgram;
	b2Vec2 worp;

	bool active;
	bool m_ongoingEmitting;

	b2Vec2 renderPosition;
	b2Vec2 m_emitterVelocity;

	GLuint vbo_vel,vbo_angle,vbo_time;
	GLuint vao;

	Color4f m_startColor, m_endColor;

	GLfloat previousV;

	b2Vec2 m_emitterPosition;

	GLuint m_maxEmittedParticles;
	GLuint m_emittedParticles;

	TickCounter timer;

	GLfloat m_maxLifeTime;
	GLfloat m_minLifeTime;

};




struct ParticleData{
	b2Vec3 speed;	// speed = vX,vY,vAngular
	double maxParticleLife;
	double life; // Remaining life of the particle. if < 0 : dead and unused.

};

struct TextureCoordinateContainer
{
	b2Vec2 tc0;
	b2Vec2 tc1;
	b2Vec2 tc2;
	b2Vec2 tc3;
};

struct ParticleTextureData
{
	Texture2D texture;
	GLuint numberOfSprites;
	std::vector<TextureCoordinateContainer> textureCoordinates;
};



class ComplexTexturedParticleEmitter : public ParticleEmitter
{
	public:
	ComplexTexturedParticleEmitter(void);
	~ComplexTexturedParticleEmitter(void);

	static void loadParticleProgram();

	void createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, bool collisions=false, bool particleRotation=true, bool ongoingEmitting=false, b2Vec2 direction=b2Vec2(0.f,0.f), GLuint particlesPerSecond=0);
	void setParticleColor(Color4f startColor,Color4f endColor);
	void renderParticles(b2Vec2 renderPos = b2Vec2(0.f, 0.f), GLfloat angle = 0.f, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f));
	void deleteEmitter();
	void setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction);
	bool isActive();

	void update();

	static bool addParticles(GLuint count);
	static bool removeParticles(GLuint count);

private:
	static GLuint particleCount;

	static ComplexTexturedParticleProgram complexParticleProgram;
	
	static HitRayCastCallback hitRayCastCallback;

	std::vector<b2Vec2> particleVertexContainer;
	TextureCoordinateContainer particleTextureContainer;
	std::vector<glm::vec4> particlePositionContainer;
	
	std::vector<ParticleData> particleDataContainer;
	/*
	particleVertexContainer;
	particleTextureContainer;
	particlePositionContainer;
	particleDataContainer;
	*/
	GLuint vertexArray;
	GLuint vertex_vbo;
	GLuint texCoord_vbo;
	GLuint position_vbo;
	GLuint information_vbo;

	GLfloat lastTime;


	// Texture
	static std::vector<ParticleTextureData> particleTextureDataContainer;

	b2Vec2 m_emitterDirection;
	GLfloat m_maxParticleVelocity;

	bool active;
	bool m_ongoingEmitting;

	b2Vec2 renderPosition;
	b2Vec2 m_emitterVelocity;

	//Color4f m_startColor, m_endColor;

	b2Vec2 m_emitterPosition;

	GLuint m_maxEmittedParticles;
	GLuint m_emittedParticles;
	
	bool m_collision;


	TickCounter timer;

	GLfloat m_maxLifeTime;
	GLfloat m_minLifeTime;
};



class ComplexPlainParticleEmitter : public ParticleEmitter
{
	public:
	ComplexPlainParticleEmitter(void);
	~ComplexPlainParticleEmitter(void);

	static void loadParticleProgram();

	void createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, b2Vec2 particleSize, bool collision=false,bool particleRotation=true, bool ongoingEmitting=false, b2Vec2 direction=b2Vec2(0.f,0.f), GLuint particlesPerSecond=0);
	void setParticleColor(Color4f startColor,Color4f endColor);
	void renderParticles(b2Vec2 renderPos = b2Vec2(0.f, 0.f), GLfloat angle = 0.f, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f));
	void deleteEmitter();
	void setPosition(b2Body* body,b2Vec2 positionOffset,b2Vec2 direction);
	bool isActive();

	void update();

	static bool addParticles(GLuint count);
	static bool removeParticles(GLuint count);

private:
	static GLuint particleCount;

	static ComplexPlainParticleProgram complexParticleProgram;
	
	static HitRayCastCallback hitRayCastCallback;

	std::vector<b2Vec2> particleVertexContainer;

	std::vector<glm::vec4> particlePositionContainer;
	
	std::vector<ParticleData> particleDataContainer;
	/*
	particleVertexContainer;
	particleTextureContainer;
	particlePositionContainer;
	particleDataContainer;
	*/
	GLuint vertexArray;
	GLuint vertex_vbo;
	GLuint position_vbo;

	GLfloat lastTime;

	bool active;
	bool m_ongoingEmitting;

	// Texture
	static std::vector<ParticleTextureData> particleTextureDataContainer;


	b2Vec2 m_emitterDirection;
	
	GLfloat m_maxParticleVelocity;




	b2Vec2 renderPosition;
	b2Vec2 m_emitterVelocity;

	Color4f m_startColor, m_endColor;

	GLfloat previousV;

	b2Vec2 m_emitterPosition;

	GLuint m_maxEmittedParticles;
	GLuint m_emittedParticles;

	bool m_collision;

	TickCounter timer;

	GLfloat m_maxLifeTime;
	GLfloat m_minLifeTime;
};