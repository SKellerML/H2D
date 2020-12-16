#pragma once

#include "ShaderProgram.h"
#include "Rect.h"
#include <glm\glm.hpp>

class TileProgram : public ShaderProgram
{
public:
	TileProgram();
	~TileProgram();

	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	void setTextureUnit(GLuint unit);
	void setColor(Color4f color);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);

	void setVertexPointer(GLsizei stride, const GLvoid* data);
	void enableDataPointers();

public:
	GLuint mVertexPos2DLocation;
	GLuint mTextureUnitLocation;


	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

