#include "TexturedPolygon2D.h"
#include <gtc\type_ptr.hpp>

TexturedPolygon2D::TexturedPolygon2D(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextureColorLocation=0;
	mTextureUnitLocation=0;
}


TexturedPolygon2D::~TexturedPolygon2D(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextureColorLocation=0;
	//mTextureUnitLocation=0;
}

bool TexturedPolygon2D::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("TexturedPolygon2D.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("TexturedPolygon2D.glfs",GL_FRAGMENT_SHADER);

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
	mTexCoordLocation = glGetAttribLocation(mProgramID,"TextureCoord");
	if(mTexCoordLocation == -1)
	{
		printf("TextureCoord is not a valid uniform\n");
	}
	mTextureColorLocation = glGetUniformLocation(mProgramID,"TextureColor");
	if(mTextureColorLocation == -1)
	{
		printf("TextureColor is not a valid uniform\n");
	}
	mTextureUnitLocation = glGetUniformLocation(mProgramID,"TextureUnit");
	if(mTextureUnitLocation == -1)
	{
		printf("TextureUnit is not a valid uniform\n");
	}
	return true;
}

void TexturedPolygon2D::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void TexturedPolygon2D::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void TexturedPolygon2D::setTextureColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mTextureColorLocation,r,g,b,a);
}

void TexturedPolygon2D::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void TexturedPolygon2D::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void TexturedPolygon2D::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void TexturedPolygon2D::setTextureUnit( GLuint unit )
{
	glUniform1i( mTextureUnitLocation, unit );
}

void TexturedPolygon2D::enableDataPointers()
{
	glEnableVertexAttribArray(mTexCoordLocation);
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void TexturedPolygon2D::setVertexPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,stride,data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}

void TexturedPolygon2D::setTexCoordPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation,2,GL_FLOAT,GL_FALSE,stride,data);

}