#pragma once

#include "OpenGLH.h"
#include "GUI.h"
#include "Rect.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "Texture2D.h"
#include "GUIDropdownList.h"
#include "GUITextfield.h"
#include "InputMapper.h"
#include "GUISlider.h"
#include "GUIImageElement.h"

#include <boost\smart_ptr.hpp>
#include <vector>
#include <boost\ptr_container\ptr_vector.hpp>

class GUIPanel : public GUI
{
public:

	enum elementTypes
	{
		ELEMENT_NONE,
		ELEMENT_BUTTON,
		ELEMENT_DROPDOWNLIST,
		ELEMENT_DROPDOWNLIST_INACTIVE,
		ELEMENT_TEXTFIELD,
		ELEMENT_LABEL,
		ELEMENT_SLIDER,
		ELEMENT_IMAGEELEMENT,
	};

	GUIPanel(void);
	~GUIPanel(void);

	bool create(std::string *titleText,Pos2D pos,RectSize size=RectSize(576.f,448.f),GLshort sheetNum=0);
	void setPos(Pos2D pos);
	GLshort update();
	void render();

	void setTextColor(Color4f tColor,Color4f tColorHover);
	void addButton(Pos2D pos,std::string t,int rv,bool textureBackground=true);
	//void addButtonTextOnly(Rect posAndSize,std::string t,int rv);

	int addDropdownList(Pos2D pos,std::string t,int rv);
	void addObjectDropdownList(int listId,std::string t,int rv);
	int addTextfield(b2Vec2 pos);
	int addLabel(Pos2D pos,RectSize size,std::string* tx);
	int addSlider(Pos2D pos,GLfloat width,GLfloat minValue,GLfloat maxValue,GLuint number_Of_Steps);
	
	int addImageElement(b2Vec2 pos,SpriteSheet2D* spriteSheet,GLuint spriteID,GLuint returnValue);
	/*
	void addButton(float x, float y, float w,float h,std::string t,GLshort type, int rv,Color4f tcol,Color4f *bCol=NULL); // rv=return Value
	void addButtonTexture(float x, float y, float w,float h,std::string t, int rv);
	void addLabel(float x, float y, float w,float h,std::string t);
	*/

	void setVisible(bool x);
	bool isVisible();

private:
	Rect position;
	FontObject text;
	GLshort sheetID;
	//GLshort selected; // Selected Element (by Mouse or key)
	bool visible;// Was the last action key/controller or mouse?
	bool cursorVisible;

	Color4f textColor,textColorHover;

	typedef std::pair<int,int> element; // every object in order has an ElementType
	element selected; // ElementType | id of type (buttons.size()-1) // Selected Element (by Mouse or key)
	bool lastActionKey;
	int keySelected;
	std::vector<element> elementOrder; // ElementType | id
	
	boost::ptr_vector<GUIButton> buttons;
	std::vector<GUILabel> labels;
	std::vector<GUIDropdownList> ddlist;
	std::vector<GUITextfield> txtfield;
	std::vector<GUISlider> slider;
	std::vector<GUIImageElement> imageElements;

	void setMouseToElement(int x);
	//Textfield
	//image
};

