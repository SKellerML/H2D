#include "ShaderProgram.h"
#include <fstream>

ShaderProgram::ShaderProgram(void)
{
	mProgramID = NULL;
}


ShaderProgram::~ShaderProgram(void)
{
	mProgramID = NULL;
}

void ShaderProgram::bind()
{
	glUseProgram(mProgramID);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Programm could not be bound: %d\n",mProgramID);
	}
}

void ShaderProgram::unbind()
{
	glUseProgram(NULL);
}

GLuint ShaderProgram::getProgramID()
{
	return mProgramID;
}

GLuint ShaderProgram::loadShaderFromFile(std::string path,GLenum shaderType)
{
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile( path.c_str() );

	if(sourceFile)
	{
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)),std::istreambuf_iterator<char>() );
		shaderID = glCreateShader(shaderType);
		const GLchar* shaderSource= shaderString.c_str();
		glShaderSource(shaderID,1,(const GLchar**)&shaderSource,NULL);

		glCompileShader(shaderID);

		//Errors?
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID ,GL_COMPILE_STATUS ,&fShaderCompiled);
		if(fShaderCompiled != GL_TRUE)
		{
			printf("Shader could not be compiled %d | %s\n",shaderID,shaderSource);
			shaderID=0;
		}
	}
	else
	{
		printf("Unable to open file at %s\n",path.c_str());
	}
	return shaderID;
}