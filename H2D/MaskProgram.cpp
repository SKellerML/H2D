#include "MaskProgram.h"
#include <glm\gtc\type_ptr.hpp>

MaskProgram::MaskProgram(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextureColorLocation=0;
}


MaskProgram::~MaskProgram(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextureColorLocation=0;
	//mTextureUnitLocation=0;
}

bool MaskProgram::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("MaskProgram.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("MaskProgram.glfs",GL_FRAGMENT_SHADER);

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

	mBackgroundLoc = glGetUniformLocation(mProgramID, "backgroundTexture");
	if (mBackgroundLoc == -1)
	{
		printf("mBackgroundLoc is not a valid uniform\n");
	}
	mForegroundLoc = glGetUniformLocation(mProgramID, "foregroundTexture");
	if (mForegroundLoc == -1)
	{
		printf("mForegroundLoc is not a valid uniform\n");
	}
	mMaskLoc = glGetUniformLocation(mProgramID, "maskTexture");
	if (mMaskLoc == -1)
	{
		printf("mMaskLoc is not a valid uniform\n");
	}
	mLightLoc = glGetUniformLocation(mProgramID, "lightTexture");
	if (mLightLoc == -1)
	{
		printf("lightTexture is not a valid uniform\n");
	}
	return true;
}

void MaskProgram::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void MaskProgram::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void MaskProgram::setTextureColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mTextureColorLocation,r,g,b,a);
}

void MaskProgram::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void MaskProgram::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void MaskProgram::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void MaskProgram::setTextureUnit(GLuint unitBack, GLuint unitFore, GLuint unitMask, GLuint unitLight)
{
	glUniform1i(mBackgroundLoc, unitBack);
	glUniform1i(mForegroundLoc, unitFore);
	glUniform1i(mMaskLoc, unitMask);
	glUniform1i(mLightLoc, unitLight);
}

void MaskProgram::enableDataPointers()
{
	glEnableVertexAttribArray(mTexCoordLocation);
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void MaskProgram::setVertexPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,stride,data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}

void MaskProgram::setTexCoordPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation,2,GL_FLOAT,GL_FALSE,stride,data);

}