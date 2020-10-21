#include "GUISlider.h"
#include <cmath>

GUISlider::GUISlider(void)
{
	sliderPressed=false;
}


GUISlider::~GUISlider(void)
{
}

void GUISlider::create(Pos2D pos,GLfloat width,GLfloat minValue,GLfloat maxValue,GLuint number_Of_Steps,Pos2D parentPosition,Color4f col)
{
	RectSize size(width,32.f);
	position=Rect(pos,size);
	parentPos=parentPosition;
	
	minV=minValue;
	maxV=maxValue;

	numberOfSteps=number_Of_Steps-1;
	currentStep=ceil((float)numberOfSteps/2);
	stepSize=position.w/numberOfSteps;

	barColor=col;

	sliderPos=Pos2D(position.x+position.w/2-16.f,position.y);

	bar=Square2D::initVAO(&Rect(0.f,0.f,size.w,12.f),0.f);
}

bool GUISlider::isHovered()
{
	return (Engine::mouseHover(position,parentPos.x,parentPos.y));
}

bool GUISlider::isHoveredSlider()
{
	return (Engine::mouseHover(Rect(sliderPos,RectSize(32.f,32.f)),parentPos.x,parentPos.y));
}

bool GUISlider::update()
{
	if(sliderPressed)
	{
		sliderPos.x=Engine::mouse_x-sliderMouseDifferenceX-parentPos.x;

		if(sliderPos.x <= position.x)
		{
			sliderPos.x=position.x-16.f;
		}
		else if(sliderPos.x >= position.w-16.f)
		{
			sliderPos.x=position.x+position.w;
		}

		for(int i=numberOfSteps;i >= 0;i--)
		{
			if(sliderPos.x >= position.x+(i*stepSize)-(stepSize/2) && sliderPos.x <= parentPos.x+position.x+(i*stepSize)+(stepSize/2))
			{
				currentStep=i;
				sliderPos.x = position.x + i*stepSize-16.f;
				i=-1;
			}
		}

		if(!GameState::handler->isPressedBS(GUIHandler::B_S_CONFIRM))
		{
			sliderPressed=false;
		}
	}
	else if(isHovered())
	{
		// Maus
		if(GameState::handler->isPressedBS(GUIHandler::B_S_CONFIRM))
		{
			if(isHoveredSlider() && !sliderPressed)
			{
				sliderMouseDifferenceX=Engine::mouse_x-(sliderPos.x+parentPos.x);
			}
			sliderPressed=true;
		}
		else if(sliderPressed)
		{
			sliderPressed=false;
		}

		// Keys
		if(GameState::handler->isPressed(GUIHandler::KEY_LEFT))
		{
			currentStep--;
			if(0 >= currentStep )
			{
				sliderPos.x=position.x-16.f;
				currentStep=0;
			}
			else
			{
				sliderPos.x-=stepSize;
			}
			/*else
			{
				sliderPos.x-=25.f;
			}*/
		}
		else if(GameState::handler->isPressed(GUIHandler::KEY_RIGHT))
		{
			currentStep++;

			if(currentStep >= numberOfSteps)
			{
				sliderPos.x=position.x+position.w-16.f;
				currentStep=numberOfSteps;
			}
			else
			{
				sliderPos.x+=stepSize;
			}
		}
		//printf("Step: %i\n",currentStep);

	}
	/*
	if(sliderPressed && !GameState::handler->isPressedBS(GUIHandler::B_S_CONFIRM))
	{
		sliderPressed=false;
	}
	*/
	return sliderPressed;
}

Pos2D GUISlider::getCenter()
{
	return Pos2D(floor(parentPos.x+position.x+position.w/2)+0.3f,floor(parentPos.y+position.y+position.h/2)+0.3f);
}

void GUISlider::render()
{
	// Render bar

	Engine::borderPolyProgram.bind();
	//Engine::borderPolyProgram.setColor(col);
	Square2D::render(bar,position.x+parentPos.x,position.y+10.f+parentPos.y,1.f,1.f,0.f,&barColor);
	// Render slider Element
	if(isHovered() || sliderPressed)
	{
		guiSheet[0].renderSprite(GUI_TEX_SLIDER_SELECTED,sliderPos.x+parentPos.x,sliderPos.y+parentPos.y);
	}
	else
	{
		guiSheet[0].renderSprite(GUI_TEX_SLIDER,sliderPos.x+parentPos.x,sliderPos.y+parentPos.y);
	}
}

GLfloat GUISlider::getValue()
{
	return ((maxV-minV)/numberOfSteps)*currentStep+minV;
}