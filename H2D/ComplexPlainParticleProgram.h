#pragma once
#include "ShaderProgram.h"
#include <gtc\type_ptr.hpp>
#include <glm.hpp>
#include "Rect.h"

class ComplexPlainParticleProgram : public ShaderProgram
{
public:
	ComplexPlainParticleProgram(void);
	~ComplexPlainParticleProgram(void);



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

	void setColour(Color4f startColor, Color4f endColor);

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
	GLuint mStartColor;
	GLuint mEndColor;

	glm::mat4 ProjectionMatrix;
	GLuint mProjectionMatrixLocation;

	glm::mat4 ModelViewMatrix;
	GLuint mModelViewMatrixLocation;
};

