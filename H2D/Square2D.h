#pragma once

#include "OpenGLH.h"
#include "BorderPolygon2D.h"
#include "Rect.h"

class Square2D
{
public:
	Square2D(void);
	~Square2D(void);

	static void setBorderPolygon2D(BorderPolygon2D *polygonProgram);
	static void unsetBorderPolygon2D();

	static void render(GLuint vaoID,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,Color4f *color);

	static GLuint initVAO(Rect* clip,GLfloat thickness);

private:
	static BorderPolygon2D *mBorderProgram2D;
};

