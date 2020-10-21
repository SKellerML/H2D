#include "ComplexPlainParticleProgram.h"


ComplexPlainParticleProgram::ComplexPlainParticleProgram(void)
{
}


ComplexPlainParticleProgram::~ComplexPlainParticleProgram(void)
{
}

bool ComplexPlainParticleProgram::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("ComplexPlainParticleProgram.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("ComplexPlainParticleProgram.glfs",GL_FRAGMENT_SHADER);

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
	mStartColor=glGetUniformLocation(mProgramID,"startColor");
	if(mStartColor == -1)
	{
		printf("startColor is not a valid uniform\n");
	}
	mEndColor=glGetUniformLocation(mProgramID,"endColor");
	if(mEndColor == -1)
	{
		printf("endColor is not a valid uniform\n");
	}
	
	/*	ATTRIBUTE!!!!!!!!!!!!!!!!!!!!!
	GLfloat mEmitterPos=glGetAttribLocation(mProgramID,"vertexPosition");
	if(mEmitterPos == -1)
	{
		printf("vertexPosition is not a valid uniform\n");
	}
	*/



	//mTextureSampler = glGetUniformLocation(mProgramID,"TextureUnit");
	//if(mTextureSampler == -1)
	//{
	//	printf("Tex is not a valid uniform\n");
	//}
	return true;
}

void ComplexPlainParticleProgram::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void ComplexPlainParticleProgram::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void ComplexPlainParticleProgram::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void ComplexPlainParticleProgram::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void ComplexPlainParticleProgram::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void ComplexPlainParticleProgram::setColour(Color4f startColor, Color4f endColor)
{
	glUniform4f(mStartColor,startColor.r,startColor.g,startColor.b,startColor.a);
	glUniform4f(mEndColor,endColor.r,endColor.g,endColor.b,endColor.a);
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

/*
void ComplexPlainParticleProgram::setElapsedTime(GLfloat time)
{
	//glUniform1i(mTextureSampler,0);
	glUniform1f(elapsed_system_time,time);
}

void ComplexPlainParticleProgram::setEmitterPosition(b2Vec2 position)
{
	glUniform2f(mEmitterPos,position.x,position.y);
}

void ComplexPlainParticleProgram::setOngoingEmitting(bool var)
{
	glUniform1i(mOngoingEmitting,var);
}

void ComplexPlainParticleProgram::setColour(Color4f startColor,Color4f endColor)
{
	glUniform4f(mColorStart,startColor.r,startColor.g,startColor.b,startColor.a);
	glUniform4f(mColorEnd,endColor.r,endColor.g,endColor.b,endColor.a);
}
*/