#pragma once

#include "Rect.h"
#include "Font2D.h"
#include "Engine.h"
#include "SpriteSheet2D.h"
#include "GameState.h"
#include <cmath>
enum GuiSheetElements
{
	GUI_TEX_BUTTON = 0,
	GUI_TEX_BUTTON_HOVER = 1,
	GUI_TEX_DROPDOWN = 2,
	GUI_TEX_DROPDOWN_HOVER = 3,
	GUI_TEX_PANEL_BACKGROUND = 4,
	GUI_TEX_ARROW = 5,
	GUI_TEX_TEXTFIELD,
	GUI_TEX_TEXTFIELD_HOVERED,
	GUI_TEX_SLIDER,
	GUI_TEX_SLIDER_SELECTED,
};

const GLfloat TEXTFIELD_WIDTH=320.f;

class GUI
{
public:
	GUI(void);
	~GUI(void);

	/*
	virtual bool create()=0;
	virtual bool update()=0;
	virtual void render()=0;
	*/

	static void setFont(Font2D* f);
	static GLshort addSpriteSheet(std::string *pathS);
	static void deleteGuiSheet();

protected:
	Rect pos;
	bool isVisible;

	static Color4f standardColor;
	static std::vector<SpriteSheet2D> guiSheet;
	static Font2D* font;

};

