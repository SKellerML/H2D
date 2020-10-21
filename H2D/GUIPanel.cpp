#include "GUIPanel.h"
#include "Square2D.h"


GUIPanel::GUIPanel(void)
{
}


GUIPanel::~GUIPanel(void)
{
}

bool GUIPanel::create(std::string *titleText,Pos2D pos,RectSize size,GLshort sheetNum)
{
	position=Rect(pos,size);
	
	text.init(*titleText,20.f,5.f);

	sheetID=sheetNum;

	textColor=Color4f(0.f,0.f,0.f,1.f);
	textColorHover=Color4f(0.f,0.f,0.f,1.f);
/*
	Rect xxx(700.f,750.f,150.f,25.f);
	
	list.createDropdownList(xxx,"List Test",0);
	list.addObject("Hello",1);
	list.addObject("He3llo",2);
	list.addObject("He4llo",3);
	list.addObject("He5llo",4);
	list.addObject("He6llo",5);
	*/
	lastActionKey=false;
	cursorVisible=false;
	keySelected=0;

	return true;
}

void GUIPanel::setPos(Pos2D pos)
{
	position.x=pos.x;
	position.y=pos.y;
}


GLshort GUIPanel::update()
{
	/*
		Panel ToDo:

		Key über Mouse verschieben

			Passe an mit Hover und Rendered Bild verändern:
				Buttons update();
				Dropdownlist update();
				Textfield update();
	*/
	
		//Update everything and let them check for mouseHover themselve.


	// Buttons
	int selected_now;
	for(int i=(buttons.size()-1);i>=0;i--)
	{
		if((selected_now=buttons[i].update())!=-1) // Wenn die Maus darüber hovered
		{
			//selected.first=ELEMENT_BUTTON;
			//selected.second=selected_now;
			return buttons[i].getRV();
		}
	}
	// Image Elements (they are just like buttons)
	for(int i=(imageElements.size()-1);i>=0;i--)
	{
		if((selected_now=imageElements[i].update())!=-1) // Wenn die Maus darüber hovered
		{
			//selected.first=ELEMENT_BUTTON;
			//selected.second=selected_now;
			return buttons[i].getRV();
		}
	}
	// Dropdown Lists
		for(int i=ddlist.size()-1;i>=0;i--)
		{
			if(ddlist[i].update())
			{
				selected.first=ELEMENT_DROPDOWNLIST;
				return -1;
			}
		}
	// Textfields
	for(int i=txtfield.size()-1;i>=0;i--)
	{
		txtfield[i].update();
	}
	// Slider
	for(int i=slider.size()-1;i>=0;i--)
	{
		if(slider[i].update())
		{
			return -1;
		}
	}





	if(!Engine::getMouseActive(0.05))
	{
		//If next or previous key is pressed set MousePos to next Object
		if(GameState::handler->isPressed(GUIHandler::KEY_NEXT_ELEMENT)) // Nach Unten
		{
			if(keySelected<0)
			{
				keySelected=0;
			}
		
			if(elementOrder.size()-1 > keySelected)
			{
				keySelected+=1;
			}
			selected=elementOrder[keySelected];
			lastActionKey=true;
		}
		else if(GameState::handler->isPressed(GUIHandler::KEY_PREVIOUS_ELEMENT)) // Nach Oben
		{	
			if(keySelected<0)
			{
				keySelected=0;
			}

			if(keySelected > 0)
			{
				keySelected-=1;
			}
			selected=elementOrder[keySelected];
			lastActionKey=true;
		}

		
		if(lastActionKey)
		{
			if(!cursorVisible)
			{
				glfwSetInputMode(Engine::getWindow(),GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
				cursorVisible=true;
			}

				switch(selected.first)
				{
				case ELEMENT_BUTTON:
					Engine::setMousePos(buttons[selected.second].getCenter());
					break;
				case ELEMENT_DROPDOWNLIST: 
					Engine::setMousePos(ddlist[selected.second].getCenter());
					break;
				case ELEMENT_TEXTFIELD:
					Engine::setMousePos(txtfield[selected.second].getCenter());		
					break;
				case ELEMENT_LABEL:
					break;
				case ELEMENT_SLIDER:
					Engine::setMousePos(slider[selected.second].getCenter());
					break;
				default:
					break;
				}
		}
	}
	else
	{
		if(!lastActionKey)
		{
			if(cursorVisible)
			{
				glfwSetInputMode(Engine::getWindow(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
				cursorVisible=false;
			}
		}
		lastActionKey=false;
	}

	return -1;
}

void GUIPanel::render()
{
	if(visible)
	{
		//Render Squares
		//Engine::borderPolyProgram.bind();
		//Square2D::render(mVAO,position.x,position.y,1.f,1.f,0.f,&color);
		guiSheet[sheetID].renderSprite(GUI_TEX_PANEL_BACKGROUND,position.x,position.y);

		//Render Text
		//text.render(position.x+25.f,position.y+25.f);

	
		// Render Button
		for(int i=(buttons.size()-1);i>=0;i--)
		{
			buttons[i].render();
		}
		// Render DropdownLists
		for(int i=(ddlist.size()-1);i>=0;i--)
		{
			ddlist[i].render();
		}
		// Render Textfields
		for(int i=(txtfield.size()-1);i>=0;i--)
		{
			txtfield[i].render();
		}
		// Render Labels
		for(int i=(labels.size()-1);i>=0;i--)
		{
			labels[i].render();
		}
		// Render Slider
		for(int i=(slider.size()-1);i>=0;i--)
		{
			slider[i].render();
		}
		// Render ImageElements
		for(int i=(imageElements.size()-1);i>=0;i--)
		{
			imageElements[i].render();
		}
		//Render Labels
		/*
		for(int i=(labels.size()-1);i>=0;i--)
		{
			labels[i].render();
		}
		*/
		//list.render();

		//buttonok.render();
	}
}

void GUIPanel::setTextColor(Color4f tColor,Color4f tColorHover)
{
	textColor=tColor;
	textColorHover=tColorHover;
}

void GUIPanel::addButton(Pos2D pos,std::string t,int rv,bool textureBackground)
{
		if(textureBackground)
		{
			GUIButtonTextured *butt=new GUIButtonTextured;
			butt->create(t,rv,textColor,textColorHover,b2Vec2(pos.x,pos.y),position.x,position.y);
			butt->setTextureObject(sheetID);
			buttons.push_back(butt);
		}
		else
		{
			GUIButtonTextOnly *butt=new GUIButtonTextOnly;
			butt->create(t,rv,textColor,textColorHover,b2Vec2(pos.x,pos.y),position.x,position.y);
			buttons.push_back(butt);
		}
		// Add Element to Order
	
		element x;
		x.first=ELEMENT_BUTTON;
		x.second=buttons.size()-1;//rv
		elementOrder.push_back(x);
}

int GUIPanel::addDropdownList(Pos2D pos,std::string t,int rv)
{
	GUIDropdownList xlist;
	xlist.create(pos,t,rv,position.x,position.y);
	ddlist.push_back(xlist);

	element x;
	x.first=ELEMENT_DROPDOWNLIST;
	x.second=ddlist.size()-1;
	elementOrder.push_back(x);
		

	return ddlist.size()-1;
}
void GUIPanel::addObjectDropdownList(int listId,std::string t,int rv)
{
	if(listId >= 0 || listId < ddlist.size())
	{
		ddlist[listId].addObject(t,rv);
	}
}

int GUIPanel::addTextfield(b2Vec2 pos)
{
	GUITextfield xfield;
	xfield.create(pos,position.x,position.y);
	txtfield.push_back(xfield);

	element x;
	x.first=ELEMENT_TEXTFIELD;
	x.second=txtfield.size()-1;
	elementOrder.push_back(x);

	return elementOrder.size()-1;
}

int GUIPanel::addLabel(Pos2D pos,RectSize size,std::string* tx)
{
	GUILabel l;
	l.create(pos,Pos2D(position.x,position.y),size.w,size.h,tx);
	labels.push_back(l);
	/*
	element x;
	x.first=ELEMENT_LABEL;
	x.second=labels.size()-1;
	elementOrder.push_back(x);
	*/
	return labels.size()-1;
}

int GUIPanel::addImageElement(b2Vec2 pos,SpriteSheet2D* spriteSheet,GLuint spriteID,GLuint returnValue)
{
	imageElements.push_back(GUIImageElement());
	GLuint id=imageElements.size()-1;

	imageElements[id].create(pos,b2Vec2(position.x,position.y),spriteSheet,spriteID,returnValue);

	return id;
}

void GUIPanel::setVisible(bool x)
{
	visible=x;
}

bool GUIPanel::isVisible()
{
	return visible;
}

void GUIPanel::setMouseToElement(int x)
{
	if(x > elementOrder.size())
	{
		switch(elementOrder[x].first)
		{
			case ELEMENT_BUTTON:
				Engine::setMousePos(buttons[x].getCenter());
				break;
			case ELEMENT_DROPDOWNLIST: 
				Engine::setMousePos(ddlist[x].getCenter());
								//selected.first=ELEMENT_DROPDOWNLIST;
								//ddlist[selected.second].update(true);
				break;
			case ELEMENT_TEXTFIELD:
				Engine::setMousePos(txtfield[x].getCenter());		
				break;
			case ELEMENT_LABEL:
				break;
			default:
				break;
		}
	}
	
}

int GUIPanel::addSlider(Pos2D pos,GLfloat width,GLfloat minValue,GLfloat maxValue,GLuint number_Of_Steps)
{
	GUISlider xSlider;
	xSlider.create(pos,width,minValue,maxValue,number_Of_Steps,Pos2D(position.x,position.y),Color4f(1.f,1.f,1.f,1.f));
	slider.push_back(xSlider);

	element x;
	x.first=ELEMENT_SLIDER;
	x.second=slider.size()-1;
	elementOrder.push_back(x);

	return elementOrder.size()-1;
}
/*

void GUIPanel::addLabel(float x, float y, float w,float h,std::string t)
{
	GUILabel labe;
	labe.create(x,y,position.x,position.y,w,h,t);

	labels.push_back(labe);
}

*/