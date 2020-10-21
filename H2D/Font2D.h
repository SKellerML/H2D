#pragma once

#include "Font2D.h"
#include "FontProgram2D.h"
#include "SpriteSheet2D.h"
#include "VertexPos2D.h"


enum FontTextAlignment
{
	FONT_TEXT_ALIGNMENT_LEFT = 1,
	FONT_TEXT_ALIGNMENT_CENTERED_H = 2,
	FONT_TEXT_ALIGNMENT_RIGHT = 4,
	FONT_TEXT_ALIGNMENT_TOP = 8,
	FONT_TEXT_ALIGNMENT_CENTERED_V = 16,
	FONT_TEXT_ALIGNMENT_BOTTOM = 32
};

class Font2D : public SpriteSheet2D
{
public:
	static void setFontProgram2D(FontProgram2D* program);
	static bool initFreeType();

	Font2D(void);
	~Font2D(void);

	bool loadBitmap(std::string path);

	bool loadFreeType(std::string path, GLuint pixelSize);

	void renderText( GLfloat x, GLfloat y, std::string text, int size=20);
    void renderText( GLfloat x, GLfloat y, std::string text, Rect *clip,int lines=1);
	Rect renderTextBox(GLfloat x, GLfloat y, std::string text);

	TextureVAO loadGlyph(GLubyte* pixels, GLuint imgWidth,GLuint imgHeight);

	GLfloat getSpace();
	GLfloat getLineHeight();
	GLfloat getNewLineHeight();
	GLfloat getLetterWidth(unsigned char letter);

	void setTextColor(float r,float g,float b,float a);
	void setTextColor(Color4f col);

	void drawFontSprite(GLuint fVAO,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz=0.f,GLfloat rPointX=0.f,GLfloat rPointY=0.f);

	RectSize getTextDimensions(std::string text);

private:
	GLfloat substringWidth(const char* substring);

	GLfloat stringHeight(const char* thisString);
	
	int addFontClipSprite(Rect newClip);

	GLuint initVAOfont(Rect* clip);

	static FontProgram2D* mFontProgram2D;

	 //static FT_Library mLibrary;

	GLuint letterVAO[256];

	GLfloat mSpace;
	GLfloat mNewLine;
	GLfloat mLineHeight;
};

