#include "GameState.h"

Font2D* GameState::text=NULL;
float GameState::interpolation=1.f;

boost::shared_ptr<KeyHandler> GameState::handler = NULL;
std::vector<boost::shared_ptr<KeyHandler>> GameState::handlerList;

int GameState::currentHandler;

GameState::GameState(void)
{

}

GameState::~GameState(void)
{

}

void GameState::init()
{
	boost::shared_ptr<GUIHandler> a(new GUIHandler);
	handlerList.push_back(a);
	boost::shared_ptr<GameHandler> b(new GameHandler);
	handlerList.push_back(b);
	boost::shared_ptr<EditorHandler> c(new EditorHandler);
	handlerList.push_back(c);
}
void GameState::setFont2D(Font2D* f)
{
	text = f;
}

void GameState::setInterpolation(float interpol)
{
	interpolation=interpol;
}
GLfloat GameState::getInterpolation()
{
	return interpolation;
}


bool GameState::isCurrentHandler(int handlerType)
{
	return (handlerType==currentHandler);
}

void GameState::saveKeys()
{
	tinyxml2::XMLDocument doc;
		
	tinyxml2::XMLElement* bindings=doc.NewElement("BINDINGS");
	
	

	for(int i = handlerList.size()-1; i >= 0; i--)
	{
		handlerList[i]->saveKeys(&doc,bindings);
	}
	
	doc.InsertEndChild(bindings);
	doc.SaveFile("input.xml");
}

void GameState::loadKeys()
{
	for(int i = handlerList.size()-1; i >= 0; i--)
	{
		handlerList[i]->loadKeys();
	}
}

void GameState::loadDefaultKeys()
{
	for(int i = handlerList.size()-1; i >= 0; i--)
	{
		handlerList[i]->loadDefaultKeys();
	}
}

void GameState::eatKeyActions()
{
	handlerList[currentHandler]->eatActionKeys();
}

void GameState::keyHandleFunc(int key,int action)
{
	handler->updateKeys(key,action);
}

void GameState::mouseHandleFunc(int button, int action)
{
	handler->updateMouse(button,action);
}

bool GameState::setHandler(int handlerType)
{
	if(handlerType < HANDLER_LAST && handlerType >= 0)
	{
		currentHandler=handlerType;

		handler=handlerList[currentHandler];

		return true;
	}
	else
		printf("Handler unaviable: %i",handlerType); return false;
}