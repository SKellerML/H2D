#pragma once

#include "ShaderProgram.h"
#include "Rect.h"
#include <glm.hpp>

class ElementProgram : public ShaderProgram
{
public:
	ElementProgram(void);
	~ElementProgram(void);

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	void setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void setColor(Color4f color);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);

	void setVertexPointer(GLsizei stride,const GLvoid* data);
	void enableDataPointers();

public:
	GLuint mVertexPos2DLocation;
	GLuint mColorLocation;


	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;

};

