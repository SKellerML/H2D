#pragma once

#include "OpenGLH.h"
#include "Rect.h"
#include "ElementProgram.h"

#include <Box2D\Box2D.h>
#include <vector>

class Element2D
{
public:
	Element2D(void);
	~Element2D(void);

	static void loadElementProgram();

	void initElement(std::vector<b2Vec2>* vertices);
	
	bool updateVertex(GLuint vertexID,b2Vec2 vertexData);
	//void updateVertices(std::vector<b2Vec2>* vertices);

	void setColor(Color4f color)	{ m_color = color; }
	virtual void render(b2Vec2 pos=b2Vec2(0.f,0.f),GLfloat angle=0.f)=0;

protected:
	static ElementProgram elementProgram;

	GLuint mVBOID;
	GLuint mVAOID;
	GLuint drawingType;	// type of GL Drawing Method e.g. GL_LINES
	GLuint amountOfVertices;

	std::vector<b2Vec2> m_vertices;
	Color4f m_color;
};

class ElementLines : public Element2D	// also handles points
{
public:
	void initElement(std::vector<b2Vec2>* vertices,GLfloat width,Color4f color,GLushort pattern=0xFFFF,GLfloat factor=1,bool singleLine = true);

	void render(b2Vec2 pos=b2Vec2(0.f,0.f),GLfloat angle=0.f);

private:
	GLfloat m_linewidth;
	GLushort m_pattern;
	GLfloat m_factor;
};

class ElementPolygon : public Element2D
{
public:
	void initElement(std::vector<b2Vec2>* vertices,Color4f color);
	void render(b2Vec2 pos=b2Vec2(0.f,0.f),GLfloat angle=0.f);
};