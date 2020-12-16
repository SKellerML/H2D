#pragma once

#include "ShaderProgram.h"
#include <glm\glm.hpp>


class LightProgram : public ShaderProgram
{
public:
	LightProgram(void);
	~LightProgram(void);

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	void setTextureColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);
	void setTextureUnit( GLuint unitBack , GLuint unitFore, GLuint unitMask);

	void enableDataPointers();
	void setVertexPointer(GLsizei stride,const GLvoid* data);
	void setTexCoordPointer(GLsizei stride,const GLvoid* data);


protected:
	GLuint mVertexPos2DLocation;
	GLuint mTexCoordLocation;
	GLuint mTextureColorLocation;
	GLuint mBackgroundLoc, mForegroundLoc, mMaskLoc;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

