#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "Square2D.h"
#include "FontObject.h"

class GUILabel : public GUI
{
public:
	GUILabel(void);
	~GUILabel(void);

	bool create(Pos2D pos,Pos2D parentPosition,float w,float h,std::string *t,GLfloat fontSize=20.f,float r=0.f, float g=0.f, float b=1.f, float a=1.f);
	void render();

private:
	Rect position;
	Pos2D parentPos;
	float textX,textY,textSize;
	FontObject text;
	Color4f color;
	GLuint mVAO;

};

