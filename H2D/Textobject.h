#pragma once

#include "OpenGLH.h"
#include "Engine.h"
#include "Rect.h"


class Textobject
{
public:
	Textobject(void);
	~Textobject(void);

	static void setFont(Font2D* f);

	void create(float x, float y,std::string t, float size);
	RectSize createBox(float x, float y, std::string t,float size);

	void changeText(std::string t);
	void changePosition(float x,float y);
	void render();

	
private:
	std::string text;
	RectSize dimension;
	float pixelSize;
	float posX,posY;
	static Font2D* font;


};

