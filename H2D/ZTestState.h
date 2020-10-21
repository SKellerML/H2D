#pragma once

#include "OpenGLH.h"
#include "GameState.h"
#include "ParticleProgram.h"
#include "TickCounter.h"
#include <gtx\transform.hpp>
#include <Box2D\Box2D.h>

#include <vector>

#include "ComplexTexturedParticleProgram.h"

#include "Texture2D.h"

#define PARTICLE_COUNT 7
#define MAX_PARTICLES 5000

// CPU representation of a particle
struct ParticleInformation
{
	GLfloat x;
	GLfloat y;

	GLfloat s;
	GLfloat t;

	//b2Vec3 pos;		// pos = position and angle 
	//Color4f color;	// Color
};

struct Particle{
	b2Vec3 speed;	// speed = vX,vY,vAngular
    float life; // Remaining life of the particle. if < 0 : dead and unused.
};





class ZTestState : public GameState
{
public:
	ZTestState(void);
	~ZTestState(void);

	void init(GLuint levelType);
	void update();
	void renderBackground();
	void render();
	void updateRender();
	void renderFinal();

	int FindUnusedParticle();

private:
	ComplexTexturedParticleProgram particleProgram;

	Texture2D tex;

	GLuint vertexArray;
	GLuint vertex_vbo;
	GLuint texCoord_vbo;
	GLuint poscon;
	
	//GLuint color_vbo;

	std::vector<b2Vec2> particleVertexContainer;
	std::vector<b2Vec2> particleTextureContainer;
	std::vector<b2Vec3> positionContainer;
	//std::vector<b2Vec2> particleInformationContainer;
	std::vector<Particle> particleContainer;
	//Particle ParticlesContainer[MAX_PARTICLES];

	int LastUsedParticle;
};


 
