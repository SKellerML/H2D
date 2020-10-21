#include "GUIMapItem.h"

SpriteSheet2D* GUIMapItem::m_mapSheet;

GUIMapItem::GUIMapItem(void)
{
	isActiveMapElement=false;
}


GUIMapItem::~GUIMapItem(void)
{
}


void GUIMapItem::setSpriteSheet2D(SpriteSheet2D* sheet)
{
	m_mapSheet=sheet;
}

void GUIMapItem::init(GLuint mapItemID, b2Vec2 position, b2Vec2 parentPosition, std::string name, std::string description)
{
	m_position=position;
	m_name=name;
	m_description=description;
	m_parentPosition=parentPosition;
	m_mapItemID=mapItemID;

	mapElement.create(m_position,parentPosition,m_mapSheet,0,m_mapItemID,true);

	/*
	*/
}

void GUIMapItem::addConnectedItem(GLuint id,b2Vec2 position)
{
	connectedItemID.push_back(id);

	std::vector<b2Vec2> lineVertices;
	lineVertices.push_back(( m_position+m_parentPosition) );

	lineVertices.push_back( b2Vec2(position)+m_parentPosition );

	ElementLines currentLine;
	currentLine.initElement(&lineVertices,5.f,Color4f(1.f,1.f,1.f,1.f),0xAAAA,50.f);

	lines.push_back(currentLine);

	lineVertices.pop_back();
	/*
	BOOST_FOREACH( ConnectedItemsMap::value_type &i , m_connectedMapItems )
	{
		lineVertices.push_back( b2Vec2(i.second) );

		ElementLines currentLine;
		currentLine.initElement(&lineVertices,10.f,Color4f(1.f,1.f,1.f,1.f));

		lines.push_back(currentLine);

		lineVertices.pop_back();
		//printf("ID: %i ",i.second.getObjectID());
	}*/
}

void GUIMapItem::addConnectedItem(std::pair<GLuint,b2Vec2> pair)
{
	connectedItemID.push_back(pair.first);

	std::vector<b2Vec2> lineVertices;
	lineVertices.push_back(( m_position+m_parentPosition) );

	lineVertices.push_back( b2Vec2(pair.second)+m_parentPosition );

	ElementLines currentLine;
	currentLine.initElement(&lineVertices,5.f,Color4f(1.f,1.f,1.f,1.f),0xAAAA,50.f);

	lines.push_back(currentLine);

	/*
	BOOST_FOREACH( ConnectedItemsMap::value_type &i , m_connectedMapItems )
	{
		lineVertices.push_back( b2Vec2(i.second) );

		ElementLines currentLine;
		currentLine.initElement(&lineVertices,10.f,Color4f(1.f,1.f,1.f,1.f));

		lines.push_back(currentLine);

		lineVertices.pop_back();
		//printf("ID: %i ",i.second.getObjectID());
	}*/
}

std::pair<GLuint,b2Vec2> GUIMapItem::getMapItemData()
{
	return std::pair<GLuint,b2Vec2>(m_mapItemID,m_position);
}

bool GUIMapItem::isConnected(GLuint mapItemID)
{		//std::find(vector.begin(), vector.end(), item)!=vector.end()
	if( std::find(connectedItemID.begin(),connectedItemID.end(),mapItemID) != connectedItemID.end())	return true;
	
	return false;
	
}

GLint GUIMapItem::update()
{
	isActiveMapElement=false;
	return mapElement.update();

	return -1;
}

void GUIMapItem::setCurrentActiveMapElement()
{
	isActiveMapElement=true;
}

void GUIMapItem::renderLines()
{
	if(mapElement.isHovered())
	{
		for(int i=lines.size()-1; i>=0 ;i--)
		{
			lines[i].render();
		}
	}
}

void GUIMapItem::render()
{
	if(isActiveMapElement)	m_mapSheet->renderSprite(3,m_position.x+m_parentPosition.x,m_position.y+m_parentPosition.y);
	else mapElement.render();
}

GLuint GUIMapItem::getMapItemID()
{
	return m_mapItemID;
}