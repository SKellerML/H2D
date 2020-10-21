#pragma once

#include "OpenGLH.h"
#include "FontObject.h"
#include "GUI.h"

const int MAX_CHARS=20;

/*
	DOES NOT WORK ON Pos2D(50.f,200.f);
*/

class GUITextfield : public GUI
{
public:
	GUITextfield(void);
	~GUITextfield(void);

	void create(b2Vec2 pos,GLfloat parentX=0.f,GLfloat parentY=0.f,Color4f col=Color4f(0.f,0.f,0.f,1.f));
	bool isHovered();
	bool update();
	Pos2D getCenter();
	void render();
	std::string getValue();

private:
	GLfloat parX,parY;
	FontObject text;
	Color4f textColor;
	b2Vec2 m_upperLeft;
	b2Vec2 m_size;
	b2Vec2 m_position;
	b2Vec2 textPos;
	GLuint sheetID;

	double lastActionTick;
};

