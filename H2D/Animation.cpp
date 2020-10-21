#include "Animation.h"

Animation::SpriteSheetMap Animation::spriteSheet;
std::vector<AnimationData> Animation::animationData;

Animation::Animation(void)
{
	currentSprite=0;
	currentFrames=0;
	hasFinished=false;
	active = false;
}


Animation::~Animation(void)
{
}


bool Animation::loadAnimations()
{

	GLfloat singleSpriteWidth=0.f;
	GLfloat singleSpriteHeight=0.f;
	GLuint numSpritesH=0.f;
	GLuint numSpritesW=0.f;
	if(spriteSheet.size()!=0)	spriteSheet.clear();

	GLuint currentSpriteSheet=0;

	typedef std::pair<int,SpriteSheet2D> spriteSheetPair;

	// ANIMATION_SHEET_ENGINES	
	spriteSheet.insert(spriteSheetPair(currentSpriteSheet,SpriteSheet2D()));								
	spriteSheet[currentSpriteSheet].loadTextureFromFile32("Effects.png");

	singleSpriteWidth=38.f;
	singleSpriteHeight=18.f;
	numSpritesH = floor(spriteSheet[currentSpriteSheet].getImgHeight()/singleSpriteWidth);
	numSpritesW = floor(spriteSheet[currentSpriteSheet].getImgWidth()/singleSpriteHeight);

	for(int i=0; i < numSpritesW; i++)
	{
		for(int u=0; u < numSpritesH; u++)
		{
			spriteSheet[currentSpriteSheet].addClipSprite(Rect(i*singleSpriteWidth,u*singleSpriteHeight,singleSpriteWidth,singleSpriteHeight));
		}
	}
	//printf("Size: %i || %i \n",currentSpriteSheet,spriteSheet[currentSpriteSheet].getTextureID());
	


	// ANIMATION_SHEET_EXPLOSIONS
	spriteSheet.insert(spriteSheetPair(++currentSpriteSheet,SpriteSheet2D()));							
	spriteSheet[currentSpriteSheet].loadTextureFromFile32("explosionSheet.png");

	singleSpriteWidth=50.f;
	singleSpriteHeight=36.f;
	numSpritesH = floor(spriteSheet[currentSpriteSheet].getImgHeight()/singleSpriteHeight);
	numSpritesW = floor(spriteSheet[currentSpriteSheet].getImgWidth()/singleSpriteWidth);

	for(int i=0; i < numSpritesW; i++)
	{
		for(int u=0; u < numSpritesH; u++)
		{
			spriteSheet[currentSpriteSheet].addClipSprite(Rect(i*singleSpriteWidth,u*singleSpriteHeight,singleSpriteWidth,singleSpriteHeight));
		}
	}
	//printf("Size: %i || %i \n",currentSpriteSheet,spriteSheet[currentSpriteSheet].getTextureID());
	// Sheet 3


	/*
		Load Animations
	*/
	// 	ANIMATION_ENGINE_DESTROYER
	animationData.push_back(AnimationData());
	animationData[animationData.size()-1].sheetID=ANIMATION_SHEET_ENGINES;
	animationData[animationData.size()-1].numberOfSprites=3;
	animationData[animationData.size()-1].firstSprite=0;
	animationData[animationData.size()-1].framesPerSprite=10;
	animationData[animationData.size()-1].animationDuration = animationData[animationData.size()-1].numberOfSprites*animationData[animationData.size()-1].framesPerSprite ;
	animationData[animationData.size()-1].ongoingAnimation=true;

	// ANIMATION_EXPLOSION_1
	animationData.push_back(AnimationData());
	animationData[animationData.size()-1].sheetID=ANIMATION_SHEET_EXPLOSIONS;
	animationData[animationData.size()-1].numberOfSprites=4;
	animationData[animationData.size()-1].firstSprite=0;
	animationData[animationData.size()-1].framesPerSprite=4;
	animationData[animationData.size()-1].animationDuration = animationData[animationData.size()-1].numberOfSprites*animationData[animationData.size()-1].framesPerSprite ;
	animationData[animationData.size()-1].ongoingAnimation=false;
	

	return true;
};
//
//bool Animation::loadAnimation(GLuint animationSheetID,GLfloat singleSpriteWidth,GLfloat singleSpriteHeight,GLuint numberSprites,GLuint framesPerSprite, bool upToDownAnimation)
//{
//	numberOfSprites=0;
//
//		if(animationSheetID < ANIMATION_SHEET_LAST)	animationSheetID=0;
//
//		SpriteSheet2D* sheet=&spriteSheet[animationSheetID];
//		sheetID=animationSheetID;
//		standardFrames=framesPerSprite;
//
//		GLuint numSpritesH = floor(sheet->getImgHeight()/singleSpriteHeight);
//		GLuint numSpritesW = floor(sheet->getImgWidth()/singleSpriteWidth);
//
//		if(upToDownAnimation)
//		{
//			// Animate from up right to bottom left
//			for(int i=0; i < numSpritesW; i++)
//			{
//				for(int u=0; u < numSpritesH; u++)
//				{
//					sheet->addClipSprite(Rect(i*singleSpriteWidth,u*singleSpriteHeight,singleSpriteWidth,singleSpriteHeight));
//					numberOfSprites++;
//					if(numberSprites==numberOfSprites)
//					{
//						i=numSpritesW;
//						u=numSpritesH;
//					}
//				}
//			}
//		}
//		else	// leftToRightanimation
//		{
//			return false;
//		}
//	return true;
//}
//
bool Animation::loadAnimation(GLuint animationID)
{
	m_animationID=animationID;
	currentSprite=animationData[m_animationID].firstSprite;
	currentFrames=0;
	hasFinished=false;
	active = true;
	return true;
}

void Animation::updateAnimation(GLfloat speed, bool render)
{
	if(!render || !active) return;

	if(hasFinished)
	{
		if(animationData[m_animationID].ongoingAnimation) hasFinished=false;
		else m_render=false;
	}

	if(!hasFinished)
	{
		m_speed=speed;
		if(++currentFrames >= animationData[m_animationID].framesPerSprite*m_speed)
		{
			
			if(++currentSprite >= animationData[m_animationID].numberOfSprites)
			{
				currentSprite=animationData[m_animationID].firstSprite;
				hasFinished=true;
			}
			currentFrames=0;
		}

		m_render=render;
	}
}

void Animation::renderAnimation(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	if(m_render && active) spriteSheet[animationData[m_animationID].sheetID].renderSprite(currentSprite,x,y,sx,sy,rz,rPointX,rPointY);
}
void Animation::renderAnimation(b2Vec2 position, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	if(m_render && active) spriteSheet[animationData[m_animationID].sheetID].renderSprite(currentSprite,position.x,position.y,sx,sy,rz,rPointX,rPointY);
}

void Animation::resetAnimation()
{
	currentFrames=0;
	currentSprite=animationData[m_animationID].firstSprite;
}
bool Animation::isFinished()
{
	return hasFinished;
}