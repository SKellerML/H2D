#pragma once

#include "OpenGLH.h"
#include "GUI_H.h"
#include "GUIMapItem.h"

class GUIMap
{
public:
	GUIMap(void);
	~GUIMap(void);

	void init(GLuint currentActiveMapItem=0);
	GLint update();
	void render();

private:
	typedef std::map<GLuint,b2Vec2> ConnectedItemsMap;
	bool isLoaded;

	b2Vec2 m_position;
	GLuint m_currentActiveMapItem;

	std::vector<GUIMapItem> mapElements;

	Texture2D background;
	SpriteSheet2D mapSpriteSheet;

	GUIButtonTextured button_back;

};

