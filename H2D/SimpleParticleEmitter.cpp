#include "SimpleParticleEmitter.h"

GLuint SimpleParticleEmitter::particleCount=0;
ParticleProgram SimpleParticleEmitter::particleProgram;

void SimpleParticleEmitter::loadParticleProgram()
{
	particleProgram.loadProgram();

	particleProgram.bind();

	particleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	particleProgram.updateProjectionMatrix();

	particleProgram.setModelViewMatrix(glm::mat4());
	particleProgram.updateModelViewMatrix();
}

SimpleParticleEmitter::SimpleParticleEmitter(void)
{
	active=false;
	worp=b2Vec2(0.f,0.f);
}


SimpleParticleEmitter::~SimpleParticleEmitter(void)
{
}

bool SimpleParticleEmitter::addParticles(GLuint count)
{
	particleCount+=count;
	if(particleCount > MAX_PARTICLE_COUNT)
	{
		particleCount-=count;
		return false;
	}
	else
	{
		return true;
	}
	return true;
}
bool SimpleParticleEmitter::removeParticles(GLuint count)
{
	particleCount-=count;
	if(particleCount < 0)	particleCount=0;
	return true;
}



void SimpleParticleEmitter::createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, bool particleRotation, bool ongoingEmitting, b2Vec2 direction, GLuint particlesPerSecond)
{
	if(active) return;

	active=true;

	m_ongoingEmitting=ongoingEmitting;
	m_maxEmittedParticles=maxEmittedParticles;
	m_emitterPosition=emitterPosition;
	m_emitterVelocity=emitterVelocity;

	m_maxLifeTime=maxLifetime;

	std::vector<float> vv;
	//float vv[PARTICLE_COUNT * 3]; // start velocities vec3
	std::vector<float> angleV;
	//float angle[PARTICLE_COUNT * 2];
	std::vector<float> vt;
	//float vt[PARTICLE_COUNT * 2]; // start times
	
	float t_accum = TickCounter::getEngineTime(); // start time

	if(m_maxEmittedParticles > MAX_PARTICLE_COUNT_PER_EMITTER)	m_maxEmittedParticles=MAX_PARTICLE_COUNT_PER_EMITTER;

	if(!SimpleParticleEmitter::addParticles(m_maxEmittedParticles))
	{
		printf("Number of Particles too high!\n");
		return;
	}

	for (int i = 0; i < maxEmittedParticles; i++) {
		

		GLfloat vX,vY;
		/*
		vX=100*(((float)rand() / (float)RAND_MAX) * maxParticleVelocity.x - maxParticleVelocity.x/2);// +emitterVelocity.x/2);
		//vX=100*(((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f) + (emitterVelocity.x*100)/TICKS_PER_SECOND;
		vY=100*(((float)rand() / (float)RAND_MAX) * maxParticleVelocity.y - maxParticleVelocity.y/2);// + emitterVelocity.y/2);
		*/


		if(direction.x == 0.f && direction.y == 0.f)
		{
			GLfloat tt = 2*b2_pi*(rand()/ (float)RAND_MAX);
			GLfloat uu = maxParticleVelocity*(rand()/ (float)RAND_MAX)+(rand()/ (float)RAND_MAX);
			GLfloat rt = uu>maxParticleVelocity ? 2*maxParticleVelocity-uu : uu;
			vX=rt*cos(tt)*100;
			vY=rt*sin(tt)*100;
		}
		else
		{
			vX = direction.x * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
			vY = direction.y * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
		}

		vv.push_back(vX);
		vv.push_back(vY);		
		// start velocities. randomly vary x and z components
		//float randx = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
		//float randz = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;

		//vv[j] = randx*100.f; // x
		//vv[j + 1] = randz*100.f; // y
		//vv[j + 2] = 0.f; // z

		// start times
		vt.push_back(t_accum + 0.01f); // spacing for start times is 0.01 seconds
		vt.push_back(((float)rand()/(float)RAND_MAX)*m_maxLifeTime);	// Lifetime

		if(particleRotation)
		{
			angleV.push_back(((float)rand() / (float)RAND_MAX) *b2_pi);
			angleV.push_back(((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f);
		}
		else
		{
			angleV.push_back(0.f);
			angleV.push_back(0.f);
		}


	}

	glGenBuffers (1, &vbo_vel);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_vel);
	glBufferData (GL_ARRAY_BUFFER, vv.size()*sizeof(float) /*sizeof (vv)*/, &vv[0], GL_STATIC_DRAW);


	glGenBuffers (1, &vbo_angle);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_angle);
	glBufferData (GL_ARRAY_BUFFER, angleV.size() * sizeof(float), &angleV[0], GL_STATIC_DRAW);

	glGenBuffers (1, &vbo_time);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_time);
	glBufferData (GL_ARRAY_BUFFER, vt.size() * sizeof(float), &vt[0], GL_STATIC_DRAW);


	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_vel);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_angle);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_time);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	glEnableVertexAttribArray (2);


	
	particleProgram.bind();
	particleProgram.setElapsedTime((GLfloat)TickCounter::getEngineTime());
	particleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	particleProgram.updateProjectionMatrix();

	particleProgram.setModelViewMatrix(glm::mat4());
	particleProgram.updateModelViewMatrix();

	renderPosition.Set( (m_emitterPosition.x)*100-50*m_emitterVelocity.x*1/TICKS_PER_SECOND , (m_emitterPosition.y)*100-50*m_emitterVelocity.y*1/TICKS_PER_SECOND);
	timer.start();
}

void SimpleParticleEmitter::setParticleColor(Color4f startColor,Color4f endColor)
{
	m_startColor=startColor;
	m_endColor=endColor;
}

void SimpleParticleEmitter::renderParticles(b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset)
{
	if(!active) return;

	/* Render Particles. Enabling point re-sizing in vertex shader */
	glEnable (GL_PROGRAM_POINT_SIZE);

	particleProgram.bind();

	particleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(renderPosition.x+worp.x,renderPosition.y+worp.y,0.f)));

	// Translate and rotate
	if (renderPos.x != 0.f || renderPos.y != 0.f || angle != 0.f)
	{
		
		if (rotationOffset.x != 0.f || rotationOffset.y != 0.f)
		{
			particleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(rotationOffset.x, rotationOffset.y, 0.f)));
			particleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
			particleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rotationOffset.x, -rotationOffset.y, 0.f)));
			particleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(renderPos.x, renderPos.y, 0.f)));
		}
		else
		{
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
			particleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(renderPos.x, renderPos.y, 0.f)));
			particleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rotationOffset.x, -rotationOffset.y, 0.f)));
			particleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
			particleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(+rotationOffset.x, +rotationOffset.y, 0.f)));
		}
	}

	/* update time in shaders */
	particleProgram.setElapsedTime((GLfloat)TickCounter::getEngineTime()+0.01f);
	particleProgram.setOngoingEmitting(m_ongoingEmitting);
	particleProgram.setColour(m_startColor,m_endColor);

	worp=BaseObject::getWorldPos();
	

	//particleProgram.setModelViewMatrix(glm::translate<GLfloat>((m_emitterPosition.x+worp.x/*BaseObject::getWorldPos().x*/)*100 , (m_emitterPosition.y+/*BaseObject::getWorldPos().y*/worp.y)*100 ,0.f));//m_emitterPosition.x,m_emitterPosition.y,0.f));
	particleProgram.updateModelViewMatrix();
	
	previousV=m_emitterVelocity.y*timer.getTime()/2;
	//printf("Pos: %f \n",(m_emitterPosition.y+BaseObject::getWorldPos().y)*100);

	//glUniform1f(elapsed_system_time_loc, (GLfloat)current_seconds);

	glBindVertexArray (vao);

	// draw points 0-3 from the currently bound VAO with current in-use shader

	glDrawArrays (GL_POINTS, 0, m_maxEmittedParticles);

	glBindVertexArray (NULL);

	//glDisable (GL_BLEND);
	//glDisable (GL_PROGRAM_POINT_SIZE);
}

void SimpleParticleEmitter::update()
{

	renderPosition.x+=50*m_emitterVelocity.x*1/TICKS_PER_SECOND;
	renderPosition.y+=50*m_emitterVelocity.y*1/TICKS_PER_SECOND;
	//printf("Pos: %f || %f || %f \n",(m_emitterVelocity.y*timer.getTime()/2)*100,(m_emitterPosition.y)*100,(m_emitterPosition.y+/*BaseObject::getWorldPos().y*/worp.y+m_emitterVelocity.y*timer.getTime()/2)*100 );
	if(!m_ongoingEmitting &&  timer.hasPassed(m_maxLifeTime+1.f))	deleteEmitter();
}

void SimpleParticleEmitter::deleteEmitter()
{
	if(active)
	{
		active=false;

		glDeleteBuffers(1,&vbo_vel);
		glDeleteBuffers(1,&vbo_angle);
		glDeleteBuffers(1,&vbo_time);

		removeParticles(m_maxEmittedParticles);
	}
}

void SimpleParticleEmitter::setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction)
{

	if(!m_ongoingEmitting)	return;
	m_emitterPosition=body->GetPosition();
	renderPosition.Set( (m_emitterPosition.x)*100-50*m_emitterVelocity.x*1/TICKS_PER_SECOND , (m_emitterPosition.y)*100-50*m_emitterVelocity.y*1/TICKS_PER_SECOND);
}

bool SimpleParticleEmitter::isActive()
{
	return active;
}

/*
	Things to consider: 
		parent Velocity
		other Stuff
*/











/*
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/



GLuint ComplexTexturedParticleEmitter::particleCount=0;
ComplexTexturedParticleProgram ComplexTexturedParticleEmitter::complexParticleProgram;
std::vector<ParticleTextureData> ComplexTexturedParticleEmitter::particleTextureDataContainer;
HitRayCastCallback ComplexTexturedParticleEmitter::hitRayCastCallback;

void ComplexTexturedParticleEmitter::loadParticleProgram()
{
	complexParticleProgram.loadProgram();

	complexParticleProgram.bind();

	complexParticleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	complexParticleProgram.updateProjectionMatrix();

	complexParticleProgram.setModelViewMatrix(glm::mat4());
	complexParticleProgram.updateModelViewMatrix();


	// Particle Texture Data
	ParticleTextureData textureData;
	textureData.texture.loadTextureFromFile32("ParticleAtlas.png");

	GLfloat texWidth=(float)textureData.texture.getImgWidth();
	GLfloat texHeight=(float)textureData.texture.getImgHeight();
	GLfloat spriteWidth = (float)texWidth/8;
	GLfloat spriteHeight = (float)texHeight/8;

	

	GLfloat posX=0.f,posY=0.f;

	TextureCoordinateContainer tcc;
	/*
	tcc.tc0 = b2Vec2( 0.f , 0.f );
	tcc.tc1 = b2Vec2( 1.f , 0.f );
	tcc.tc2 = b2Vec2( 1.f , 1.f );
	tcc.tc3 = b2Vec2( 0.f , 1.f );
	textureData.textureCoordinates.push_back(tcc);
	*/
	for(int row=0 ; row < 8 ; row++)
	{
		posX=0.f;

		for(int column=0 ; column < 8 ; column++)
		{
			
			tcc.tc0 = b2Vec2( posX/texWidth , posY/texHeight );
			tcc.tc1 = b2Vec2( (posX+spriteWidth)/texWidth , posY/texHeight );
			tcc.tc2 = b2Vec2( (posX+spriteWidth)/texWidth , (posY+spriteHeight)/texHeight );
			tcc.tc3 = b2Vec2( posX/texWidth , (posY+spriteHeight)/texHeight );

			textureData.textureCoordinates.push_back(tcc);

			posX+=spriteWidth;
		}

		posY+=spriteHeight;
	}
	textureData.numberOfSprites=64;


	//textureData.texture.~Texture2D();
	particleTextureDataContainer.push_back(textureData);
	particleTextureDataContainer[0].texture.loadTextureFromFile32("ParticleAtlas.png");
	/*
		texLeft=clip->x/((float)mTextureWidth);
		texRight=(clip->x+clip->w)/((float)mTextureWidth);

		texTop=(clip->y+clip->h)/((float)mTextureHeight);
		texBottom=clip->y/((float)mTextureHeight);


		quadPos[ 0 ].texCoord.s = texLeft; quadPos[ 0 ].texCoord.t =texBottom;
		quadPos[ 1 ].texCoord.s =texRight; quadPos[ 1 ].texCoord.t =texBottom; 		
		quadPos[ 2 ].texCoord.s =texRight; quadPos[ 2 ].texCoord.t =   texTop;		
		quadPos[ 3 ].texCoord.s = texLeft; quadPos[ 3 ].texCoord.t =   texTop; 
	*/

}

ComplexTexturedParticleEmitter::ComplexTexturedParticleEmitter(void)
{
	active=false;
}


ComplexTexturedParticleEmitter::~ComplexTexturedParticleEmitter(void)
{
}

bool ComplexTexturedParticleEmitter::addParticles(GLuint count)
{
	particleCount+=count;
	if(particleCount > MAX_PARTICLE_COUNT)
	{
		particleCount-=count;
		return false;
	}
	else
	{
		return true;
	}
	return true;
}
bool ComplexTexturedParticleEmitter::removeParticles(GLuint count)
{
	particleCount-=count;
	if(particleCount < 0)	particleCount=0;
	return true;
}



void ComplexTexturedParticleEmitter::createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, bool collisions, bool particleRotation, bool ongoingEmitting, b2Vec2 direction, GLuint particlesPerSecond)
{
	if(active) return;
	
	active=true;
	
	m_maxEmittedParticles=maxEmittedParticles;
	m_maxLifeTime=maxLifetime;
	m_emitterVelocity=emitterVelocity;
	m_maxParticleVelocity=maxParticleVelocity;

	m_ongoingEmitting=ongoingEmitting;
	
	m_emitterPosition=emitterPosition;

	b2Vec2 v=m_emitterVelocity;
	v*=(1.f/(TICKS_PER_SECOND*2));
	m_emitterPosition-=v;

	m_collision=collisions;

	// Save all 4 Vertices

	particleVertexContainer.reserve(4);
	particleVertexContainer.push_back(b2Vec2( -50.f , -50.f ));
	particleVertexContainer.push_back(b2Vec2( 50.f , -50.f ));
	particleVertexContainer.push_back(b2Vec2( 50.f , 50.f ));
	particleVertexContainer.push_back(b2Vec2( -50.f , 50.f ));

	
	particlePositionContainer.reserve(m_maxEmittedParticles);
	particleDataContainer.reserve(m_maxEmittedParticles);
	
	float t_accum = TickCounter::getEngineTime(); // start time

	if(m_maxEmittedParticles > MAX_PARTICLE_COUNT_PER_EMITTER)	m_maxEmittedParticles=MAX_PARTICLE_COUNT_PER_EMITTER;

	particleTextureContainer = particleTextureDataContainer[0].textureCoordinates[floor( (rand()/ (float)RAND_MAX)*64 )];

	if(!ComplexTexturedParticleEmitter::addParticles(m_maxEmittedParticles))
	{
		printf("Number of Particles too high!\n");
		return;
	}
	ParticleData currentParticle;

	for (int i = 0; i < maxEmittedParticles; i++) {

		GLfloat posAngle;
		GLfloat vX,vY,vAngular;


		// Speed
		if(direction.x == 0.f && direction.y == 0.f)
		{
			GLfloat tt = 2*b2_pi*(rand()/ (float)RAND_MAX);
			GLfloat uu = maxParticleVelocity*(rand()/ (float)RAND_MAX)+(rand()/ (float)RAND_MAX);
			GLfloat rt = uu>maxParticleVelocity ? 2*maxParticleVelocity-uu : uu;
			vX=rt*cos(tt)*100;
			vY=rt*sin(tt)*100;
		}
		else
		{
			vX = direction.x * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
			vY = direction.y * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
		}
		
		vX+=m_emitterVelocity.x * 50;
		vY+=m_emitterVelocity.y * 50;

		// Rotation
		if(particleRotation)
		{
			vAngular = ((float)rand() / (float)RAND_MAX) *b2_pi;
			posAngle = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
		}
		else
		{
			vAngular=0.f;
			posAngle = 0.f;
		}
		currentParticle.speed=b2Vec3(vX,vY,toAngle(vAngular/TICKS_PER_SECOND));


		currentParticle.maxParticleLife=((float)rand()/(float)RAND_MAX)*m_maxLifeTime;
		currentParticle.life=currentParticle.maxParticleLife;


		// Position
		particlePositionContainer.push_back(glm::vec4(emitterPosition.x*100.f-vX/TICKS_PER_SECOND,emitterPosition.y*100.f-vY/TICKS_PER_SECOND,posAngle,1.f));

		// start times
		//vt.push_back(t_accum + 0.01f); // spacing for start times is 0.01 seconds
		//vt.push_back(((float)rand()/(float)RAND_MAX)*m_maxLifeTime);	// Lifetime
		particleDataContainer.push_back(currentParticle);		
	}

	glGenBuffers (1, &vertex_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData (GL_ARRAY_BUFFER, particleVertexContainer.size() * (sizeof( b2Vec2 )), &particleVertexContainer[0], GL_STATIC_DRAW);

	glGenBuffers (1, &position_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, position_vbo);
	glBufferData (GL_ARRAY_BUFFER, particlePositionContainer.size() * (sizeof( glm::vec4 )) , &particlePositionContainer[0], GL_STREAM_DRAW);

	glGenBuffers (1, &texCoord_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, texCoord_vbo);
	glBufferData (GL_ARRAY_BUFFER, (sizeof( b2Vec2 )*4), &particleTextureContainer, GL_STREAM_DRAW);

	glGenVertexArrays (1, &vertexArray);
	glBindVertexArray (vertexArray);

	//glEnableVertexAttribArray (0);
	//glEnableVertexAttribArray (1);
	//glEnableVertexAttribArray (2);

	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2),	0);

	glBindBuffer(GL_ARRAY_BUFFER,position_vbo);
	glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4),	0);
	
	glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2),	0);

	glVertexAttribDivisor(0,0);	// Vertex
	glVertexAttribDivisor(1,1); // Position
	//glVertexAttribDivisor(2,0); // TexCoord

	glBindVertexArray (NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	
	complexParticleProgram.bind();
	//complexParticleProgram.setElapsedTime((GLfloat)TickCounter::getEngineTime());
	complexParticleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	complexParticleProgram.updateProjectionMatrix();

	complexParticleProgram.setModelViewMatrix(glm::mat4());
	complexParticleProgram.updateModelViewMatrix();
	
	renderPosition.Set( (m_emitterPosition.x)*100-50*m_emitterVelocity.x*1/TICKS_PER_SECOND , (m_emitterPosition.y)*100-50*m_emitterVelocity.y*1/TICKS_PER_SECOND);
	timer.start();

	lastTime=TickCounter::getEngineTime();
}

void ComplexTexturedParticleEmitter::setParticleColor(Color4f startColor,Color4f endColor)
{
	//m_startColor=startColor;
	//m_endColor=endColor;
}


void ComplexTexturedParticleEmitter::update()
{
	if(!active) return;
	if(!m_ongoingEmitting &&  timer.hasPassed(m_maxLifeTime+1.f))	
	{
		deleteEmitter();
		return;
	}
	double timeStep=TickCounter::getEngineTime()-lastTime;

	b2Vec2 oldPos;
	bool isEmitting = m_isEmitting;
	GLuint numberOfNewEmitted = 0;


	for(int i=0;i<m_maxEmittedParticles;i++)
	{
		if( particleDataContainer[i].life > -0.2f)
		{	
			//particleTextureContainer[i] = (particleTextureDataContainer[0].textureCoordinates[floor( (particleTextureDataContainer[0].numberOfSprites) - (particleDataContainer[i].life/particleDataContainer[i].maxParticleLife * (particleTextureDataContainer[0].numberOfSprites-1))) ]);

			//printf("I: %f \n", particleTextureDataContainer[0].textureCoordinates[3].tc0.x/*(int)(particleDataContainer[i].life/particleDataContainer[i].maxParticleLife * particleTextureContainer.size()) ].tc2.x*/ );
			
			/*
				Check with Raycasting between last and now position for objects
			*/



			

			if(m_ongoingEmitting && !timer.hasPassed(particleDataContainer[i].maxParticleLife))
			{
				particleDataContainer[i].life=-0.1f;
				particlePositionContainer[i].w  = -0.1f;

			}
			else
			{
				oldPos.Set(particlePositionContainer[i].x/100.f,particlePositionContainer[i].y/100.f);

				particlePositionContainer[i].x += particleDataContainer[i].speed.x/TICKS_PER_SECOND;
				particlePositionContainer[i].y += particleDataContainer[i].speed.y/TICKS_PER_SECOND;

				if(m_collision && timer.hasPassed(0.2f))
				{
					BaseObject::getWorld()->RayCast(&hitRayCastCallback,oldPos,b2Vec2(particlePositionContainer[i].x,particlePositionContainer[i].y));

					if(hitRayCastCallback.isColliding())
					{
							particleDataContainer[i].life=-1.f;
							particlePositionContainer[i].w =-1.f;
					}
				}
				particleDataContainer[i].life-=timeStep;
				
				particlePositionContainer[i].z += particleDataContainer[i].speed.z;
				particlePositionContainer[i].w  = particleDataContainer[i].life/particleDataContainer[i].maxParticleLife;

			}
		}
		else if(m_ongoingEmitting && isEmitting)
		{	
			if (numberOfNewEmitted < m_maxEmittedParticles*m_emittedParticleModifier)
			{
				//particlePositionContainer.push_back(glm::vec4(emitterPosition.x*100.f-vX/TICKS_PER_SECOND,emitterPosition.y*100.f-vY/TICKS_PER_SECOND,posAngle,1.f));
				GLfloat vX, vY;
				if (m_emitterDirection.x == 0.f && m_emitterDirection.y == 0.f)
				{
					GLfloat tt = 2 * b2_pi*(rand() / (float)RAND_MAX);
					GLfloat uu = m_maxParticleVelocity*(rand() / (float)RAND_MAX) + (rand() / (float)RAND_MAX);
					GLfloat rt = uu>m_maxParticleVelocity ? 2 * m_maxParticleVelocity - uu : uu;
					vX = rt*cos(tt) * 100;
					vY = rt*sin(tt) * 100;
				}
				else
				{
					vX = m_emitterDirection.x * m_maxParticleVelocity * 100 + ((rand() / (float)RAND_MAX) - 0.5f) * 100;
					vY = m_emitterDirection.y * m_maxParticleVelocity * 100 + ((rand() / (float)RAND_MAX) - 0.5f) * 100;
				}

				vX += m_emitterVelocity.x * 50;
				vY += m_emitterVelocity.y * 50;



				particleDataContainer[i].speed = b2Vec3(vX, vY, particleDataContainer[i].speed.z != 0 ? toAngle((((float)rand() / (float)RAND_MAX) *b2_pi) / TICKS_PER_SECOND) : 0.f);



				//particleDataContainer[i].maxParticleLife=((float)rand()/(float)RAND_MAX)*m_maxLifeTime;
				particleDataContainer[i].life = particleDataContainer[i].maxParticleLife;

				particlePositionContainer[i].x = m_emitterPosition.x*100.f;// - particleDataContainer[i].speed.x/TICKS_PER_SECOND;
				particlePositionContainer[i].y = m_emitterPosition.y*100.f;// - particleDataContainer[i].speed.y/TICKS_PER_SECOND;

				particleDataContainer[i].life -= timeStep;
				//printf("Dead and respawned!\n");
			}
		}

	}



	glBindBuffer(GL_ARRAY_BUFFER,position_vbo);	// Change Angle for the whole Buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, particlePositionContainer.size() * sizeof( glm::vec4 ), &particlePositionContainer[0]);

	//glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);	// Change Angle for the whole Buffer
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof( b2Vec2 )*4, &particleTextureContainer[0]);


	if(glGetError() != GL_NO_ERROR)	printf("Error!\n");

	lastTime+=timeStep;
}


void ComplexTexturedParticleEmitter::renderParticles(b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset)
{
	if(!active) return;

	glEnable(GL_BLEND);

	//tex.render(960.f,540.f);
	complexParticleProgram.bind();

	complexParticleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(BaseObject::getWorldPos().x , BaseObject::getWorldPos().y ,0.f)));

	if (renderPos.x != 0.f || renderPos.y != 0.f || angle != 0.f)	//b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset
	{
		if (rotationOffset.x != 0.f || rotationOffset.y != 0.f)
		{
			complexParticleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(rotationOffset.x, rotationOffset.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rotationOffset.x, -rotationOffset.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(renderPos.x, renderPos.y, 0.f)));
		}
		else
		{
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
			complexParticleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(renderPos.x, renderPos.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rotationOffset.x, -rotationOffset.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(+rotationOffset.x, +rotationOffset.y, 0.f)));
		}
	}

	complexParticleProgram.updateModelViewMatrix();
	
	
	glBindVertexArray( vertexArray );
	
	glBindTexture(GL_TEXTURE_2D,particleTextureDataContainer[0].texture.getTextureID()); 
	glDrawArraysInstanced(GL_TRIANGLE_FAN,0,4,m_maxEmittedParticles);
	glBindVertexArray(NULL);
	if(glGetError() != GL_NO_ERROR)	printf("Error!\n");
}


void ComplexTexturedParticleEmitter::deleteEmitter()
{
	if(active)
	{
		active=false;

		particleVertexContainer.clear();
		particlePositionContainer.clear();
	
		particleDataContainer.clear();

		glDeleteBuffers(1,&vertex_vbo);
		glDeleteBuffers(1,&position_vbo);
		glDeleteBuffers(1,&information_vbo);

		removeParticles(m_maxEmittedParticles);
	}
}

void ComplexTexturedParticleEmitter::setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction)
{

	if(!m_ongoingEmitting)	return;
	m_emitterPosition = body->GetPosition();
	m_emitterVelocity = body->GetLinearVelocity();
	m_emitterDirection=direction;

}

bool ComplexTexturedParticleEmitter::isActive()
{
	return active;
}

/*
	Things to consider: 
		parent Velocity
		other Stuff
*/

/*
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

GLuint ComplexPlainParticleEmitter::particleCount=0;
ComplexPlainParticleProgram ComplexPlainParticleEmitter::complexParticleProgram;
std::vector<ParticleTextureData> ComplexPlainParticleEmitter::particleTextureDataContainer;
HitRayCastCallback ComplexPlainParticleEmitter::hitRayCastCallback;

void ComplexPlainParticleEmitter::loadParticleProgram()
{
	complexParticleProgram.loadProgram();

	complexParticleProgram.bind();

	complexParticleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	complexParticleProgram.updateProjectionMatrix();

	complexParticleProgram.setModelViewMatrix(glm::mat4());
	complexParticleProgram.updateModelViewMatrix();
}

ComplexPlainParticleEmitter::ComplexPlainParticleEmitter(void)
{
	active=false;
}


ComplexPlainParticleEmitter::~ComplexPlainParticleEmitter(void)
{
}

bool ComplexPlainParticleEmitter::addParticles(GLuint count)
{
	particleCount+=count;
	if(particleCount > MAX_PARTICLE_COUNT)
	{
		particleCount-=count;
		return false;
	}
	else
	{
		return true;
	}
	return true;
}
bool ComplexPlainParticleEmitter::removeParticles(GLuint count)
{
	particleCount-=count;
	if(particleCount < 0)	particleCount=0;
	return true;
}



void ComplexPlainParticleEmitter::createEmitter(b2Vec2 emitterPosition, b2Vec2 emitterVelocity, GLuint maxEmittedParticles, GLdouble maxLifetime, GLfloat maxParticleVelocity, b2Vec2 particleSize, bool collision, bool particleRotation, bool ongoingEmitting, b2Vec2 direction, GLuint particlesPerSecond)
{
	if(active) return;
	
	active=true;

	m_maxEmittedParticles=maxEmittedParticles;
	m_maxLifeTime=maxLifetime;
	m_emitterVelocity=emitterVelocity;
	m_emitterDirection=direction;
	m_maxParticleVelocity=maxParticleVelocity;

	m_ongoingEmitting=ongoingEmitting;
	
	
	m_emitterPosition=emitterPosition;
	b2Vec2 v=m_emitterVelocity;

	v*=(1.f/(TICKS_PER_SECOND*2));
	m_emitterPosition-=v;



	m_collision=collision;

	// Save all 4 Vertices
	particleSize.x /= 2;	// get the halfsizes
	particleSize.y /= 2;	// get the halfsizes
	//particleSize=b2Vec2(0.5f,0.5f);
	particleVertexContainer.reserve(4);
	particleVertexContainer.push_back(b2Vec2( -particleSize.x , -particleSize.y ));
	particleVertexContainer.push_back(b2Vec2( particleSize.x , -particleSize.y ));
	particleVertexContainer.push_back(b2Vec2( particleSize.x , particleSize.y ));
	particleVertexContainer.push_back(b2Vec2( -particleSize.x , particleSize.y ));

	
	particlePositionContainer.reserve(m_maxEmittedParticles);
	particleDataContainer.reserve(m_maxEmittedParticles);
	
	float t_accum = TickCounter::getEngineTime(); // start time

	if(m_maxEmittedParticles > MAX_PARTICLE_COUNT_PER_EMITTER)	m_maxEmittedParticles=MAX_PARTICLE_COUNT_PER_EMITTER;

	if(!ComplexPlainParticleEmitter::addParticles(m_maxEmittedParticles))
	{
		printf("Number of Particles too high!\n");
		return;
	}
	ParticleData currentParticle;

	for (int i = 0; i < maxEmittedParticles; i++) {

		GLfloat posAngle;
		GLfloat vX,vY,vAngular;


		// Speed
		if(m_emitterDirection.x == 0.f && m_emitterDirection.y == 0.f)
		{
			GLfloat tt = 2*b2_pi*(rand()/ (float)RAND_MAX);
			GLfloat uu = maxParticleVelocity*(rand()/ (float)RAND_MAX)+(rand()/ (float)RAND_MAX);
			GLfloat rt = uu>maxParticleVelocity ? 2*maxParticleVelocity-uu : uu;
			vX=rt*cos(tt)*100;
			vY=rt*sin(tt)*100;
		}
		else
		{
			vX = direction.x * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
			vY = direction.y * maxParticleVelocity* 100 + ( (rand() / (float)RAND_MAX) -0.5f) * 100;
		}
		
		vX+=m_emitterVelocity.x * 50;
		vY+=m_emitterVelocity.y * 50;

		// Rotation
		if(particleRotation)
		{
			vAngular = ((float)rand() / (float)RAND_MAX) *b2_pi;
			posAngle = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
		}
		else
		{
			vAngular=0.f;
			posAngle = 0.f;
		}
		currentParticle.speed=b2Vec3(vX,vY,toAngle(vAngular/TICKS_PER_SECOND));

		currentParticle.maxParticleLife=((float)rand()/(float)RAND_MAX)*m_maxLifeTime;
		currentParticle.life=currentParticle.maxParticleLife;

		// Position
		particlePositionContainer.push_back(glm::vec4(m_emitterPosition.x*100.f,m_emitterPosition.y*100.f,posAngle,1.f));

		// start times
		//vt.push_back(t_accum + 0.01f); // spacing for start times is 0.01 seconds
		//vt.push_back(((float)rand()/(float)RAND_MAX)*m_maxLifeTime);	// Lifetime
		particleDataContainer.push_back(currentParticle);		
	}

	glGenBuffers (1, &vertex_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData (GL_ARRAY_BUFFER, particleVertexContainer.size() * (sizeof( b2Vec2 )), &particleVertexContainer[0], GL_STATIC_DRAW);

	glGenBuffers (1, &position_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, position_vbo);
	glBufferData (GL_ARRAY_BUFFER, particlePositionContainer.size() * (sizeof( glm::vec4 )) , &particlePositionContainer[0], GL_STREAM_DRAW);


	glGenVertexArrays (1, &vertexArray);
	glBindVertexArray (vertexArray);

	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);

	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2),	0);

	glBindBuffer(GL_ARRAY_BUFFER,position_vbo);
	glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4),	0);


	glVertexAttribDivisor(0,0);	// Vertex
	glVertexAttribDivisor(1,1); // Position


	glBindVertexArray (NULL);

		
	
	complexParticleProgram.bind();
	//complexParticleProgram.setElapsedTime((GLfloat)TickCounter::getEngineTime());
	complexParticleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	complexParticleProgram.updateProjectionMatrix();

	complexParticleProgram.setModelViewMatrix(glm::mat4());
	complexParticleProgram.updateModelViewMatrix();
	
	//renderPosition.Set( (m_emitterPosition.x)*100-50*m_emitterVelocity.x*1/TICKS_PER_SECOND , (m_emitterPosition.y)*100-50*m_emitterVelocity.y*1/TICKS_PER_SECOND);
	timer.start();

	lastTime=TickCounter::getEngineTime();
}

void ComplexPlainParticleEmitter::setParticleColor(Color4f startColor,Color4f endColor)
{
	m_startColor=startColor;
	m_endColor=endColor;
}


void ComplexPlainParticleEmitter::update()
{
	if(!active) return;
	if(!m_ongoingEmitting &&  timer.hasPassed(m_maxLifeTime+1.f))	
	{
		deleteEmitter();
		return;
	}
	double timeStep=TickCounter::getEngineTime()-lastTime;

	b2Vec2 oldPos;
	bool isEmitting = m_isEmitting;
	GLuint numberOfNewEmitted = 0;

	for(int i=0;i<m_maxEmittedParticles;i++)
	{
		if( particleDataContainer[i].life > -0.2f)
		{	
			//particleTextureContainer[i] = (particleTextureDataContainer[0].textureCoordinates[floor( (particleTextureDataContainer[0].numberOfSprites) - (particleDataContainer[i].life/particleDataContainer[i].maxParticleLife * (particleTextureDataContainer[0].numberOfSprites-1))) ]);

			//printf("I: %f \n", particleTextureDataContainer[0].textureCoordinates[3].tc0.x/*(int)(particleDataContainer[i].life/particleDataContainer[i].maxParticleLife * particleTextureContainer.size()) ].tc2.x*/ );
			
			/*
				Check with Raycasting between last and now position for objects
			*/

			if(m_ongoingEmitting && !timer.hasPassed(particleDataContainer[i].maxParticleLife))
			{
				particleDataContainer[i].life=-0.1f;
				particlePositionContainer[i].w  = -0.1f;

			}
			else
			{
			//oldPos.Set(particlePositionContainer[i].x/100.f,particlePositionContainer[i].y/100.f);
				particleDataContainer[i].life-=timeStep;
				particlePositionContainer[i].x += particleDataContainer[i].speed.x/TICKS_PER_SECOND;
				particlePositionContainer[i].y += particleDataContainer[i].speed.y/TICKS_PER_SECOND;

				particlePositionContainer[i].z += particleDataContainer[i].speed.z;
				particlePositionContainer[i].w  = particleDataContainer[i].life/particleDataContainer[i].maxParticleLife;

				if(m_collision && timer.hasPassed(0.17f))
				{
					BaseObject::getWorld()->RayCast(&hitRayCastCallback, oldPos, b2Vec2(particlePositionContainer[i].x / 100.f, particlePositionContainer[i].y / 100.f));

					if(hitRayCastCallback.isColliding())
					{
							particleDataContainer[i].life=-1.f;
							particlePositionContainer[i].w =-1.f;
					}
				}

			}
		}
		else if(m_ongoingEmitting && isEmitting)
		{	
			if (numberOfNewEmitted < ceil(m_maxEmittedParticles*m_emittedParticleModifier))
			{
				++numberOfNewEmitted;
				//particlePositionContainer.push_back(glm::vec4(emitterPosition.x*100.f-vX/TICKS_PER_SECOND,emitterPosition.y*100.f-vY/TICKS_PER_SECOND,posAngle,1.f));
				GLfloat vX, vY;
				if (m_emitterDirection.x == 0.f && m_emitterDirection.y == 0.f)
				{
					GLfloat tt = 2 * b2_pi*(rand() / (float)RAND_MAX);
					GLfloat uu = m_maxParticleVelocity*(rand() / (float)RAND_MAX) + (rand() / (float)RAND_MAX);
					GLfloat rt = uu>m_maxParticleVelocity ? 2 * m_maxParticleVelocity - uu : uu;
					vX = rt*cos(tt) * 100;
					vY = rt*sin(tt) * 100;
				}
				else
				{
					vX = m_emitterDirection.x * m_maxParticleVelocity * 100 + ((rand() / (float)RAND_MAX) - 0.5f) * 100;
					vY = m_emitterDirection.y * m_maxParticleVelocity * 100 + ((rand() / (float)RAND_MAX) - 0.5f) * 100;
				}

				vX += m_emitterVelocity.x *50;
				vY += m_emitterVelocity.y *50;// *50;


				particleDataContainer[i].speed = b2Vec3(vX, vY, particleDataContainer[i].speed.z != 0 ? toAngle((((float)rand() / (float)RAND_MAX) *b2_pi) / TICKS_PER_SECOND) : 0.f);



				particleDataContainer[i].maxParticleLife = ((float)rand() / (float)RAND_MAX)*m_maxLifeTime;
				particleDataContainer[i].life = particleDataContainer[i].maxParticleLife;

				particlePositionContainer[i].x = m_emitterPosition.x*100.f;// - particleDataContainer[i].speed.x/TICKS_PER_SECOND;
				particlePositionContainer[i].y = m_emitterPosition.y*100.f;// - particleDataContainer[i].speed.y/TICKS_PER_SECOND;

				particleDataContainer[i].life -= timeStep;
				//printf("Dead and respawned!\n");
			}
		}

	}


	glBindBuffer(GL_ARRAY_BUFFER,position_vbo);	// Change Angle for the whole Buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, particlePositionContainer.size() * sizeof( glm::vec4 ), &particlePositionContainer[0]);

	//glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);	// Change Angle for the whole Buffer
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof( b2Vec2 )*4, &particleTextureContainer[0]);


	if(glGetError() != GL_NO_ERROR)	printf("Error!\n");

	lastTime+=timeStep;
}


void ComplexPlainParticleEmitter::renderParticles(b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset)
{
	if(!active) return;

	//glEnable(GL_BLEND);

	//tex.render(960.f,540.f);
	complexParticleProgram.bind();

	complexParticleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(BaseObject::getWorldPos().x , BaseObject::getWorldPos().y ,0.f)));

	if (renderPos.x != 0.f || renderPos.y != 0.f || angle != 0.f)
	{
		if (rotationOffset.x != 0.f || rotationOffset.y != 0.f)
		{

			complexParticleProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(rotationOffset.x, rotationOffset.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rotationOffset.x, -rotationOffset.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(BaseObject::getWorldPos().x + renderPos.x, BaseObject::getWorldPos().y + renderPos.y, 0.f)));
		}
		else
		{
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
			complexParticleProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(renderPos.x, renderPos.y, 0.f)));
			complexParticleProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
		}
	}
	
	complexParticleProgram.updateModelViewMatrix();
	complexParticleProgram.setColour(m_startColor,m_endColor);
	
	glBindVertexArray( vertexArray );

	glDrawArraysInstanced(GL_TRIANGLE_FAN,0,4,m_maxEmittedParticles);
	glBindVertexArray(NULL);
	
	if(glGetError() == GL_INVALID_OPERATION)	printf("Error Rendering CPPE!\n");
}


void ComplexPlainParticleEmitter::deleteEmitter()
{
	if(active)
	{
		active=false;

		particleVertexContainer.clear();
		particlePositionContainer.clear();
	
		particleDataContainer.clear();

		glDeleteBuffers(1,&vertex_vbo);
		glDeleteBuffers(1,&position_vbo);

		removeParticles(m_maxEmittedParticles);
	}
}

void ComplexPlainParticleEmitter::setPosition(b2Body* body, b2Vec2 positionOffset, b2Vec2 direction)
{
	if(!m_ongoingEmitting)	return;
	positionOffset *= 1.f / 100.f;			
	
	m_emitterPosition = body->GetPosition() + body->GetWorldVector(positionOffset);
	m_emitterVelocity = body->GetLinearVelocity();
	m_emitterDirection=direction;
}

bool ComplexPlainParticleEmitter::isActive()
{
	return active;
}
































