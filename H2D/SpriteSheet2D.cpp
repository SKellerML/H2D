#include "SpriteSheet2D.h"
#include "Engine.h"

SpriteSheet2D::SpriteSheet2D(void) : Texture2D()
{


	mVAOID = 0;
	mTextureID=0;


	mTextureWidth= 0;
	mTextureHeight= 0;

	mImgWidth= 0;
	mImgHeight= 0;

	mPixelFormat= 0;

	mVBOID= 0;
	mIBOID= 0;
	mVAOID= 0;
}


SpriteSheet2D::~SpriteSheet2D(void)
{
}

int SpriteSheet2D::addClipSprite(Rect newClip,bool invert)
{
	RectVAO n;
	n.r = newClip;
	n.fVAO = initVAOf(&newClip,invert);
	mClips.push_back(n);
	return mClips.size()-1;
}

void SpriteSheet2D::renderSprite(int index,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	//Engine::textureProgram.bind();
	//Engine::textureProgram.setTextureColor(1.f,1.f,1.f,1.f);
	renderVAO(mClips[index].fVAO,x,y,sx,sy,rz,rPointX,rPointY);
}

void SpriteSheet2D::renderSprite(int index,GLfloat x, GLfloat y,Color4f color, GLfloat rz,GLfloat rPointX,GLfloat rPointY,GLfloat sx, GLfloat sy)
{
	//Engine::textureProgram.bind();
	Engine::textureProgram.setTextureColor(color.r,color.g,color.b,color.a);
	renderVAO(mClips[index].fVAO,x,y,sx,sy,rz,rPointX,rPointY);
	//Engine::textureProgram.bind();
	Engine::textureProgram.setTextureColor(1.f,1.f,1.f,1.f);
}

RectVAO SpriteSheet2D::getRectVAO(GLuint sprite)
{
	// sicherstellen dass nich jede zahl genommwen werden kann -> absturz
		return mClips[sprite];

}