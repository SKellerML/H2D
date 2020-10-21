#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "GUIButton.h"

#include "Texture2D.h"

class GUIDropdownList : public GUI
{
public:
	GUIDropdownList(void);
	~GUIDropdownList(void);

	void create(Pos2D pos,std::string text,GLshort returnValue,GLfloat parentX,GLfloat parentY);
	void addObject(std::string text,GLshort returnValue);

	GLshort getSelectedValue();

	bool isHovered();
	bool update(); // return true if active
	Pos2D getCenter();
	void render();

	// Get and Set Methods


private:

	//GUIButton main;
	std::vector<GUIButtonTextured> objects;
	GLshort keySelected;

	Rect size;
	GLfloat pX,pY;

	Color4f txtCol,txtColHover;

	int selectedValue;
	bool lastActionKey;
	bool cursorVisible;
	bool mainHovered;
	bool isSelectedKey;
	bool unfolded;

	Texture2D arrow;
};

