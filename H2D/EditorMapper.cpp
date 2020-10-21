#include "InputMapper.h"


EditorHandler::EditorHandler()
{
}


EditorHandler::~EditorHandler()
{
}

bool EditorHandler::saveKeys(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *bindings)
{
	printf("Saving Keys for Game\n");

	tinyxml2::XMLElement* gui = doc->NewElement("GAME");

	// Everything automatic

	//---------------------------------------------------------------------Mouse---------------------------------------------------------------------
	tinyxml2::XMLElement* mouse = doc->NewElement("MOUSE");

	//Actions
	tinyxml2::XMLElement* m_actions = doc->NewElement("ACTIONS");

	for (int i = action_b.size() - 1; i >= 0; i--)
	{
		m_actions->InsertEndChild(createKeyElement(doc, "A", action_b[i].first)); // Might change string to array with names
	}
	mouse->InsertEndChild(m_actions);

	//States
	tinyxml2::XMLElement* m_states = doc->NewElement("STATES");

	for (int i = state_b.size() - 1; i >= 0; i--)
	{
		m_states->InsertEndChild(createKeyElement(doc, "S", state_b[i].first));
	}
	mouse->InsertEndChild(m_states);


	gui->InsertEndChild(mouse);

	//----------------------------------------------------------------------Keys----------------------------------------------------------------------
	tinyxml2::XMLElement* keys = doc->NewElement("KEYS");

	//Actions
	tinyxml2::XMLElement* actions = doc->NewElement("ACTIONS");
	for (int i = action_keys.size() - 1; i >= 0; i--)
	{
		actions->InsertEndChild(createKeyElement(doc, "A", action_keys[i].first)); // Might change string to array with names
	}
	keys->InsertEndChild(actions);

	//States
	tinyxml2::XMLElement* states = doc->NewElement("STATES");
	for (int i = state_keys.size() - 1; i >= 0; i--)
	{
		states->InsertEndChild(createKeyElement(doc, "S", state_keys[i].first)); // Might change string to array with names
	}
	keys->InsertEndChild(states);

	gui->InsertEndChild(keys);



	bindings->InsertEndChild(gui);

	return true;
}

bool EditorHandler::loadKeys()
{
	/*
	Actions
	States
	Ranges
	*/

	// Load File, Error if not aviable and load default
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("input.xml") != tinyxml2::XML_NO_ERROR)
	{
		printf("Could not load input.xml - Loading Default File\n");
		//loadDefaultKeys();
		return true;
	}

	//saveKeys();

	const char* key = NULL;

	tinyxml2::XMLElement* elementNode = doc.FirstChildElement("BINDINGS")->FirstChildElement("GAME");

	int keyNumber = 0;
	keyPair x;
	x.second = false;



	//Load Actions Mouse
	for (tinyxml2::XMLElement* child = elementNode->FirstChildElement("MOUSE")->FirstChildElement("ACTIONS")->FirstChildElement(); child != NULL || keyNumber < B_A_LAST; child = child->NextSiblingElement())
	{
		int u = child->IntAttribute("key");

		x.first = u;

		action_b[keyNumber] = x;

		keyNumber++;
	}
	//--------------------------------------------------------------------------------------Keys--------------------------------------------------------------------------------------

	//Load Actions Key
	keyNumber = 0;
	for (tinyxml2::XMLElement* child = elementNode->FirstChildElement("KEYS")->FirstChildElement("ACTIONS")->NextSiblingElement(); child != NULL || keyNumber < KEY_A_LAST; child = child->NextSiblingElement())
	{
		int u = child->IntAttribute("key");

		x.first = u;

		action_keys[keyNumber] = x;

		keyNumber++;
	}



	//Load States
	keyNumber = 0;

	for (tinyxml2::XMLElement* child = elementNode->FirstChildElement("KEYS")->FirstChildElement("STATES")->NextSiblingElement(); child != NULL || keyNumber > KEY_S_LAST; child = child->NextSiblingElement())
	{
		int u = child->IntAttribute("key");



		x.first = u;
		state_keys[keyNumber] = x;

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

bool EditorHandler::loadDefaultKeys()
{
	// CLEAR EVERYTHING!!!
	action_keys.clear();
	state_keys.clear();
	action_b.clear();
	state_b.clear();
	ranges.clear();


	printf("\n Gamehandler activated \n");
	// Actions	
	// Keys
	action_keys.push_back(keyPair(GLFW_KEY_PAGE_UP, false));
	action_keys.push_back(keyPair(GLFW_KEY_PAGE_DOWN, false));

	// Buttons
	action_b.push_back(keyPair(GLFW_MOUSE_BUTTON_LEFT, false));
	action_b.push_back(keyPair(GLFW_MOUSE_BUTTON_RIGHT, false));
	// States
	// Keys
	state_keys.push_back(keyPair(GLFW_KEY_A, false));
	state_keys.push_back(keyPair(GLFW_KEY_D, false));
	state_keys.push_back(keyPair(GLFW_KEY_W, false));
	state_keys.push_back(keyPair(GLFW_KEY_S, false));
	state_keys.push_back(keyPair(GLFW_KEY_LEFT_SHIFT, false));

	// Buttons
	state_b.push_back(keyPair(GLFW_MOUSE_BUTTON_LEFT, false));
	state_b.push_back(keyPair(GLFW_MOUSE_BUTTON_RIGHT, false));

	ranges.push_back(rangesPair(0, 0.f));
	ranges.push_back(rangesPair(1, 0.f));
	ranges.push_back(rangesPair(2, 0.f));
	ranges.push_back(rangesPair(3, 0.f));

	//action_c.push_back(keyPair(CONTROLLER_A,false));
	action_c.push_back(keyPair(CONTROLLER_A, false));
	action_c.push_back(keyPair(CONTROLLER_B, false));
	action_c.push_back(keyPair(CONTROLLER_X, false));
	action_c.push_back(keyPair(CONTROLLER_Y, false));
	action_c.push_back(keyPair(CONTROLLER_LB, false));
	action_c.push_back(keyPair(CONTROLLER_RB, false));
	action_c.push_back(keyPair(CONTROLLER_SELECT, false));
	action_c.push_back(keyPair(CONTROLLER_START, false));
	action_c.push_back(keyPair(CONTROLLER_LEFT_STICK, false));
	action_c.push_back(keyPair(CONTROLLER_RIGHT_STICK, false));
	action_c.push_back(keyPair(CONTROLLER_UP, false));
	action_c.push_back(keyPair(CONTROLLER_RIGHT, false));
	action_c.push_back(keyPair(CONTROLLER_DOWN, false));
	action_c.push_back(keyPair(CONTROLLER_LEFT, false));


	return true;
}

/*
CONTROLLER_A,
CONTROLLER_B,
CONTROLLER_X,
CONTROLLER_Y,
CONTROLLER_LB,
CONTROLLER_RB,
CONTROLLER_SELECT,
CONTROLLER_START,
CONTROLLER_LEFT_STICK,
CONTROLLER_RIGHT_STICK,
CONTROLLER_UP,
CONTROLLER_RIGHT,
CONTROLLER_DOWN,
CONTROLLER_LEFT
*/