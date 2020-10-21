
#pragma once

#include "OpenGLH.h"
#include "tinyxml2.h"

#include <set>
#include <map>
#include <list>
#include <vector>
#include <utility>
#include <array>
#include <boost\algorithm\string.hpp>
/*
	Keys
*/
struct JoystickData
{
	int numberOfAxes;
	int numberOfButtons;

	const float* axesPos;
	
	unsigned char* previous_actions;
	const unsigned char* buttons;
};

//functions

class KeyHandler
{
public:
	virtual bool loadKeys()=0;
	virtual bool loadDefaultKeys()=0;
	virtual bool saveKeys(tinyxml2::XMLDocument *doc,tinyxml2::XMLElement *bindings)=0;
	/*	CONTROLLER

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


	// Actions
	bool isPressed(int key);
	bool isPressedB(int button);
	bool isPressedC(int c);

	// States
	bool isPressedS(int key);
	bool isPressedBS(int button);
	bool isPressedCS(int c);

	// Ranges

	void eatActionKeys();

	void updateKeys(int key,int action);
	void updateMouse(int button, int action);
	
	int getLastPressedKey();


	// Controller
	GLfloat getRange(int axis);


	static void checkForController();
	static void printControllerDataDebug();
	void updateController();

protected:
	
	typedef std::pair<int,bool> keyPair;
	typedef std::pair<int,GLfloat> rangesPair;

	std::vector<keyPair> action_keys;
	std::vector<keyPair> state_keys;
	

	std::vector<keyPair> action_b;
	std::vector<keyPair> state_b;

	std::vector<keyPair> action_c;	// <button to push , state> at(buttonPushed)
	// States in controller struct
	std::vector<rangesPair> ranges;

	int lastPressedKey;

	static GLint joyStickPresent;
	static JoystickData controller;
};

class GUIHandler : public KeyHandler
{
public:

	GUIHandler();
	~GUIHandler();

	enum GUIActions
	{
		KEY_CONFIRM,
		KEY_NEXT_ELEMENT,
		KEY_PREVIOUS_ELEMENT,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_A_LAST
	};

	/*
		ENUM AND XML HAS TO BE IN THE SAME ORDER
	*/

	enum GUIStates
	{
		KEY_S_SHIFT_LEFT,
		KEY_S_SHIFT_RIGHT,
		KEY_S_BACKSPACE,
		KEY_S_LAST
	};

	enum GUIRanges
	{
		KEY_R_LAST,
	};

	enum GUIButtonActions
	{
		B_CONFIRM,
		B_A_LAST
	};

	enum GUIButtonStates
	{
		B_S_CONFIRM,
		B_S_LAST
	};

	void clearActions();
	void clearStates();
	void clearRanges();



	bool saveKeys(tinyxml2::XMLDocument *doc,tinyxml2::XMLElement *bindings);
	bool loadKeys();
	bool loadDefaultKeys();
	void eatActionKeys();



	//void saveKeys();
	//void loadDefaultKeys();
	//void setKeyHandler();
};



class GameHandler : public KeyHandler
{
public:
	GameHandler();
	~GameHandler();

	enum GameActions
	{
		KEY_MENU,
		KEY_USE,
		KEY_ITEM_1,
		KEY_ITEM_2,
		KEY_ITEM_3,
		KEY_ITEM_4,
		KEY_ITEM_5,
		KEY_ITEM_6,
		KEY_ITEM_7,
		KEY_ITEM_8,
		KEY_ITEM_9,
		KEY_ITEM_0,
		KEY_A_LAST
	};

	enum ControllerActions
	{
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
		CONTROLLER_LEFT,
		CONTROLLER_LAST
	};
	/*
		ENUM AND XML HAS TO BE IN THE SAME ORDER
	*/

	enum States
	{
		KEY_S_LEFT,
		KEY_S_RIGHT,
		KEY_S_UP,
		KEY_S_DOWN,
		KEY_RUN,
		KEY_HIDE,
		KEY_S_LAST
	};

	enum GameRanges
	{
		AXIS_1_X,
		AXIS_1_Y,
		AXIS_TRIGGER,
		AXIS_2_Y,
		AXIS_2_X,
		RANGE_LAST,
	};

	enum GameControllerStates
	{
		CONTROLLER_S_A,
		CONTROLLER_S_B,
		CONTROLLER_S_X,
		CONTROLLER_S_Y,
		CONTROLLER_S_LB,
		CONTROLLER_S_RB,
		CONTROLLER_S_SELECT,
		CONTROLLER_S_START,
		CONTROLLER_S_LEFT_STICK,
		CONTROLLER_S_RIGHT_STICK,
		CONTROLLER_S_UP,
		CONTROLLER_S_RIGHT,
		CONTROLLER_S_DOWN,
		CONTROLLER_S_LEFT,
		CONTROLLER_S_LAST
	};

	enum GameButtonActions
	{
		B_FIRE_PRIMARY,
		B_FIRE_SECONDARY,
		B_A_LAST
	};

	enum GameButtonStates
	{
		B_S_FIRE_PRIMARY,
		B_S_FIRE_SECONDARY,
		B_S_LAST
	};

	/*void clearActions();
	void clearStates();
	void clearRanges();*/

	bool saveKeys(tinyxml2::XMLDocument *doc,tinyxml2::XMLElement *bindings);
	bool loadKeys();
	bool loadDefaultKeys();
	//void eatActionKeys();
};


class EditorHandler : public KeyHandler
{
public:
	EditorHandler();
	~EditorHandler();

	enum GameActions
	{
		KEY_FLOOR_UP,
		KEY_FLOOR_DOWN,
		KEY_A_LAST
	};

	enum ControllerActions
	{
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
		CONTROLLER_LEFT,
		CONTROLLER_LAST
	};
	/*
	ENUM AND XML HAS TO BE IN THE SAME ORDER
	*/

	enum States
	{
		KEY_S_LEFT,
		KEY_S_RIGHT,
		KEY_S_UP,
		KEY_S_DOWN,
		KEY_S_SPEEDUP,
		KEY_S_LAST
	};

	enum GameRanges
	{
		AXIS_1_X,
		AXIS_1_Y,
		AXIS_TRIGGER,
		AXIS_2_Y,
		AXIS_2_X,
		RANGE_LAST,
	};

	enum GameControllerStates
	{
		CONTROLLER_S_A,
		CONTROLLER_S_B,
		CONTROLLER_S_X,
		CONTROLLER_S_Y,
		CONTROLLER_S_LB,
		CONTROLLER_S_RB,
		CONTROLLER_S_SELECT,
		CONTROLLER_S_START,
		CONTROLLER_S_LEFT_STICK,
		CONTROLLER_S_RIGHT_STICK,
		CONTROLLER_S_UP,
		CONTROLLER_S_RIGHT,
		CONTROLLER_S_DOWN,
		CONTROLLER_S_LEFT,
		CONTROLLER_S_LAST
	};

	enum GameButtonActions
	{
		B_FIRE_PRIMARY,
		B_FIRE_SECONDARY,
		B_A_LAST
	};

	enum GameButtonStates
	{
		B_S_FIRE_PRIMARY,
		B_S_FIRE_SECONDARY,
		B_S_LAST
	};

	/*void clearActions();
	void clearStates();
	void clearRanges();*/

	bool saveKeys(tinyxml2::XMLDocument *doc, tinyxml2::XMLElement *bindings);
	bool loadKeys();
	bool loadDefaultKeys();
	//void eatActionKeys();
};



extern tinyxml2::XMLElement* createKeyElement(tinyxml2::XMLDocument *doc, std::string name,int key_Value);

class Handler
{
public:
	enum HandlerEnum
	{
		HANDLER_GUI,
		HANDLER_GAME,

		HANDLER_LAST
	};

	Handler();
	~Handler();

	void setHandler(int x);

	// Keyhandler Objects
	GUIHandler gui;
	//GameHandler game;

	int currentHandlerID;
};