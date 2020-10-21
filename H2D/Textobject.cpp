#include "Textobject.h"

Font2D* Textobject::font=NULL;

void Textobject::setFont(Font2D* f)
{
	font = f;
}


Textobject::Textobject(void)
{
}


Textobject::~Textobject(void)
{
}

void Textobject::create(float x, float y,std::string t, float size)
{
	dimension=font->getTextDimensions(t);
	// Berechnung fehlt noch
	//pixelSize=();

	text=t;
	posX=x;
	posY=y;
}

RectSize Textobject::createBox(float x, float y, std::string t,float size)
{
	dimension=font->getTextDimensions(t);

	//pixelSize=();

	text=t;
	posX=x;
	posY=y;

	return dimension;
}

void Textobject::changeText(std::string t)
{
	dimension=font->getTextDimensions(t);
	text=t;
}

void Textobject::changePosition(float x,float y)
{
	posX=x;
	posY=y;
}

void Textobject::render()
{
	font->renderText(posX,posY,text,pixelSize);
}