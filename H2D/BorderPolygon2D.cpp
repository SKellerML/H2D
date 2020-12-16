#include "BorderPolygon2D.h"

#include <glm\gtc\type_ptr.hpp>
//#include <gtc\type_ptr.hpp>

BorderPolygon2D::BorderPolygon2D(void)
{
	mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;
	mColorLocation=0;
}


BorderPolygon2D::~BorderPolygon2D(void)
{
	mVertexPos2DLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;
	mColorLocation=0;
}

bool BorderPolygon2D::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("BorderPolygon2D.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("BorderPolygon2D.glfs",GL_FRAGMENT_SHADER);

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
	mColorLocation = glGetUniformLocation(mProgramID,"PlainColor");
	if(mColorLocation == -1)
	{
		printf("PlainColor is not a valid uniform\n");
	}

	return true;
}

void BorderPolygon2D::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void BorderPolygon2D::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void BorderPolygon2D::setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mColorLocation,r,g,b,a);
}

void BorderPolygon2D::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void BorderPolygon2D::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void BorderPolygon2D::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void BorderPolygon2D::enableDataPointers()
{
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void BorderPolygon2D::setVertexPointer()
{

	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,0,NULL);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}
