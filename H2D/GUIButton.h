#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "Rect.h"
#include "FontObject.h"

#include <Box2D\Box2D.h>

enum buttonType
{
	GUI_BUTTON_PLAIN_BACKGROUND,
	GUI_BUTTON_JUST_TEXT,
	GUI_BUTTON_TEXTURE_BACKGROUND,
	GUI_BUTTON_TEXTURE_BACKGROUND_DROPDOWN,
};

class GUIButton : public GUI
{
public:
	GUIButton(void);
	~GUIButton(void);

	void create(std::string t,GLshort returnV,Color4f textColor,Color4f textColorHover,b2Vec2 relPos,GLfloat parentX=0.f,GLfloat parentY=0.f,GLuint textSizeMax=22.f,RectSize size=standardButtonSize);
	GLshort update(); // checks if it is hovered over
	bool isHovered();
	Pos2D getCenter();
	void setSelected(bool s);
	virtual void render()=0;

	void setParentPosition(GLfloat parX,GLfloat parY);

	FontObject* getText();
	
	void setText(FontObject *t);
	// Create

	/*

	bool createPlainBackground(int x, int y,int px,int py,float w,float h,std::string t,GLshort returnV,Color4f textColor,Color4f backgroundColor,GLfloat padding=-1.f);
	bool createJustText(Rect sizes,GLfloat px,GLfloat py,std::string t,GLshort returnV,Color4f textColor,GLfloat padding=0.f);
	bool createDropdownButton(int x, int y,int px,int py,std::string t,GLshort returnV);

	// Change values
	void setPlainBackground(Color4f col);
	void setFontSizeMax(GLfloat s);

	*/

	// Get and Set Methods
	int getRV();


protected:
	static RectSize standardButtonSize;
	static GLfloat guiButtonPadding;
	static GLint guiButtonTextSizeMax;

	//Rect position;
	b2Vec2 m_position;
	b2Vec2 m_size;
	b2Vec2 m_upperLeft;
	FontObject text;
	GLfloat pX,pY;
	Color4f colNormal,colHover;
	int returnValue;
	bool isSelected;
};

class GUIButtonTextured : public GUIButton
{
public:

	GUIButtonTextured();
	~GUIButtonTextured();

	bool setTextureObject(int sheet = 0);
	void render();
private:
	int sheetID;
};

class GUIButtonTextOnly : public GUIButton
{
public:
	void render();
};

class GUIButtonPlain : public GUIButton
{
public:
	bool setBackground(Color4f backCol,Color4f backColHover);
	void render();
private:
	Color4f bCol,bColHover;
	GLuint mVAO;

};