#pragma once

#include "OpenGLH.h"
#include "Engine.h"
#include "Rect.h"
#include "Font2D.h"
/*
enum fontAlignment
{
	FONT_TEXT_ALIGNMENT_LEFT,
	FONT_TEXT_ALIGNMENT_CENTERED_H,
	FONT_TEXT_ALIGNMENT_RIGHT,
	FONT_TEXT_ALIGNMENT_TOP,
	FONT_TEXT_ALIGNMENT_CENTERED_V,
	FONT_TEXT_ALIGNMENT_BOTTOM
};
*/

class FontObject
{
public:
	FontObject(void);
	~FontObject(void);

	static void setFont2D(Font2D *f);

	/*
		FontObject Types:
			- Fit to Rect
			- Defined Fontsize, return Rect
	*/

	GLshort initFitToRect(std::string t,Rect size,GLfloat padding=1.f,GLuint alignmentH=FONT_TEXT_ALIGNMENT_LEFT,GLuint alignmentV=FONT_TEXT_ALIGNMENT_TOP,GLshort maxFontSize=-1);
	
	Rect init(std::string t,GLshort fontSize, GLfloat padding=1.f);

	GLfloat initWrap(std::string t,GLshort fontSize,GLfloat width,GLfloat padding=1.f,GLuint alignmentH=FONT_TEXT_ALIGNMENT_LEFT,GLuint alignmentV=FONT_TEXT_ALIGNMENT_TOP);

	void setTextColor(Color4f col);

	void updateText(std::string t);
	std::string *getText();

	void render(GLfloat x,GLfloat y);


private:

	enum TextType
	{
		TEXT_FIT_TO_RECT,
		TEXT_NORMAL,
		TEXT_WRAP,
	};

	static Font2D *font;

	Color4f textColor;

	GLint textType;

	Rect position;
	GLfloat pad;
	GLuint alignH,alignV;
	GLshort maxSize;


	GLint fontSize;
	GLfloat posX;
	GLfloat posY;
	GLfloat length;
	GLfloat height;
	std::string text;



};

