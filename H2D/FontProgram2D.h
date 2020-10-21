#pragma once

#include "ShaderProgram.h"
#include <glm.hpp>
#include "Rect.h"


class FontProgram2D : public ShaderProgram
{
public:
	FontProgram2D(void);
	~FontProgram2D(void);

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);

	void setTextColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void setTextColor(Color4f col);

	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);
	void setTextureUnit( GLuint unit );

	void enableDataPointers();
	void setVertexPointer(GLsizei stride,const GLvoid* data);
	void setTexCoordPointer(GLsizei stride,const GLvoid* data);

	GLuint initVAO(GLuint textureWidth,GLuint textureHeight,Rect* clip);
	void drawVAO(GLuint textureID,GLuint fVAO,GLfloat x, GLfloat y);



protected:
	GLuint mVertexPos2DLocation;
	GLuint mTexCoordLocation;
	GLuint mTextColorLocation;
	GLuint mTextureUnitLocation;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

