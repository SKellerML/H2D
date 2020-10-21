#pragma once

#include "OpenGLH.h"
#include "GameState.h"
#include "Game.h"
#include "GUIButton.h"
#include "GUIPanel.h"
#include "GUITextfield.h"

#include <boost\shared_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>

class StateMenu : public GameState
{
public:
	StateMenu(void)	{}
	~StateMenu(void)	{}

	void update(){}
	void renderBackground(){}
	void render(){}
	void updateRender(){}
	void renderFinal(){}
//
//private:
//	//std::vector<GUIButton*> buttons;
//
//	//std::vector<boost::shared_ptr<GUIButtonTextured> buttons> buttons;
//	boost::ptr_vector<GUIButton> buttons;
//	GLshort selected;
//
//	Texture2D background;
//
//	GUIButtonTextured testButt;
//	GUIDropdownList dlist;
//	GUIPanel panel;
//
//	GUITextfield txtfld;
//	

};

