#pragma once

#include "ShaderProgram.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#include "Rect.h"

class ComplexTexturedParticleProgram : public ShaderProgram
{
public:
	ComplexTexturedParticleProgram(void);
	~ComplexTexturedParticleProgram(void);



	bool loadProgram();

	void setProjectionMatrix(glm::mat4 matrix);
	void setModelViewMatrix(glm::mat4 matrix);
	//void setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	//void setColor(Color4f color);
	void updateProjectionMatrix();
	void updateModelViewMatrix();
	void leftMultModelView(glm::mat4 matrix);

	void setElapsedTime(GLfloat time);
	void setEmitterPosition(b2Vec2 position);
	void setOngoingEmitting(bool var);

	void setColour(Color4f color);

	/*
	void setVertexPointer(GLsizei stride,const GLvoid* data);
	void enableDataPointers();
	*/
public:
	/*
	GLuint mEmitterPos;
	GLuint elapsed_system_time;
	GLuint mTextureSampler;
	GLuint mOngoingEmitting;
	GLuint mColorStart;
	GLuint mColorEnd;
	*/
	GLuint mTextureColor;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

