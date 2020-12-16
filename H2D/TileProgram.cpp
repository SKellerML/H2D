#include "TileProgram.h"

#include <glm\gtc\type_ptr.hpp>

TileProgram::TileProgram()
{
}


TileProgram::~TileProgram()
{
}

bool TileProgram::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader, fragmentShader;

	vertexShader = loadShaderFromFile("TileProgram.glvs", GL_VERTEX_SHADER);

	glAttachShader(mProgramID, vertexShader);

	fragmentShader = loadShaderFromFile("TileProgram.glfs", GL_FRAGMENT_SHADER);

	glAttachShader(mProgramID, fragmentShader);

	if (vertexShader == 0 || fragmentShader == 0)
	{
		mProgramID = 0;
		return false;
	}

	glLinkProgram(mProgramID);

	GLint programSuccess = GL_FALSE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Could not link program %d\n", mProgramID);
		mProgramID = 0;
		return false;
	}

	mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "ProjectionMatrix");
	if (mProjectionMatrixLocation == -1)
	{
		printf("ProjectionMatrix is not a valid uniform\n");
	}
	mModelViewMatrixLocation = glGetUniformLocation(mProgramID, "ModelViewMatrix");
	if (mModelViewMatrixLocation == -1)
	{
		printf("ModelViewMatrix is not a valid uniform\n");
	}
	//mVertexPos2DLocation = glGetAttribLocation(mProgramID, "VertexPos2D");
	//if (mVertexPos2DLocation == -1)
	//{
	//	printf("VertexPos2D is not a valid attrib\n");
	//}
	//mTextureUnitLocation = glGetUniformLocation(mProgramID, "TextureUnit");
	//if (mTextureUnitLocation == -1)
	//{
	//	printf("TextureUnit is not a valid attrib\n");
	//}

	return true;
}

void TileProgram::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void TileProgram::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void TileProgram::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
}

void TileProgram::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
}

void TileProgram::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix = ModelViewMatrix*matrix;
}

void TileProgram::enableDataPointers()
{
	glEnableVertexAttribArray(mVertexPos2DLocation);
	//glEnableVertexAttribArray(0);
}

void TileProgram::setTextureUnit(GLuint unit)
{
	glUniform1i(mTextureUnitLocation, unit);
}

void TileProgram::setColor(Color4f color)
{
	//glUniform4f(mColorLocation, color.r, color.g, color.b, color.a);
}

void TileProgram::setVertexPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}