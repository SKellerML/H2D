#pragma once

#include "OpenGLH.h"

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);

	void bind();

	void unbind();

	GLuint getProgramID();

	virtual bool loadProgram()=0;

protected:
	GLuint loadShaderFromFile(std::string path,GLenum shaderType);

	GLuint mProgramID;
};

