#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "Rect.h"

#include <Box2D\Box2D.h>

class GUIImageElement : public GUI
{
public:
	GUIImageElement(void);
	~GUIImageElement(void);

	void create(b2Vec2 position,b2Vec2 parentPosition,SpriteSheet2D* spriteSheet,GLuint spriteID,GLuint returnValue,bool isHoverable=false);

	bool isHovered();
	GLuint update();
	void render();

private:

	b2Vec2 m_position;
	b2Vec2 m_size;

	SpriteSheet2D* m_spriteSheet;
	GLuint m_spriteID;

	b2Vec2 m_parentPosition;

	bool m_isHoverable;
	bool m_isHovered;

	GLuint m_returnValue;

};

