#pragma once


#include "OpenGLH.h"
#include "TexturedPolygon2D.h"
#include "Rect.h"


class Texture2D
{
public:
	Texture2D(void);
	~Texture2D(void);

	static void setTexturedPolygonProgram2D(TexturedPolygon2D* program);

	//Pixel32
	bool loadTextureFromFile32(std::string path);
	
	bool loadPixelsFromFile32(std::string path);
	bool loadPixelsFromFile8(std::string path);

	bool loadTextureFromPixels32();
	bool loadTextureFromPixels8();
	
	bool loadTextureFromPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight);
	
	bool loadScreenshotFromPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight);
	void createScreenTexture(int w,int h);
	void changeScreenTextureSize();

	void createPixels32(GLuint imgWidth,GLuint imgHeight);
	void createPixels8(GLuint imgWidth,GLuint imgHeight);

	void copyPixels32(GLuint* pixels, GLuint imgWidth,GLuint imgHeight);
	void copyPixels8(GLubyte* pixels, GLuint imgWidth,GLuint imgHeight);

	void padPixels32();
	void padPixels8();

	GLubyte* padPixels8(GLubyte* pixels);

	void blitPixels32(GLuint x, GLuint y, Texture2D& destination);
	void blitPixels8(GLuint x, GLuint y, Texture2D& destination);	

	//allgemein
	void render(GLfloat x, GLfloat y, GLfloat sx = 1.f, GLfloat sy = 1.f, GLfloat rz = 0.f,GLfloat rPointX=0.f,GLfloat =0.f);
	void render(GLfloat x, GLfloat y, Color4f color, GLfloat sx = 1.f, GLfloat sy = 1.f, GLfloat rz = 0.f, GLfloat rPointX = 0.f, GLfloat = 0.f);
	void renderVAO(GLuint fVAO,GLfloat x, GLfloat y, GLfloat sx = 1.f, GLfloat sy = 1.f, GLfloat rz = 0.f,GLfloat rPointX=0.f,GLfloat =0.f);
	void renderFast(b2Vec2 pos);

	GLuint getTextureID();

	GLuint powerOfTwo(GLuint num);

	void initVAO(Rect* clip=NULL);
	GLuint initVAOf(Rect* clip,bool invert=false);

	GLuint* getPixelData32();
	GLubyte* getPixelData8();

	GLuint getPixel32(GLuint x, GLuint y);
	GLubyte getPixel8(GLuint x, GLuint y);

	void setPixel32(GLuint x, GLuint y, GLuint pixel);
	void setPixel8(GLuint x, GLuint y, GLubyte pixel);

	//Get-Methoden | Set-Methoden

	GLuint getImgHeight();
	GLuint getImgWidth();
	GLuint getTexWidth()	{ return mTextureWidth; }
	GLuint getTexHeight()	{ return mTextureHeight; }

protected:
	static TexturedPolygon2D* mTexturePolygonProgram2D;

	GLuint mTextureID;

	GLuint* mPixels32;
	GLubyte* mPixels8;

	GLuint mTextureWidth;
	GLuint mTextureHeight;

	GLuint mImgWidth;
	GLuint mImgHeight;

	GLuint mPixelFormat;

	GLuint mVBOID;
	GLuint mIBOID;
	GLuint mVAOID;

};

extern Texture2D scTexture;