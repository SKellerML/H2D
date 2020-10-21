#include "GUI.h"

Color4f GUI::standardColor(0.f,0.f,0.f,1.f);
std::vector<SpriteSheet2D> GUI::guiSheet;
Font2D* GUI::font;

void GUI::setFont(Font2D* f)
{
	font = f;
}

GLshort GUI::addSpriteSheet(std::string *pathS)
{
	// Safe data in external file to load with each picture, changeable file path?
	SpriteSheet2D x;

	guiSheet.push_back(x);
	
	int num=guiSheet.size()-1;
	guiSheet[num].loadTextureFromFile32(*pathS);
	// Buttons
	guiSheet[num].addClipSprite(Rect(0.f,0.f,96.f,32.f));
	guiSheet[num].addClipSprite(Rect(0.f,32.f,96.f,32.f));
	guiSheet[num].addClipSprite(Rect(0.f,64.f,96.f,32.f));
	guiSheet[num].addClipSprite(Rect(0.f,96.f,96.f,32.f));
	// Panel
	guiSheet[num].addClipSprite(Rect(0.f,128.f,576.f,448.f));
	// Arrow
	guiSheet[num].addClipSprite(Rect(96.f,0.f,32.f,32.f));
	// Textfield
	guiSheet[num].addClipSprite(Rect(128.f,0.f,TEXTFIELD_WIDTH,32.f));
	guiSheet[num].addClipSprite(Rect(128.f,32.f,TEXTFIELD_WIDTH,32.f));
	// Slider
	guiSheet[num].addClipSprite(Rect(97.f,33.f,31.f,31.f)); //+/-1
	guiSheet[num].addClipSprite(Rect(97.f,65.f,31.f,31.f)); //+/-1
	return num;
}

void GUI::deleteGuiSheet()
{
	//guiSheet.~SpriteSheet2D();
}

GUI::GUI(void)
{

}


GUI::~GUI(void)
{

}
