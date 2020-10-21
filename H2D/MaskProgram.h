#pragma once

#include "ShaderProgram.h"
#include <glm.hpp>


class MaskProgram : public ShaderProgram
{
public:
	MaskProgram(void);
	~MaskProgram(void);

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	void setTextureColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);
	void setTextureUnit(GLuint unitBack, GLuint unitFore, GLuint unitMask, GLuint unitLight);

	void enableDataPointers();
	void setVertexPointer(GLsizei stride,const GLvoid* data);
	void setTexCoordPointer(GLsizei stride,const GLvoid* data);


protected:
	GLuint mVertexPos2DLocation;
	GLuint mTexCoordLocation;
	GLuint mTextureColorLocation;
	GLuint mBackgroundLoc, mForegroundLoc, mMaskLoc, mLightLoc;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

