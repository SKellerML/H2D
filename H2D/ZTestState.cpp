#include "ZTestState.h"

ZTestState::ZTestState(void)
{
	init(1);
	LastUsedParticle = 0;
}


ZTestState::~ZTestState(void)
{

}

void ZTestState::init(GLuint levelType)
{	
	GameState::setHandler(HANDLER_GUI);

	tex.loadTextureFromFile32("arrow.png");

	particleProgram.loadProgram();

	particleProgram.bind();

	//particleProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	//particleProgram.updateProjectionMatrix();
	particleProgram.setProjectionMatrix(glm::ortho<GLfloat>(-960.0f,960.0f,540.f,-540.f,-1.f,0.f));
	particleProgram.updateProjectionMatrix();

	particleProgram.setModelViewMatrix(glm::mat4());
	particleProgram.updateModelViewMatrix();

	/*
		Scheiﬂ auf Instancing, vorerst
	*/
	ParticleInformation pinf[12];



	particleVertexContainer.push_back(b2Vec2( -50.f , -50.f ));
	particleTextureContainer.push_back(b2Vec2( 0.f , 0.f ));

	particleVertexContainer.push_back(b2Vec2( 50.f , -50.f ));
	particleTextureContainer.push_back(b2Vec2( 1.f , 0.f ));

	particleVertexContainer.push_back(b2Vec2( 50.f , 50.f ));
	particleTextureContainer.push_back(b2Vec2( 1.f , 1.f ));


	particleVertexContainer.push_back(b2Vec2( -50.f , 50.f ));
	particleTextureContainer.push_back(b2Vec2( 0.f , 1.f ));

	


	GLfloat px=90.f,py=90.f,pa=0.f;

	positionContainer.push_back(b2Vec3(px,py,pa));


	px=-90.f;
	py=-90.f;
	pa=45.f;

	positionContainer.push_back(b2Vec3(px,py,pa));


	px=-90.f;
	py=90.f;
	pa=0.f;

	positionContainer.push_back(b2Vec3(px,py,pa));

	px=90.f;
	py=-90.f;
	pa=45.f;

	positionContainer.push_back(b2Vec3(px,py,pa));

	//particleInformationContainer.push_back(b2Vec2(-100.f,-100.f));
	//particleInformationContainer.push_back(b2Vec2(100.f,-100.f));
	//particleInformationContainer.push_back(b2Vec2(100.f,100.f));
	//particleInformationContainer.push_back(b2Vec2(-100.f,100.f));

	//float pppp[8];
	//pppp[0]=-100.f;
	//pppp[1]=-100.f;
	//pppp[2]=100.f;
	//pppp[3]=-100.f;
	//pppp[4]=100.f;
	//pppp[5]=100.f;
	//pppp[6]=-100.f;
	//pppp[7]=100.f;

	//pinf.pos=b2Vec3(960.f,540.f,0.f);
	//pinf.color=Color4f(1.f,1.f,1.f,1.f);

	Particle p;
	p.speed=b2Vec3(10.f,10.f,0.f);
	p.life=5.f;

	//particleInformationContainer.push_back(pinf);
	particleContainer.push_back(p);

	

	glGenBuffers (1, &vertex_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData (GL_ARRAY_BUFFER, particleVertexContainer.size() * (sizeof( b2Vec2 )), &particleVertexContainer[0], GL_STATIC_DRAW);

	glGenBuffers (1, &texCoord_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, texCoord_vbo);
	glBufferData (GL_ARRAY_BUFFER, particleTextureContainer.size() * (sizeof( b2Vec2 )), &particleTextureContainer[0], GL_STREAM_DRAW);


	glGenBuffers (1, &poscon);
	glBindBuffer (GL_ARRAY_BUFFER, poscon);
	glBufferData (GL_ARRAY_BUFFER, positionContainer.size() * (sizeof( b2Vec3 )) , &positionContainer[0], GL_STREAM_DRAW);

	//glGenBuffers (1, &position_vbo);
	//glBindBuffer (GL_ARRAY_BUFFER, position_vbo);
	//glBufferData (GL_ARRAY_BUFFER, particleInformationContainer.size()*sizeof(float)*3 /*sizeof (vv)*/, &particleInformationContainer[0], GL_DYNAMIC_DRAW);

	/*
	glGenBuffers (1, &color_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, color_vbo);
	glBufferData (GL_ARRAY_BUFFER, particleContainer.size() * sizeof(float)*4, &angleV[0], GL_STATIC_DRAW);
	*/
	

	glGenVertexArrays (1, &vertexArray);
	glBindVertexArray (vertexArray);

	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	glEnableVertexAttribArray (2);

	glBindBuffer (GL_ARRAY_BUFFER, vertex_vbo);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2),	0);//(GLvoid*)(offsetof(ParticleInformation,vertices))	);//(GLvoid*)offsetof(ParticleInformation,vertices));
	
	glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2),	0);//(GLvoid*)(offsetof(ParticleInformation,pos))		);//(GLvoid*)offsetof(ParticleInformation,vertices) );

	glBindBuffer(GL_ARRAY_BUFFER,poscon);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(b2Vec3),	0);//(GLvoid*)(offsetof(ParticleInformation,pos))		);//(GLvoid*)offsetof(ParticleInformation,vertices) );
	//glBindBuffer (GL_ARRAY_BUFFER, position_vbo);
	//glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE,sizeof(ParticleInformation), (GLvoid*)offsetof(ParticleInformation,pos));

	// assuming glVertexPointer is already set
	glVertexAttribDivisor(0,0);	// Vertex
	glVertexAttribDivisor(1,1); // Position
	glVertexAttribDivisor(2,0); // TexCoord
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);

	/*
	glBindBuffer (GL_ARRAY_BUFFER, vbo_angle);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	*/
	glBindVertexArray (NULL);
	//glEnableVertexAttribArray (2);
}

void ZTestState::update()
{
	for(int i=0;i<positionContainer.size();i++)
	{
		positionContainer[i].z+=1.0f;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER,poscon);	// Change Angle for the whole Buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionContainer.size() * (sizeof( b2Vec3 )) , &positionContainer[0]);

	if(glGetError() != GL_NO_ERROR)	printf("Error!\n");
}

void ZTestState::renderBackground()
{
}

void ZTestState::render()
{
}

void ZTestState::updateRender()
{
}

void ZTestState::renderFinal()
{
	tex.render(960.f,540.f);
	
	particleProgram.bind();
	glBindVertexArray( vertexArray );
	
	glBindTexture(GL_TEXTURE_2D,tex.getTextureID()); 
	//glDrawElements( GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, NULL );
	//glDrawArrays(GL_TRIANGLE_FAN,0,8);
	GLint startingElements[] = {0, 4};
	GLsizei counts[] = {4, 4};
	//glMultiDrawArrays(GL_TRIANGLE_FAN,startingElements, counts, 2);
	glDrawArraysInstanced(GL_TRIANGLE_FAN,0,4,4);
	glBindVertexArray(NULL);

	if(glGetError() != GL_NO_ERROR)	printf("Error!\n");
}
