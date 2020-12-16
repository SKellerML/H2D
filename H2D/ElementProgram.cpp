#include "ElementProgram.h"
#include <glm\gtc\type_ptr.hpp>

ElementProgram::ElementProgram(void)
{
	mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mColorLocation=0;
}


ElementProgram::~ElementProgram(void)
{
	mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mColorLocation=0;
}

bool ElementProgram::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("ElementProgram2D.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("ElementProgram2D.glfs",GL_FRAGMENT_SHADER);

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
	mVertexPos2DLocation = glGetAttribLocation(mProgramID,"VertexPos2D");
	if(mVertexPos2DLocation == -1)
	{
		printf("VertexPos2D is not a valid uniform\n");
	}
	mColorLocation = glGetUniformLocation(mProgramID,"Color");
	if(mColorLocation == -1)
	{
		printf("TextureColor is not a valid uniform\n");
	}

	return true;
}

void ElementProgram::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void ElementProgram::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void ElementProgram::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void ElementProgram::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void ElementProgram::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void ElementProgram::enableDataPointers()
{
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void ElementProgram::setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mColorLocation,r,g,b,a);
}

void ElementProgram::setColor(Color4f color)
{
	glUniform4f(mColorLocation,color.r,color.g,color.b,color.a);
}

void ElementProgram::setVertexPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,stride,data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}