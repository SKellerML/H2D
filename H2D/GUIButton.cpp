#include "GUIButton.h"
#include "Square2D.h"

#include <vector>

RectSize GUIButton::standardButtonSize(96.f,32.f);
GLfloat GUIButton::guiButtonPadding=5.f;
GLint GUIButton::guiButtonTextSizeMax=22;


GUIButton::GUIButton(void)
{
	returnValue=-1;
	isSelected=false;
}


GUIButton::~GUIButton(void)
{
	returnValue=-1;
	isSelected=false;
}

void GUIButton::create(std::string t,GLshort returnV,Color4f textColor,Color4f textColorHover,b2Vec2 relPos,GLfloat parentX,GLfloat parentY,GLuint textSizeMax,RectSize size)
{
	colNormal=textColor;
	colHover=textColorHover;	

	//position.x=relPos.x;
	//position.y=relPos.y;
	
	m_position=relPos;
	m_size.Set(size.w,size.h);
	m_upperLeft.Set(m_position.x-m_size.x/2,m_position.y+m_size.y/2);


	pX=parentX;
	pY=parentY;

	//position.w=size.w;
	//position.h=size.h;


	text.initFitToRect(t,Rect(m_upperLeft,size),guiButtonPadding,FONT_TEXT_ALIGNMENT_CENTERED_H,FONT_TEXT_ALIGNMENT_CENTERED_V,textSizeMax);
	//text.setTextColor(standardColor);

	returnValue=returnV;
}

void GUIButton::setSelected(bool s)
{
	isSelected=s;
}

bool GUIButton::isHovered()
{
	return Engine::mouseHover(m_upperLeft,m_size,pX,pY);
}

Pos2D GUIButton::getCenter()
{
	return Pos2D(floor(pX+(m_position.x+(m_size.x/2)))+0.3f,floor(pY+(m_position.y+(m_size.y/2))+0.3f));
}

GLshort GUIButton::update()
{
	// if true -> select

		if(Engine::mouseHover(m_upperLeft,m_size,pX,pY))
		{
			isSelected=true;
			if(GameState::handler->isPressed(GUIHandler::KEY_CONFIRM) || GameState::handler->isPressedB(GUIHandler::B_CONFIRM))
			{
				return returnValue;
			}
			else
				return -1;
		}
		else
		{
			isSelected=false;
			return -1;
		}
	/*
	if(isSelected && (Engine::mouse_left || k_enter))
	{
		return returnValue;
	}*/
	return -1;
}

void GUIButton::setParentPosition(GLfloat parX,GLfloat parY)
{
	pX=parX;
	pY=parY;
}

FontObject* GUIButton::getText()
{
	return &text;
}

void GUIButton::setText(FontObject *t)
{
	text=*t;
}

int GUIButton::getRV()
{
	return returnValue;
}

/*
	Textured Button ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

GUIButtonTextured::GUIButtonTextured()
{
	sheetID=0;
}
GUIButtonTextured::~GUIButtonTextured()
{

}

bool GUIButtonTextured::setTextureObject(int sheet)
{
	sheet=sheet;

	return true;
}

void GUIButtonTextured::render()
{
	if(isSelected)
	{
		guiSheet[sheetID].renderSprite(GUI_TEX_BUTTON,m_position.x+pX,m_position.y+pY);
		text.setTextColor(colHover);
	}
	else
	{
		guiSheet[sheetID].renderSprite(GUI_TEX_BUTTON_HOVER,m_position.x+pX,m_position.y+pY);
		text.setTextColor(colNormal);
	}

	text.render(pX+m_position.x,pY+m_position.y);
}

/*
	Text Only Button ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void GUIButtonTextOnly::render()
{
	if(isSelected)
	{
		text.setTextColor(colHover);
	}
	else
	{
		text.setTextColor(colNormal);
	}

	text.render(pX+m_position.x,pY+m_position.y);
}

/*
	Plain Background Button ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
bool GUIButtonPlain::setBackground(Color4f backCol,Color4f backColHover)
{
	Rect a=Rect(m_position.x,m_position.y,m_size.x,m_size.y);
	mVAO=Square2D::initVAO(&a,20.f);
	bCol=backCol;
	bColHover=backColHover;

	return true;
}

void GUIButtonPlain::render()
{
	Engine::borderPolyProgram.bind();
	if(isSelected)
	{
		Square2D::render(mVAO,pX+m_position.x,pY+m_position.y,1.f,1.f,0.f,&bColHover);
		text.setTextColor(colHover);
	}
	else
	{
		Square2D::render(mVAO,pX+m_position.x,pY+m_position.y,1.f,1.f,0.f,&bCol);
		text.setTextColor(colNormal);
	}
	text.render(pX+m_position.x,pY+m_position.y);
}