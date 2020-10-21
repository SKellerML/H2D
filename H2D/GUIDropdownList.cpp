#include "GUIDropdownList.h"


GUIDropdownList::GUIDropdownList(void)
{
	keySelected=0;
	unfolded=false;
}


GUIDropdownList::~GUIDropdownList(void)
{
}


void GUIDropdownList::create(Pos2D pos,std::string text,GLshort returnValue,GLfloat parentX,GLfloat parentY)
{
	pX=parentX;
	pY=parentY;
	size=Rect(pos,RectSize(96.f,32.f));


	Color4f background(1.f,1.f,1.f,1.f);

	
	//main.createDropdownButton(0.f,0.f,size.x,size.y,text,returnValue);

	txtCol=Color4f(0.f,0.f,0.f,1.f);
	txtColHover=Color4f(0.f,0.f,0.f,1.f);

	addObject(text,-7);
	addObject(text,returnValue);

	selectedValue=returnValue;
	cursorVisible=false;

	unfolded=false;
}

void GUIDropdownList::addObject(std::string text,GLshort returnValue)
{
	GLshort amount=objects.size();

	GUIButtonTextured butt;
	butt.create(text,returnValue,txtCol,txtColHover,b2Vec2(size.x,size.y+(amount*size.h)),pX,pY);
	//butt.createPlainBackground(0.f,amount*size.h,size.x,size.y,size.w,size.h,text,returnValue,Color4f(0.f,0.f,0.f,1.f),Color4f(1.f,1.f,1.f,1.f),0.f);
	objects.push_back(butt);
}

GLshort GUIDropdownList::getSelectedValue()
{
	return selectedValue;
}
bool GUIDropdownList::isHovered()
{
	// Only works in folded situation
	return (Engine::mouseHover(Rect(size.x,size.y,size.w+size.h,size.h),pX,pY));
}

bool GUIDropdownList::update()
{
	if(unfolded)
	{
		int selected_now;
		for(int i=(objects.size()-1);i>=0;i--)
		{
			if((selected_now=objects[i].update())!=-1) // Wenn die Maus darüber hovered
			{
				objects[0].setText(objects[i].getText());
				selectedValue = objects[i].getRV();
				unfolded=false;

				//Engine::setMousePos(objects[0].getCenter()); // Currently cursor gets visible when set here

				return unfolded;
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
		
				if(objects.size()-1 > keySelected)
				{
					keySelected+=1;
				}
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
				lastActionKey=true;
			}

		
			if(lastActionKey)
			{
				Engine::setMousePos(objects[keySelected].getCenter());

				if(!cursorVisible)
				{
					glfwSetInputMode(Engine::getWindow(),GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
					cursorVisible=true;
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
	}
	else if(isHovered())
	{

			if(objects[0].update()!=-1)
			{
				unfolded=true;
			}

			
			if(!mainHovered)
			{
				mainHovered=true;
			}
	}
	else
	{
		if(mainHovered)
		{
			mainHovered=false;
			objects[0].setSelected(false);
		}


	}

	/*
	if(objects.size()>0)
	{
		// Key Behaviour
		if(unfolded)
		{
			// Check for Mousehover
			GLshort x;
			for(int i=(objects.size()-1);i>=1;i--)
			{
				if((x=objects[i].update())!=-1)
				{
					if(GameState::handler->isPressedB(GUIHandler::B_CONFIRM))
					{
						objects[0].setText(objects[i].getText());
						unfolded=false;
					}
				}
			}

			// Check for KeyMovement
			if(GameState::handler->isPressed(GUIHandler::KEY_NEXT_ELEMENT)) // 
			{
				if((objects.size()-1) > keySelected)
				{
					keySelected+=1;
				}
				
			}
			else if(GameState::handler->isPressed(GUIHandler::KEY_PREVIOUS_ELEMENT))
			{
				if(keySelected > 0)
				{
					keySelected-=1;
				}
			}

			for(int i=(objects.size()-1);i>=1;i--)
			{
				if(keySelected==i)
				{
					objects[i].setSelected(true);
				}
				else
				{
					objects[i].setSelected(false);
				}
			}

			if(GameState::handler->isPressed(GUIHandler::KEY_CONFIRM))
			{
				objects[0].setText(objects[keySelected].getText());
				unfolded=false;
			}
		}
	}

	if(isHovered())
	{
		mainHovered=true;
		if(!mainHovered)
		{
			objects[0].setSelected(false);
			mainHovered=true;
		}
		if(!unfolded && (GameState::handler->isPressedB(GUIHandler::B_CONFIRM) || GameState::handler->isPressed(GUIHandler::KEY_CONFIRM)))
		{
			unfolded=true;
		}
		else if(unfolded && (GameState::handler->isPressedB(GUIHandler::B_CONFIRM) || GameState::handler->isPressed(GUIHandler::KEY_CONFIRM)))
		{
			unfolded=false;
		}
		return unfolded;
	}
	else
	{
		if(mainHovered)
		{
			objects[0].setSelected(true);
			mainHovered=false;
		}
	}
	*/

	return unfolded;
}

Pos2D GUIDropdownList::getCenter()
{
	return Pos2D(floor(pX+(size.x+(size.w/2)))+0.3f,floor(pY+(size.y+(size.h/2))+0.3f));
}


void GUIDropdownList::render()
{
	
	if(unfolded)
	{
		for(int i=(objects.size()-1);i>=1;i--)
		{
			objects[i].render();
		}
	}
	objects[0].render();
	//objects[0].setSelected(false);
	//main.render();
	//GLfloat scaleFactor=size.h/32;
	//arrow.render(size.x+pX+size.w,size.y+pY,scaleFactor,scaleFactor);
	// Arrow
	guiSheet[0].renderSprite(GUI_TEX_ARROW,size.x+pX+size.w,size.y+pY);
}
