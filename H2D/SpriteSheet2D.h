#pragma once

#include <vector>

#include "Texture2D.h"
#include "Rect.h"

class SpriteSheet2D : public Texture2D
{
public:
	SpriteSheet2D(void);
	~SpriteSheet2D(void);

	int addClipSprite(Rect& newClip,bool invert = false);

	void renderSprite(int index,GLfloat x, GLfloat y, GLfloat sx=1.f, GLfloat sy=1.f, GLfloat rz=0.f,GLfloat rPointX=0.f,GLfloat rPointY=0.f);
	void renderSprite(int index,GLfloat x, GLfloat y,Color4f color, GLfloat rz=0.f,GLfloat rPointX=0.f,GLfloat rPointY=0.f,GLfloat sx=1.f, GLfloat sy=1.f);
	RectVAO getRectVAO(GLuint sprite);

protected:
	std::vector<RectVAO> mClips;
};

