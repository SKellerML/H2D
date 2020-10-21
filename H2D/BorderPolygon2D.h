#pragma once

#include "OpenGLH.h"
#include "ShaderProgram.h"
#include <glm.hpp>


class BorderPolygon2D : public ShaderProgram
{
public:
	BorderPolygon2D(void);
	~BorderPolygon2D(void);

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	void setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);

	void enableDataPointers();
	void setVertexPointer();



protected:
	GLuint mVertexPos2DLocation;
	GLuint mColorLocation;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;

};

