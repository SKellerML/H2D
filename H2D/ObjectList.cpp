#include "ObjectList.h"

//int ObjectList::m_currentObjectID;

//std::map< GLuint, std::shared_ptr<BaseObject> > ObjectList::mapmap;
GLuint ObjectList::currentFloor;

std::vector<int> ObjectList::m_currentObjectID;
std::vector< ObjectMapType > ObjectList::objectMap;
std::vector<TileMap> ObjectList::tm;
std::vector< std::shared_ptr<b2World> > ObjectList::worldContainer;
LevelContactListener ObjectList::contactListener;

ObjectList::ObjectList(void)
{
	//m_currentObjectID=0;
	//world = new b2World(b2Vec2(0.f, 0.f));
	//BaseObject::setWorld(world);
}



ObjectList::~ObjectList(void)
{
}

void ObjectList::destroy()	
{
	/*player.~Player();
	objects_entity.clear();
	objects_ship.clear();
	objects_aiShip.clear();*/
	//BaseObject::destroyWorld();	
}


/*
// World handling methods
void ObjectList::setWorld(b2World* w)
{
	world=w;
}
b2World* ObjectList::getWorld()
{
	return world;
}
*/
void ObjectList::update(int id)
{


	for (std::map<GLuint, std::shared_ptr<BaseObject> >::iterator it = objectMap[currentFloor].normal.begin(); it != objectMap[currentFloor].normal.end(); ++it)
	{
		it->second->update();
	}
	for (std::map<GLuint, std::shared_ptr<BaseObject> >::iterator it = objectMap[currentFloor].ground.begin(); it != objectMap[currentFloor].ground.end(); ++it)
	{
		it->second->update();
	}

	//deleteObjects();
}

void ObjectList::render(int id)
{
	
	tm[currentFloor].render();//GLdouble timeStamp = glfwGetTime();
	for (std::map<GLuint, std::shared_ptr<BaseObject> >::iterator it = objectMap[currentFloor].ground.begin(); it != objectMap[currentFloor].ground.end(); ++it)
	{
		it->second->render();
	}
	for (std::map<GLuint, std::shared_ptr<BaseObject> >::iterator it = objectMap[currentFloor].normal.begin(); it != objectMap[currentFloor].normal.end(); ++it)
	{
		//printf("Size: %i \n", objectMap[currentFloor].size());
		it->second->render();
	}
	//printf("Time::: %f \n", (float)(glfwGetTime() - timeStamp));
//	switch(id)
//	{
//	case -1:
//		BOOST_FOREACH( entityMap::value_type &i , objects_entity )
//		{
//			i.second.render();
//		}
//		BOOST_FOREACH( shipMap::value_type &i, objects_ship)
//		{
//			i.second.render();
//		}
//		BOOST_FOREACH( aiShipMap::value_type &i, objects_aiShip)
//		{
//			i.second.render();
//		}
//
//		player.renderPlayer();
//		break;
//	};
}
void ObjectList::renderLights(int id)
{
	// Floor objects have no light

	for (std::map<GLuint, std::shared_ptr<BaseObject> >::iterator it = objectMap[currentFloor].normal.begin(); it != objectMap[currentFloor].normal.end(); ++it)
	{
		//printf("Size: %i \n", objectMap[currentFloor].size());
		it->second->renderLight();
	}
}

// Object Loading methods

GLuint ObjectList::addObject(GLuint objectType, b2Vec2 pos, GLfloat angle, int floor, int objectState)
{
	Entity ent;
	ent.init(pos, objectType);//,objectState);
	return addObject(std::make_shared<Entity>(ent), floor, true);

	//switch (objectType)
	//{
	//case OBJECTTYPE_C4:
	//{
	//					  C4 obj;
	//					  obj.init(pos, angle, additionalInfo, floor);
	//					  return addObject(std::make_shared<C4>(obj), floor, true);
	//}
	//	break;
	//case OBJECTTYPE_POLICECAR:
	//{
	//							 PoliceCar obj;
	//							 obj.init(pos, angle, additionalInfo, floor);
	//							 return addObject(std::make_shared<PoliceCar>(obj), floor);
	//}
	//	break;


	//case OBJECTTYPE_DOOR:
	//{
	//						Door obj;
	//						obj.initDoor(pos, additionalInfo, false, floor);
	//						return addObject(std::make_shared<Door>(obj), floor);
	//}
	//	break;
	//case OBJECTTYPE_MONEYPILE:
	//{
	//							 MoneyPile obj(pos, angle, additionalInfo);
	//							 return addObject(std::make_shared<MoneyPile>(obj), floor, true);
	//}
	//	break;
	//case OBJECTTYPE_DEAD_BODY:
	//{
	//							 DeadBody obj(pos, angle, additionalInfo);
	//							 return addObject(std::make_shared<DeadBody>(obj), floor, true);
	//}
	//	break;
	//case OBJECTTYPE_PERSON:
	//{
	//						  Person obj;// (os, angle, additionalInfo);
	//						  obj.init(pos, floor);
	//						  return addObject(std::make_shared<Person>(obj), floor, false);
	//}
	//case OBJECTTYPE_CIVILIAN | OBJECTTYPE_GUARD:
	//	printf("It has happened!\n");
	//	break;
	/*
	case OBJECTTYPE_CIVILIAN:
	{
							  Civilian obj;// (os, angle, additionalInfo);
							  obj.init(pos, floor);
							  return addObject(std::make_shared<Civilian>(obj), floor, false);
	}
	case OBJECTTYPE_GUARD:
	{
							  Guard obj;// (os, angle, additionalInfo);
							  obj.init(pos, floor);
							  return addObject(std::make_shared<Guard>(obj), floor, false);
	}
		break;
	}*/
	return 0;
}

GLuint ObjectList::addObject(std::shared_ptr<BaseObject> object, int floor, bool onFloor)
{
	if (floor < 0 || floor >= tm.size()) floor = currentFloor;
	
	// Set object i
	if (onFloor) objectMap[floor].ground.at(m_currentObjectID[floor])->setObject( objectMap[floor].ground.insert(objectMap[floor].ground.end(), std::make_pair(++m_currentObjectID[floor], object))->second, m_currentObjectID[floor] );
	else objectMap[floor].normal.at(m_currentObjectID[floor])->setObject( objectMap[floor].normal.insert(objectMap[floor].normal.end(), std::make_pair(++m_currentObjectID[floor], object))->second, m_currentObjectID[floor] );

	return m_currentObjectID[floor];
}


bool ObjectList::deleteObjects()
{
	std::map<GLuint,DeleteData>* delMap = BaseObject::getDeletionMap();

	for (std::map<GLuint, DeleteData>::iterator it = delMap->begin(); it != delMap->end(); ++it)
	{
		if (it->second.onGround)
		{
			objectMap[it->second.floor].ground.at(it->first)->destroy();
			objectMap[it->second.floor].ground.erase(it->first);
		}
		else
		{
			printf("First: %i ||Second: %i \n", it->second.floor, it->first);
			objectMap[it->second.floor].normal.at(it->first)->destroy();
			objectMap[it->second.floor].normal.erase(it->first);
		}
	}

	BaseObject::clearDeletionMap();
	// Destroy Walls
	std::map<GLuint, GLuint>* desMap = BaseObject::getDestroyWallMap(); // <tileID,floor>

	for (std::map<GLuint, GLuint>::iterator it = desMap->begin(); it != desMap->end(); ++it)
	{
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		tm[it->second].destroyWall(it->first);
	}
	BaseObject::clearDestructionMap();
	return true;
}


//bool ObjectList::deleteObjects()
//{
//	std::map<GLuint,GLuint>* delMap = BaseObject::getDeletionMap();
//
//	GLuint ID;
//
//
//	
//	BOOST_FOREACH( objectListMap::value_type &i , *delMap )
//	{
//		ID=i.second;
//		switch(i.first)
//		{
//		case GAMEOBJECTTYPE_ENTITY:
//				
//				//objects_entity.find(ID)->second.~Entity();
//				objects_entity.find(ID)->second.destroy();
//				//objects_entity.erase(ID);
//
//			break;
//		case GAMEOBJECTTYPE_SHIP:
//				objects_ship.find(ID)->second.destroy();
//				//objects_ship.erase(ID);
//			break;
//		case GAMEOBJECTTYPE_AISHIP:
//				objects_aiShip.find(ID)->second.destroy();
//				//objects_aiShip.erase(ID);
//			break;
//			/*
//		case GAMEOBJECTTYPE_PLAYER:
//				player.loadShip(position,angle,idOfObjectMap,&player);
//				player.init();
//				return 0;
//			break;
//			*/
//		}
//	}
//	
//	BaseObject::clearDeletionMap();
//
//	return true;
//}
///*
//void ObjectList::update()
//{
//	
//
//	player.update();
//}
//*/
//bool ObjectList::getAIShip(GLfloat id,AIShip* ship)
//{
//	aiShipMap::iterator it=objects_aiShip.find(id);
//	
//	if( it == objects_aiShip.end() )	return false;
//	
//	ship = &it->second;
//	return true;
//}
//bool ObjectList::getEntity(GLfloat id,Entity** entity)
//{
//	entityMap::iterator it=objects_entity.find(id);
//	
//	if( it == objects_entity.end() )	return false;
//	
//	*entity = &objects_entity[id];
//	return true;
//}
//Player* ObjectList::getPlayer()
//{
//	return &player;
//}
//
//BaseObject* ObjectList::getBaseObject(GLuint gameObjectType,GLuint objectID)
//{
//	switch(gameObjectType)
//	{
//	case GAMEOBJECTTYPE_ENTITY:	if(objectID < objects_entity.size())	return &objects_entity[objectID];
//		break;
//	}
//}

void ObjectList::addFloor(std::ifstream *fStream, GLuint sX, GLuint sY)
{
	worldContainer.push_back( std::make_shared<b2World>(b2Vec2(0.f, 0.f)) )  ;
	worldContainer[worldContainer.size() - 1]->SetContactListener(&contactListener);

	BaseObject::setWorld(worldContainer[worldContainer.size() - 1]);
	tm.push_back(TileMap(fStream, sX, sY));
	objectMap.push_back(ObjectMapType());
	m_currentObjectID.push_back(0);
}

void ObjectList::setFloor(GLuint floorID)
{
	currentFloor = floorID;
	tm[currentFloor].setTileMaps();
	BaseObject::setWorld(worldContainer[currentFloor]);
	BaseObject::setCurrentFloor(currentFloor);
	//Person::setTileMap(&tm[currentFloor]);
}

void ObjectList::saveFloors(std::ofstream &saveStream)
{
	saveStream << "MAP\n";

	for (std::vector<TileMap>::iterator it = tm.begin(); it != tm.end(); ++it)
	{
		saveStream << "M\n";
		it->saveTileMap(saveStream);
		saveStream << "N\n";
	}
}

void ObjectList::clearAllFloors()
{
	currentFloor = - 1;
	m_currentObjectID.clear();
	objectMap.clear();
	tm.clear();
	worldContainer.clear();
}

void ObjectList::loadObjectList()
{
	printf("IsLoaded!");
	BaseObject::setWorldContainer(&worldContainer);
}