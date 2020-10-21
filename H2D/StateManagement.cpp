#include "Game.h"

#include "StateManagement.h"

#include "StateMenu.h"
#include "Level.h"
#include "Editor.h"

void changeState()
{
	if (nextState != -1)
	{
		// destroy currenstate with virtual destructor?

		switch (nextState)
		{
		case STATE_MENU:
			currentState = std::make_shared<StateMenu>();//StateMenu();
			break;
		case STATE_LEVEL1:
			currentState = std::make_shared<Level>(); // new Level(nextStateInfo);
			break;
		case STATE_EDITOR:
			currentState.reset(new Editor());// = std::make_shared<Editor>();
			break;
		case STATE_EXIT:
			//quitProgram();
		default:
			//currentState = new Intro();
			break;
		}

	}
	nextState = -1;
}

