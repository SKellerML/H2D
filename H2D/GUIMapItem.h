#pragma once

#include "OpenGLH.h"
#include "SpriteSheet2D.h"
#include "GUIImageElement.h"
#include "Element2D.h"

#include <Box2D\Box2D.h>
#include <map>
#include <algorithm>
#include <boost\foreach.hpp>

class GUIMapItem
{
public:
	GUIMapItem(void);
	~GUIMapItem(void);

	static void setSpriteSheet2D(SpriteSheet2D* sheet);

	void init(GLuint mapItemID, b2Vec2 position, b2Vec2 parentPosition, std::string name, std::string description);
	void addConnectedItem(GLuint id,b2Vec2 position);
	void addConnectedItem(std::pair<GLuint,b2Vec2> pair);
	std::pair<GLuint,b2Vec2> getMapItemData();

	bool isConnected(GLuint mapItemID);

	GLint update();
	void renderLines();
	void render();

	GLuint getMapItemID();

	void setCurrentActiveMapElement();

private:
	//typedef std::map<GLuint,b2Vec2> ConnectedItemsMap;
	//ConnectedItemsMap m_connectedMapItems;
	std::vector<GLuint> connectedItemID;
	std::vector<ElementLines> lines;

	std::string m_name;
	std::string m_description;
	b2Vec2 m_position;
	b2Vec2 m_parentPosition;
	GLuint m_mapItemID;
	GUIImageElement mapElement;

	bool isActiveMapElement;

	bool playerIsHere;

	static SpriteSheet2D* m_mapSheet;

};

