#pragma once

#ifndef GAMESTATEH_H
#define GAMESTATEH_H

#include "OpenGLH.h"
#include "Font2D.h"
#include "Engine.h"
#include "Element2D.h"
#include "tinyxml2.h"


#include <boost\smart_ptr.hpp>

#include "InputMapper.h"

enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_MENU,
	STATE_EXIT,
	STATE_LEVEL1,
	STATE_EDITOR,
};

enum HandlerType
{
	HANDLER_GUI,
	HANDLER_GAME,
	HANDLER_EDITOR,
	HANDLER_LAST
};




class GameState
{
public:
	GameState(void);
	virtual ~GameState(void);

	virtual void update()=0;
	virtual void renderBackground()=0;
	virtual void render()=0;
	virtual void updateRender()=0;
	virtual void renderFinal()=0;



	static void setFont2D(Font2D* f);

	static void setInterpolation(float interpol);
	static GLfloat getInterpolation();
	// Key Handling
	static bool isCurrentHandler(int handlerType);
	static void saveKeys();
	static void loadKeys();
	static void loadDefaultKeys();

	static void eatKeyActions();
	static void keyHandleFunc(int key,int action);
	static void mouseHandleFunc(int button, int action);
	static bool setHandler(int handlerType);

	static void init();
	static boost::shared_ptr<KeyHandler> handler;

protected:
	static Font2D* text;
	static float interpolation;


	static std::vector<boost::shared_ptr<KeyHandler>> handlerList;
	//static KeyHandler *handler;
	static int currentHandler;

};

void setNextState(int state,int stateInfo);

#endif