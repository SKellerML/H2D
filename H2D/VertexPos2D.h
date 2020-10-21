#pragma once

#include "OpenGLH.h"

struct VertexPos2D
{
	GLfloat x;
	GLfloat y;
};

struct TexCoord
{
	GLfloat s;
	GLfloat t;
};

struct TexturedVertexPos2D
{
	VertexPos2D pos;
	TexCoord texCoord;
};

struct TextureVAO
{
	GLuint VAO;
	GLuint textureID;
};