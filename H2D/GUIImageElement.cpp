#include "GUIImageElement.h"


GUIImageElement::GUIImageElement(void)
{
	m_spriteSheet=NULL;
}


GUIImageElement::~GUIImageElement(void)
{
	m_spriteSheet=NULL;


}

void GUIImageElement::create(b2Vec2 position,b2Vec2 parentPosition,SpriteSheet2D* spriteSheet,GLuint spriteID,GLuint returnValue,bool isHoverable)
{
	m_position=position;
	

	m_parentPosition=parentPosition;

	m_spriteSheet=spriteSheet;
	m_spriteID=spriteID;

	m_size.Set(m_spriteSheet->getRectVAO(spriteID).r.w,m_spriteSheet->getRectVAO(spriteID).r.h);

	m_returnValue=returnValue;

	m_isHoverable=isHoverable;	// for hovering the next sprite on the spriteSheet is used
	m_isHovered=false;
}

bool GUIImageElement::isHovered()
{	m_isHovered = Engine::mouseHoverCenter(m_position,m_size,m_parentPosition.x,m_parentPosition.y);
	return m_isHovered;
}
GLuint GUIImageElement::update()
{
	if(isHovered())
	{
		return m_returnValue;
	}
	return -1;
}
void GUIImageElement::render()
{
	if(m_isHoverable && m_isHovered) m_spriteSheet->renderSprite(m_spriteID+1,m_position.x+m_parentPosition.x,m_position.y+m_parentPosition.y);
	else m_spriteSheet->renderSprite(m_spriteID,m_position.x+m_parentPosition.x,m_position.y+m_parentPosition.y);
}
