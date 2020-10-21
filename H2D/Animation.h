#pragma once

#include "OpenGLH.h"
#include "SpriteSheet2D.h"
#include <Box2D\Box2D.h>
#include <map>
enum AnimationSheet
{
	ANIMATION_SHEET_ENGINES,
	ANIMATION_SHEET_EXPLOSIONS,
	ANIMATION_SHEET_LAST
};

enum AnimationList
{
	ANIMATION_ENGINE_DESTROYER,
	ANIMATION_EXPLOSION_1,
	ANIMATION_LAST,
};

struct AnimationData
{
	GLuint sheetID;
	GLuint firstSprite;
	GLuint numberOfSprites;
	GLuint framesPerSprite;
	GLuint animationDuration;
	bool ongoingAnimation;
};

class Animation
{
public:
	Animation(void);
	~Animation(void);

	static bool loadAnimations();
	//bool loadAnimation(GLuint animationSheetID,GLfloat singleSpriteWidth,GLfloat singleSpriteHeight,GLuint numberSprites,GLuint framesPerSprite, bool upToDownAnimation=true);
	bool loadAnimation(GLuint animationID);

	void updateAnimation(GLfloat speed,bool render);
	void renderAnimation(GLfloat x, GLfloat y, GLfloat sx=1.f, GLfloat sy=1.f, GLfloat rz=0.f,GLfloat rPointX=0.f,GLfloat =0.f);
	void renderAnimation(b2Vec2 position, GLfloat sx=1.f, GLfloat sy=1.f, GLfloat rz=0.f,GLfloat rPointX=0.f,GLfloat =0.f);

	void resetAnimation();
	bool isFinished();

	GLuint getAnimationDurationInFrames()	{return animationData[m_animationID].animationDuration;}

private:
	typedef std::map<int,SpriteSheet2D> SpriteSheetMap;
	static SpriteSheetMap spriteSheet;

	static std::vector<AnimationData> animationData;

	GLuint currentSprite;
	GLuint currentFrames;

	GLuint m_animationID;
	GLfloat m_speed;
	bool hasFinished;
	bool active;

	bool m_render;

};

