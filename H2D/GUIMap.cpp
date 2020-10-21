#include "GUIMap.h"


GUIMap::GUIMap(void)
{
	isLoaded=false;
	m_currentActiveMapItem=0;
}


GUIMap::~GUIMap(void)
{
	isLoaded=false;
	m_currentActiveMapItem=0;
}

void GUIMap::init(GLuint currentActiveMapItem)
{
	if(!isLoaded)
	{
		m_currentActiveMapItem=currentActiveMapItem;

		m_position=b2Vec2(960.f,540.f);

		mapSpriteSheet.loadTextureFromFile32("dbug.png");
		mapSpriteSheet.addClipSprite(Rect(0.f,0.f,100.f,100.f));
		mapSpriteSheet.addClipSprite(Rect(0.f,100.f,100.f,100.f));
		mapSpriteSheet.addClipSprite(Rect(100.f,100.f,100.f,100.f));
		mapSpriteSheet.addClipSprite(Rect(100.f,100.f,100.f,100.f));
		GUIMapItem::setSpriteSheet2D(&mapSpriteSheet);
		/*
			Load map objects

			position, conntected sectors
		*/
		GLuint mapItemID=-1;
		mapElements.push_back(GUIMapItem());
		mapElements[mapElements.size()-1].init(++mapItemID,b2Vec2(-360.f,150.f),m_position,"Sector 7G","Sector 7G is a pretty small sector with only a one inhabited planet.");//b2Vec2(-360.f,150.f),m_position,&mapSpriteSheet,0,1,true);
		mapElements.push_back(GUIMapItem());
		mapElements[mapElements.size()-1].init(++mapItemID,b2Vec2(-255.f,-123.f),m_position,"Sector 8H","Sector 8H, pretty empty if you'd ask me, but you won't ask me, because I'm just static text.");//create(b2Vec2(-255.f,-123.f),m_position,&mapSpriteSheet,0,2,true);
		mapElements.push_back(GUIMapItem());
		mapElements[mapElements.size()-1].init(++mapItemID,b2Vec2(250.f,-140.f),m_position,"Sector 1A","No information avaible...");//create(b2Vec2(250.f,-140.f),m_position,&mapSpriteSheet,0,3,true);
		mapElements.push_back(GUIMapItem());
		mapElements[mapElements.size()-1].init(++mapItemID,b2Vec2(250.f,250.f),m_position,"Sector Z22","Little information is avaible about this sector. It looks like a huge area for mining. Many Dwarfes live here.");//create(b2Vec2(250.f,-140.f),m_position,&mapSpriteSheet,0,3,true);
		
		//loop to come

		mapElements[0].addConnectedItem(mapElements[1].getMapItemData());

		mapElements[1].addConnectedItem(mapElements[2].getMapItemData());

		mapElements[2].addConnectedItem(mapElements[0].getMapItemData());

		mapElements[3].addConnectedItem(mapElements[1].getMapItemData());

		GLuint size = mapElements.size();

		for(int i=0;i<size;i++)
		{
			for(int u=0;u<size;u++)
			{
				if(mapElements[i].isConnected(u))
				{
					mapElements[u].addConnectedItem(mapElements[i].getMapItemData());
				}
			}
		}

		/*
			Other stuff
		*/
		background.loadTextureFromFile32("map.png");
		button_back.create("Back",-2,Color4f(0.f,0.f,0.f,1.f),Color4f(0.f,0.f,0.f,1.f),b2Vec2(300.f,-300.f),m_position.x,m_position.y);

		isLoaded=true;
	}
}

GLint GUIMap::update()
{
	if(button_back.update()!=-1) return -2;

	//if( GameState::handler->isPressed(GUIHandler::KEY_M)	// Add ESCAPE as quit key to the GUI Hanlder

	GLint rv=0;

	mapElements[m_currentActiveMapItem].setCurrentActiveMapElement();

	for(int i=mapElements.size()-1;i>=0;i--)
	{
		if(m_currentActiveMapItem!=i)
		{
			rv = mapElements[i].update();
			if(rv != -1)	
			{	


				if( !mapElements[m_currentActiveMapItem].isConnected(mapElements[i].getMapItemID()) )		 return -1;
			
				if(GameState::handler->isPressed(GUIHandler::KEY_CONFIRM) || GameState::handler->isPressedB(GUIHandler::B_CONFIRM)) 
				{
					m_currentActiveMapItem=i;
					return rv;
				}
			}
		}
	}
	return -1;
}

void GUIMap::render()
{
	background.render(960.f,540.f);

	//mapElements[m_currentActiveMapItem].renderLines();

	for(int i=mapElements.size()-1;i>=0;i--)
	{
		mapElements[i].renderLines();
	}

	for(int i=mapElements.size()-1;i>=0;i--)
	{
		mapElements[i].render();
	}
	
	button_back.render();
}