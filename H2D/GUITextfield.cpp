#include "GUITextfield.h"


GUITextfield::GUITextfield(void)
{
}


GUITextfield::~GUITextfield(void)
{
}

void GUITextfield::create(b2Vec2 pos, GLfloat parentX, GLfloat parentY, Color4f col)
{
	m_position = pos;// RectSize(TEXTFIELD_WIDTH, 32.f));
	m_size.Set(TEXTFIELD_WIDTH, 32.f);
	m_upperLeft.Set(m_position.x - m_size.x / 2, m_position.y + m_size.y / 2);
	parX=parentX;
	parY=parentY;

	textColor=col;
	sheetID=0;

	text.initFitToRect("Test", Rect(m_position.x, m_position.y, m_size.x, m_size.y), 4.f);
	text.setTextColor(col);

	lastActionTick=0.f;

}
bool GUITextfield::isHovered()
{
	return Engine::mouseHover(m_upperLeft, m_size, parX, parY);
}
bool GUITextfield::update()
{
	if(isHovered())
	{
			// Background setzten 2
			int key = GameState::handler->getLastPressedKey();
		
			if((key >= GLFW_KEY_A && key <= GLFW_KEY_Z))
			{
			
				std::string *t=text.getText();
				if(t->length() < MAX_CHARS)
				{
					if(!(GameState::handler->isPressedS(GUIHandler::KEY_S_SHIFT_LEFT) || GameState::handler->isPressedS(GUIHandler::KEY_S_SHIFT_RIGHT)))
					{
						key+=32;
					}
				
					text.updateText((*t+=key));
				}

				lastActionTick=(float)glfwGetTime();
			}

			else if(GameState::handler->isPressedS(GUIHandler::KEY_S_BACKSPACE))
			{
				std::string *t=text.getText();
				if(t->length() > 0)
				{
					t->pop_back();
					text.updateText(*t);
				}
				lastActionTick=(float)glfwGetTime();
			}
			else
			{
				std::string *t=text.getText();
				if(t->length() < MAX_CHARS)
				{	
					switch(key)
					{
					case GLFW_KEY_SPACE: text.updateText((*t+=' '));
						break;
					case GLFW_KEY_GRAVE_ACCENT: text.updateText((*t+='^'));
						break;
					case GLFW_KEY_COMMA: text.updateText((*t+=','));
						break;
					case GLFW_KEY_PERIOD: text.updateText((*t+='.'));
						break;
					case GLFW_KEY_APOSTROPHE: text.updateText((*t+="'"));
						break;
					case GLFW_KEY_MINUS: text.updateText((*t+='-'));
						break;
					default:
						break;
					}

					if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
					{
						text.updateText(*t+=key);
					}
				}

				lastActionTick=(float)glfwGetTime();
			}
	}
	return true;
}

Pos2D GUITextfield::getCenter()
{
	return Pos2D(floor(parX + (m_position.x + (m_size.x / 2))) + 0.5f, floor(parY + (m_position.y + (m_size.y / 2)) + 0.5f));
}

std::string GUITextfield::getValue()
{
	return *text.getText();
}

void GUITextfield::render()
{
	if(isHovered())
	{
		guiSheet[sheetID].renderSprite(GUI_TEX_TEXTFIELD_HOVERED, m_position.x + parX, m_position.y + parY);
	}
	else
	{
		guiSheet[sheetID].renderSprite(GUI_TEX_TEXTFIELD, m_position.x + parX, m_position.y + parY);
	}
	text.render(m_upperLeft.x + parX + 5.f, m_upperLeft.y + parY - m_size.y/2.f);
}