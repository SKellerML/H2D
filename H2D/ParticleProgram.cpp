#include "ParticleProgram.h"


ParticleProgram::ParticleProgram(void)
{
	//mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	//mColorLocation=0;
}


ParticleProgram::~ParticleProgram(void)
{
	//mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	//mColorLocation=0;
}

bool ParticleProgram::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("ParticleProgram2D.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("ParticleProgram2D.glfs",GL_FRAGMENT_SHADER);

	glAttachShader(mProgramID,fragmentShader);

	if(vertexShader == 0 || fragmentShader == 0)
	{
		mProgramID = 0;
		return false;
	}

	glLinkProgram(mProgramID);

	GLint programSuccess = GL_FALSE;
	glGetProgramiv(mProgramID,GL_LINK_STATUS,&programSuccess);
	if( programSuccess != GL_TRUE )
    {
		printf( "Could not link program %d\n", mProgramID );
        mProgramID = 0;
        return false;
    }

	mProjectionMatrixLocation=glGetUniformLocation(mProgramID,"ProjectionMatrix");
	if(mProjectionMatrixLocation == -1)
	{
		printf("ProjectionMatrix is not a valid uniform\n");
	}
	mModelViewMatrixLocation=glGetUniformLocation(mProgramID,"ModelViewMatrix");
	if(mModelViewMatrixLocation == -1)
	{
		printf("ModelViewMatrix is not a valid uniform\n");
	}

	mEmitterPos=glGetUniformLocation(mProgramID,"emitterPosWorld");
	if(mEmitterPos == -1)
	{
		printf("emitterPosWorld is not a valid uniform\n");
	}

	elapsed_system_time = glGetUniformLocation(mProgramID,"elapsedSystemTime");
	if(elapsed_system_time == -1)
	{
		printf("elapsedSystemTime is not a valid uniform\n");
	}

	mOngoingEmitting = glGetUniformLocation(mProgramID,"ongoingEmitting");
	if(mOngoingEmitting == -1)
	{
		printf("ongoingEmitting is not a valid uniform\n");
	}
	
	mColorStart = glGetUniformLocation(mProgramID,"particle_colourStart");
	if(mOngoingEmitting == -1)
	{
		printf("particle_colourStart is not a valid uniform\n");
	}
	mColorEnd = glGetUniformLocation(mProgramID,"particle_colourEnd");
	if(mOngoingEmitting == -1)
	{
		printf("particle_colourEnd is not a valid uniform\n");
	}

	//mTextureSampler = glGetUniformLocation(mProgramID,"TextureUnit");
	//if(mTextureSampler == -1)
	//{
	//	printf("Tex is not a valid uniform\n");
	//}
	return true;
}

void ParticleProgram::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void ParticleProgram::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void ParticleProgram::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void ParticleProgram::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void ParticleProgram::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}
/*
void ParticleProgram::enableDataPointers()
{
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void ParticleProgram::setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mColorLocation,r,g,b,a);
}

void ParticleProgram::setColor(Color4f color)
{
	glUniform4f(mColorLocation,color.r,color.g,color.b,color.a);
}

void ParticleProgram::setVertexPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,stride,data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}
*/
void ParticleProgram::setElapsedTime(GLfloat time)
{
	//glUniform1i(mTextureSampler,0);
	glUniform1f(elapsed_system_time,time);
}

void ParticleProgram::setEmitterPosition(b2Vec2 position)
{
	glUniform2f(mEmitterPos,position.x,position.y);
}

void ParticleProgram::setOngoingEmitting(bool var)
{
	glUniform1i(mOngoingEmitting,var);
}

void ParticleProgram::setColour(Color4f startColor,Color4f endColor)
{
	glUniform4f(mColorStart,startColor.r,startColor.g,startColor.b,startColor.a);
	glUniform4f(mColorEnd,endColor.r,endColor.g,endColor.b,endColor.a);
}