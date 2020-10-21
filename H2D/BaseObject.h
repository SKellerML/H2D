#pragma once

#include "OpenGLH.h"


#include "Game.h"
#include "SpriteSheet2D.h"

#include <Box2D\Box2D.h>
#include <vector>
#include <map>
#include <boost\smart_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>

#define toAngle(rad) (rad*180)/(b2_pi) // rad = 2*pi*alpha/360
#define toRad(a) (a*b2_pi)/180 // rad = (a*2*b2_pi)/360 => rad*360=a*2*pi => a=

enum ObjectTypes
{
	OBJECTTYPE_POLICECAR,
	OBJECTTYPE_C4,
	OBJECTTYPE_DOOR,
	OBJECTTYPE_MONEYPILE,
	OBJECTTYPE_DEAD_BODY,
	OBJECTTYPE_STONE,
	OBJECTTYPE_PERSON,
	OBJECTTYPE_CIVILIAN,
	OBJECTTYPE_GUARD,
};

enum CollisionObjectType
{
	COLLISIONOBJECTTYPE_WALL =		0x0001,
	COLLISIONOBJECTTYPE_CAR =		0x0002,
	COLLISIONOBJECTTYPE_PERSON =	0x0004,
	COLLISIONOBJECTTYPE_FLOOR =	0x0008,
	COLLISIONOBJECTTYPE_PARTICLE = 0x00016,
};

enum CollisionObjectMask
{
	COLLISIONOBJECTMASK_ALL = COLLISIONOBJECTTYPE_WALL | COLLISIONOBJECTTYPE_CAR | COLLISIONOBJECTTYPE_PERSON,
	COLLISIONOBJECTMASK_PERSON = COLLISIONOBJECTTYPE_WALL | COLLISIONOBJECTTYPE_CAR | COLLISIONOBJECTTYPE_PERSON,
	
};

// The categoryBits flag can be thought of as the fixture saying 'I am a ...', and the maskBits is like saying 'I will collide with a ...'.

enum GameObjectTyoe
{
	GAMEOBJECTTYPE_OBJECT = 1,
	GAMEOBJECTTYPE_PERSON,
	GAMEOBJECTTYPE_PARTICLE,
	GAMEOBJECTTYPE_BULLET,
	GAMEOBJECTTYPE_WALL,
};

struct HitData
{
	HitData(GLuint _weaponType, const float32 _impactImpulse[2], GLfloat _damageValue) : weaponType(_weaponType), damageValue(_damageValue) { impactImpulse.Set(_impactImpulse[0], _impactImpulse[1]); }
	HitData(GLuint _weaponType, b2Vec2 _impactImpulse, GLfloat _damageValue) : weaponType(_weaponType), impactImpulse(_impactImpulse), damageValue(_damageValue) {  }

	HitData() {}

	GLuint weaponType;
	b2Vec2 impactImpulse;
	GLfloat damageValue;
};

struct DeleteData
{
	DeleteData() {}
	DeleteData(GLuint _floor, bool _onGround) : floor(_floor), onGround(_onGround) {}

	GLuint floor;
	bool onGround;
};

struct PathNode
{
	PathNode()	{ distanceToNode = 0.f; estimateToTarget = 0.f; previousNode = 0; nodeID = 0; }
	PathNode(GLuint dist, GLuint est, GLuint previousN, GLuint _nodeID) : distanceToNode(dist), estimateToTarget(est), previousNode(previousN), nodeID(_nodeID)	{}

	GLuint getNodeValue()	{ return distanceToNode + estimateToTarget; }

	bool isClosed;
	GLuint nodeID;
	GLuint distanceToNode;
	GLuint estimateToTarget;
	GLuint previousNode;
};

class BaseObject
{
public:
	BaseObject(void);
	~BaseObject(void);
	
	static void loadSheets();
	// Sprite Sheet handling methods
	static GLuint addSheet(std::string *sheetLocation);
	static void deleteSheets();
	static GLuint addSprite(Rect &obj,GLuint sheet);
	static SpriteSheet2D* getSpriteSheet(int id);
	static void initBaseObject(GLuint(*func)(GLuint, b2Vec2, GLfloat, int, int));
	static void loadBaseObjectSpriteSheets();

	// World handling methods
	static void setWorld(std::shared_ptr<b2World> w);
	static std::shared_ptr<b2World> getWorld();
	static void updateWorld();
	static void destroyWorld()	
	{
		//delete world;
	}

	void initObject(GLuint gameObjectType, GLuint collisionObjectType, b2Vec2 position, GLfloat angle, b2BodyType bodyType, GLfloat mass, GLfloat friction, GLfloat restitution, bool isSquare, void* obj, int* id, int floor = -1);
	void initPolygon(GLuint gameObjectType, GLuint collisionObjectType, b2Vec2 position, GLfloat angle, b2BodyType bodyType, GLfloat mass, GLfloat friction, GLfloat restitution, std::vector<b2Vec2> vertices, void* obj, int* id, int floor = -1);

	// pObject* data,GLuint materialT, void* xxx

	bool isInArea(b2Vec2 position,GLfloat radius);
	b2Vec2 getPosition();



	virtual void update()=0;
	virtual void render()=0;
	virtual void renderLight() {}
	virtual void isHit(HitData* impactData,b2Vec2 collisionPoint,GLuint hitFixture)=0;
	virtual void listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious) {}

	void setObject(std::shared_ptr<BaseObject> objPtr, GLuint listID) { body->SetUserData(objPtr.get()); m_listID = listID; body->GetFixtureList()->SetUserData(&objectID); }

	static b2Vec2 getWorldPos();
	static void setWorldPos(b2Vec2 w)	{ worldPos = w; }

	// public vars
	int objectID;	
	b2Body* body;
	// 

	static void deleteObject(GLuint ID, GLuint floor, bool onGround);//=false
	static std::map<GLuint, DeleteData>* getDeletionMap();
	static void clearDeletionMap();

	static void destroyWall(GLuint tileID, GLuint floor = -1)
	{
		if (floor == -1)	floor = currentFloor;
		wallDestructionMap.insert(std::make_pair(tileID, floor));
	}
	static std::map<GLuint, GLuint>* getDestroyWallMap() { return &wallDestructionMap; }
	static void clearDestructionMap() { wallDestructionMap.clear(); }

	void destroy();

	GLuint getObjectID() {return objectID;}

	bool isAlive()	{return alive;};


	static void setCurrentFloor(int floor) { currentFloor = floor; }
	static void setWorldContainer(std::vector< std::shared_ptr<b2World> >* wC) { worldContainer = wC; }

	
private:
	uint16 getMaskBits(uint16 categoryBits);
	

protected:
	// All objects that are due to deletion
	typedef GLuint(*addObjectFPTR)(GLuint, b2Vec2, GLfloat, int, int);
	static addObjectFPTR addObject;

	static int currentFloor;

	static int ScaleFactor;

	static std::map<GLuint, DeleteData> deletionMap;
	static std::map<GLuint, GLuint> wallDestructionMap;

	// Sprite Sheet handling variables
	static boost::ptr_vector<SpriteSheet2D> sheetList;

	// World variables
	static std::shared_ptr<b2World> world;
	static std::vector< std::shared_ptr<b2World> >* worldContainer;
	static GLint velocityIterations, positionIterations;

	static b2Vec2 worldPos;

	static GLuint debugSheet1;

	GLuint currentRenderSprite;
	GLuint currentRenderSpriteSheet;

	bool alive;

	bool isExploding;

	b2Vec2 halfSize;

	GLfloat hitPoints;

	GLuint materialType;

	GLuint m_listID;
	GLuint m_floor;
	static GLuint standardFixtureValue;

	bool isDestroyed;
};

