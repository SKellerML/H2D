#pragma once


#include "BaseObject.h"
#include "Entity.h"
#include "Door.h"
#include "Item.h"
#include "LevelContactListener.h"
#include "OpenGLH.h"
#include "Person.h"
#include "SpriteSheet2D.h"
#include "TileMap.h"

#include <Box2D\Box2D.h>
#include <boost\foreach.hpp>
#include <boost\ptr_container\ptr_vector.hpp>
#include <boost\smart_ptr.hpp>

#include <fstream>
#include <ostream>
#include <sstream>



struct ObjectMapType
{
	ObjectMapType() { ground = std::map< GLuint, std::shared_ptr<BaseObject> >(); normal = std::map< GLuint, std::shared_ptr<BaseObject> >(); }

	std::map< GLuint, std::shared_ptr<BaseObject> > ground;
	std::map< GLuint, std::shared_ptr<BaseObject> > normal;
};

class ObjectList
{
public:
	ObjectList(void);
	~ObjectList(void);

	static void loadObjectList();
	static void update(int id); // -1 for everything
	static void render(int id);	// -1 for everything
	static void renderLights(int id);
	static void destroy();

	// Object Loading methods
	static GLuint addObject(std::shared_ptr<BaseObject> object, int floor = -1, bool onFloor = false);// Add an object to the currently active ObjectList, (or any other specified List?) //  GLfloat density,GLfloat restitution,GLuint sheet,GLuint sprite,pObject* data,GLuint materialT);
	static GLuint addObject(GLuint objectType,b2Vec2 pos, GLfloat angle, int floor = -1, int objectState = -1);
	static bool deleteObjects();	

	static BaseObject* getBaseObject(GLuint gameObjectType, GLuint objectID);
	//static void addCreateItem()	{ mapmap.insert(std::make_pair(0, std::make_shared<BaseObject>(new Item()))); }
	//static void removeItem(GLuint id);
	static void addFloor(std::ifstream *fStream, GLuint sX, GLuint sY);
	static void setFloor(GLuint floorID);
	static void saveFloors(std::ofstream &saveStream);
	static void clearAllFloors();

	static TileMap* getCurrentTileMap()	{ return &tm[currentFloor]; }

	static GLuint getSizeX() { return tm[0].getSizeX(); }

private:
	
	//static int m_currentObjectID;	// saves current object ID
	//boost::ptr_vector<b2Body> bodies;
	
	typedef std::map<GLuint,GLuint> objectListMap;
	// Object vectors
	static GLuint currentFloor;

	static std::vector<int> m_currentObjectID;
	static std::vector<ObjectMapType> objectMap; // std::array<std::map< GLuint, std::shared_ptr<BaseObject> >, 2 > 
	static std::vector<TileMap> tm;
	static std::vector< std::shared_ptr<b2World> > worldContainer;

	static LevelContactListener contactListener;

	/*
	typedef std::map<int,Entity> entityMap;
	std::map<int,Entity> objects_entity;
	
	typedef std::map<int,Ship> shipMap;
	std::map<int,Ship> objects_ship;
	
	typedef std::map<int,AIShip> aiShipMap;
	std::map<int,AIShip> objects_aiShip;*/
	//std::vector<Entity> objects_entity;
	//std::vector<Ship> objects_ship;
};

