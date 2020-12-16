#include "InputMapper.h"
#include <iostream>

/*
void KeyHandler::loadKeys()
{
		
		Just testing some stuff below this
	

	Actions
    States
    Ranges

	

	tinyxml2::XMLDocument doc;
	doc.LoadFile("inp.xml");

	const char* title = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->GetText();
    printf( "Name of play (1): %s\n", title );
	
	/*
	tinyxml2::XMLText* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->FirstChild()->ToText();
	title = textNode->Value();
    printf( "Name of play (2): %s\n", title );
	*/
/*
	tinyxml2::XMLElement* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "BINDINGS" )->FirstChildElement("GUI")->FirstChildElement("confirm")->ToElement();

	title = textNode->Attribute("key");
    printf( "Name of play (2): %s\n", title );

	std::vector<std::string> obj;


	//boost::split(obj,title,'||');
	boost::split(obj,"Hello, You",boost::is_any_of(","));

	printf( "Name of play (3): %s \n", obj[0].c_str(),obj[1].c_str() );

	
	std::map<int,int> assigned;

	//GLFW_KEY, true or false;
	std::map<int,bool> actions;

	std::map<int, bool> states;

	std::map<int, float> ranges;

	/*
	if(obj[0]=="KEY_ENTER")
	{

	}
	

	//GLFW_KEY_ENTER

	// End of testing
}
*/


GLint KeyHandler::joyStickPresent=-1;
JoystickData KeyHandler::controller;

GUIHandler::GUIHandler()
{

}
GUIHandler::~GUIHandler()
{

}

bool GUIHandler::saveKeys(tinyxml2::XMLDocument *doc,tinyxml2::XMLElement *bindings)
{
	printf("Test im Keyhandler Nummero Uno\n");

	tinyxml2::XMLElement* gui=doc->NewElement("GUI");
	
	// Everything automatic
	
	//---------------------------------------------------------------------Mouse---------------------------------------------------------------------
		tinyxml2::XMLElement* mouse = doc->NewElement("MOUSE");		

		//Actions
		tinyxml2::XMLElement* m_actions = doc->NewElement("ACTIONS");

		for(int i=action_b.size()-1; i>=0 ;i--)
		{
			m_actions->InsertEndChild(createKeyElement(doc,"A",action_b[i].first)); // Might change string to array with names
		}
		mouse->InsertEndChild(m_actions);

		//States
		tinyxml2::XMLElement* m_states = doc->NewElement("STATES");

		for(int i=state_b.size()-1; i>=0 ;i--)
		{
			m_states->InsertEndChild(createKeyElement(doc,"S",state_b[i].first));
		}
		mouse->InsertEndChild(m_states);


		gui->InsertEndChild(mouse);

	//----------------------------------------------------------------------Keys----------------------------------------------------------------------
		tinyxml2::XMLElement* keys = doc->NewElement("KEYS");

		//Actions
		tinyxml2::XMLElement* actions = doc->NewElement("ACTIONS");
		for(int i=action_keys.size()-1; i>=0 ;i--)
		{
			actions->InsertEndChild(createKeyElement(doc,"A",action_keys[i].first)); // Might change string to array with names
		}
		keys->InsertEndChild(actions);

		//States
		tinyxml2::XMLElement* states = doc->NewElement("STATES");
		for(int i=state_keys.size()-1; i>=0 ;i--)
		{
			states->InsertEndChild(createKeyElement(doc,"S",state_keys[i].first)); // Might change string to array with names
		}
		keys->InsertEndChild(states);

		gui->InsertEndChild(keys);



	bindings->InsertEndChild(gui);

	return true;
}

bool GUIHandler::loadKeys()
{
	/*
	Actions
    States
    Ranges
*/
	/*
		Keys:
			confirm
			next
			last
	*/

	

	// Load File, Error if not aviable and load default
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile("input.xml")!=tinyxml2::XML_NO_ERROR)
	{
		printf("Could not load input.xml - Loading Default File\n");
		//loadDefaultKeys();
		return true;
	}

	//saveKeys();

	const char* key=NULL;

	tinyxml2::XMLElement* elementNode = doc.FirstChildElement( "BINDINGS" )->FirstChildElement("GUI");
	
	int keyNumber=0;
	keyPair x;
	x.second=false;



	//Load Actions Mouse
	for(tinyxml2::XMLElement* child = elementNode->FirstChildElement("MOUSE")->FirstChildElement("ACTIONS")->FirstChildElement(); child != NULL || keyNumber < B_A_LAST; child=child->NextSiblingElement())
	{
		int u=child->IntAttribute("key");

		x.first=u;
			
		action_b[keyNumber]=x;
		
		keyNumber++;
	}
//--------------------------------------------------------------------------------------Keys--------------------------------------------------------------------------------------

	//Load Actions Key
	keyNumber=0;
	for(tinyxml2::XMLElement* child = elementNode->FirstChildElement("KEYS")->FirstChildElement("ACTIONS")->NextSiblingElement(); child != NULL || keyNumber < KEY_A_LAST; child=child->NextSiblingElement())
	{
		int u=child->IntAttribute("key");

			x.first=u;

			action_keys[keyNumber]=x;

		keyNumber++;
	}

	

	//Load States
	keyNumber=0;

	for(tinyxml2::XMLElement* child = elementNode->FirstChildElement("KEYS")->FirstChildElement("STATES")->NextSiblingElement(); child != NULL || keyNumber > KEY_S_LAST; child=child->NextSiblingElement())
	{
		int u=child->IntAttribute("key");

		

			x.first=u;
			state_keys[keyNumber]=x;

		keyNumber++;
	}
	//Load Ranges
	/*for(tinyxml2::XMLElement* child = elementNode->FirstChildElement("KEYS")->FirstChildElement("RANGES"); child != NULL || keyNumber > KEY_A_LAST; child=child->NextSiblingElement())
	{
		int u=child->IntAttribute("key");

			x.first=u;
			range_keys[keyNumber]=x; // MIGHT NEED FIXING BEFORE USE

		keyNumber++;
	}*/

	return true;
}

bool GUIHandler::loadDefaultKeys()
{
	// CLEAR EVERYTHING!!!
	action_keys.clear();
	state_keys.clear();
	action_b.clear();
	state_b.clear();

// Actions	
	// Keys
	action_keys.push_back(keyPair(GLFW_KEY_ENTER,false));//[KEY_CONFIRM].first=GLFW_KEY_ENTER;
	
	action_keys.push_back(keyPair(GLFW_KEY_DOWN,false));
	action_keys.push_back(keyPair(GLFW_KEY_UP,false));

	action_keys.push_back(keyPair(GLFW_KEY_LEFT,false));
	action_keys.push_back(keyPair(GLFW_KEY_RIGHT,false));

		/*
		KEY_CONFIRM,
		KEY_NEXT_ELEMENT,
		KEY_PREVIOUS_ELEMENT,
		KEY_LEFT,
		KEY_RIGHT,
		*/

	// Buttons
	action_b.push_back(keyPair(GLFW_MOUSE_BUTTON_LEFT,false));
	
// States
	// Keys
	state_keys.push_back(keyPair(GLFW_KEY_LEFT_SHIFT,false));
	state_keys.push_back(keyPair(GLFW_KEY_RIGHT_SHIFT,false));
	state_keys.push_back(keyPair(GLFW_KEY_BACKSPACE,false));

	// Buttons
	state_b.push_back(keyPair(GLFW_MOUSE_BUTTON_LEFT,false));

	return true;
}

bool KeyHandler::isPressed(int key)
{
	// Other Keys
	if(key < action_keys.size())
	{
		if(action_keys[key].second)
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool KeyHandler::isPressedB(int button)
{
	if(button < action_b.size())
	{
		if(action_b[button].second)
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool KeyHandler::isPressedS(int key)
{
	
	if(key < state_keys.size())
	{
		if(state_keys[key].second)
		{
			
			return true;
		}
		else
			return false;
	}
	return false;
}
bool KeyHandler::isPressedBS(int button)
{
	if(button < state_b.size())
	{
		if(state_b[button].second)
		{	
			return true;
		}
		else
			return false;
	}
	return false;
}



/*
bool GUIHandler::isPressed(int x)
{
	if(action_keys[x].second || states_keys[x].second)
	{
		return true;
	}
}
*/

tinyxml2::XMLElement* createKeyElement(tinyxml2::XMLDocument *doc, std::string name,int key_Value)
{
	tinyxml2::XMLElement* x=doc->NewElement(name.c_str());
	x->SetAttribute("key",key_Value);
	return x;
}

void KeyHandler::eatActionKeys()
{
	lastPressedKey=0;

	for(int i=action_keys.size()-1;i>=0;i--)
	{
		action_keys[i].second=false;
	}

	for(int i=action_b.size()-1;i>=0;i--)
	{
		action_b[i].second=false;
	}

	for(int i=action_c.size()-1;i>=0;i--)
	{
		action_c[i].second=false;
	}
}

void KeyHandler::updateKeys(int key,int action)
{
	if(action==GLFW_RELEASE)
	{
		
		for(int i = state_keys.size()-1;i>=0;i--)
		{
			if(state_keys[i].first==key)
			{
				state_keys[i].second=false;
				return;
			}
		}
	}
	else if(action==GLFW_PRESS)
	{
		lastPressedKey=key;
		for(int i = action_keys.size()-1;i>=0;i--)
		{
			if(action_keys[i].first==key)
			{
				action_keys[i].second=true;
			}
		}

		for(int i = state_keys.size()-1;i>=0;i--)
		{
			if(state_keys[i].first==key)
			{
				state_keys[i].second=true;
				return;
			}
		}
	}
	/*
		if these loops take too long, use map instead of array and use GLFW_KEY Value as key
	*/
}

void KeyHandler::updateMouse(int button, int action)
{
	if(action==GLFW_RELEASE)
	{
		for(int i = state_b.size()-1;i>=0;i--)
		{
			if(state_b[i].first==button)
			{
				state_b[i].second=false;
				return;
			}
		}
	}
	else if(action==GLFW_PRESS)
	{
		for(int i = action_b.size()-1;i>=0;i--)
		{
			if(action_b[i].first==button)
			{
				action_b[i].second=true;
			}
		}

		for(int i = state_b.size()-1;i>=0;i--)
		{
			if(state_b[i].first==button)
			{
				state_b[i].second=true;
				return;
			}
		}
	}
}

int KeyHandler::getLastPressedKey()
{
	int x=lastPressedKey;
	lastPressedKey=0;

	return x;
}

void KeyHandler::checkForController()
{
	for(int i=GLFW_JOYSTICK_1;i<=GLFW_JOYSTICK_16;i++)
	{
		if(glfwJoystickPresent(i))
		{
			joyStickPresent=i;
			std::cout << "Joystick/Controller "<< i << GL_FALSE <<" present: " <<glfwGetJoystickName(joyStickPresent) << std::endl;


			controller.buttons = glfwGetJoystickButtons(joyStickPresent,&controller.numberOfButtons);
			controller.axesPos = glfwGetJoystickAxes(joyStickPresent,&controller.numberOfAxes);
			controller.previous_actions = new unsigned char[controller.numberOfButtons];
			std::fill(controller.previous_actions,controller.previous_actions + controller.numberOfButtons,0);
		}
	}
}
void KeyHandler::updateController()
{
	if(joyStickPresent!=-1 && glfwJoystickPresent(joyStickPresent))
	{
		controller.axesPos = glfwGetJoystickAxes(joyStickPresent,&controller.numberOfAxes);
		controller.buttons = glfwGetJoystickButtons(joyStickPresent,&controller.numberOfButtons);

		for(int i=controller.numberOfButtons-1;i>=0;i--)
		{
			//printf("Key %i: %i\n",i,(const unsigned int)controller.buttons[i]);
			// Actions
			//printf("changed! %i || %i \n",(const unsigned int)controller.previous_actions[i],(const unsigned int)controller.buttons[i]);
			if(controller.previous_actions[i]==false && controller.buttons[i]==true)
			{
				for(int u=0; u < action_c.size(); u++)
				{
					if(action_c[u].first == i)
					{
						action_c[u].second=true;
						controller.previous_actions[i]=true;
					}
				}
			}
			else if(controller.previous_actions[i]==true && controller.buttons[i]==false)
			{
				for(int u=0; u < action_c.size(); u++)
				{
					if(action_c[u].first == i)
					{
						controller.previous_actions[i]=false;
					}
				}
			}
			
		}

	}
}

void KeyHandler::printControllerDataDebug()
{
		
		if( controller.numberOfAxes > 0 )
			controller.axesPos = glfwGetJoystickAxes(joyStickPresent,&controller.numberOfAxes);
			for(int i=controller.numberOfAxes-1;i>=0;i--)
			{
				std::cout << "Axes "<< i <<" : "  << controller.axesPos[i] << std::endl;
			}
	
		if( controller.numberOfButtons > 0 )
			controller.buttons = glfwGetJoystickButtons(joyStickPresent,&controller.numberOfButtons);
			for(int i=controller.numberOfButtons-1;i>=0;i--)
			{
				std::cout << "Button "<< i <<" : "  << controller.buttons[i] << std::endl;
			}
}

GLfloat KeyHandler::getRange(int axis)
{
	if(joyStickPresent!=-1)
		if(ranges.size() >= axis)
		{
			return controller.axesPos[axis];//  ranges[axis].second;
		}
}

bool KeyHandler::isPressedC(int c)
{
	if(joyStickPresent!=-1)
	{
		if(action_c.size() >= c)
		{
			return action_c[c].second;//  ranges[axis].second;
		}
	}

	return false;
}
bool KeyHandler::isPressedCS(int c)
{
	if(joyStickPresent!=-1)
	{
		if(action_c.size() >= c)
		{
			return controller.buttons[c];//  ranges[axis].second;
		}
	}

	return false;
}