#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "FontObject.h"
#include "Square2D.h"


class GUISlider : public GUI
{
public:
	GUISlider(void);
	~GUISlider(void);


	void create(Pos2D pos,GLfloat width,GLfloat minValue,GLfloat maxValue,GLuint number_Of_Steps,Pos2D parentPosition=Pos2D(0.f,0.f),Color4f col=Color4f(1.f,1.f,1.f,1.f));
	bool isHovered();
	bool isHoveredSlider();
	bool update();
	Pos2D getCenter();
	void render();
	GLfloat getValue();

private:

	Rect position;
	Pos2D parentPos;
	Pos2D sliderPos;
	GLuint bar;
	bool sliderPressed;


	GLfloat sliderMouseDifferenceX;

	GLfloat minV,maxV,stepSize;
	GLint numberOfSteps,currentStep;

	FontObject text;
	Color4f barColor;

	GLuint sheetID;

	double lastActionTick;
};

