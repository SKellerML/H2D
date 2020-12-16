#pragma once

#include "Explosion.h"
#include "BaseObject.h"
#include "Light.h"
#include "TickCounter.h"
#include "GameState.h"

//extern "C"{
//	#include "lua.h"
//	#include "lualib.h"
//	#include "lauxlib.h"
//}

struct entity_object
{
	std::string init;
	std::string update;
	std::string render;	// const char* instead, null if not specified
	std::string renderLight;

	std::string name;
	int id;

	entity_object(std::string name_, int id_, std::string init_, std::string update_, std::string render_, std::string renderLight_) : name(name_), id(id_), init(init_), update(update_), render(render_), renderLight(renderLight_){}
	entity_object(int id_) : id(id_) { render = ""; renderLight = ""; }
};

class Entity : public BaseObject
{
public:
	Entity() {}
	//Entity(b2Vec2 pos, GLfloat angle, GLuint id);
	~Entity() {}

	// Create Wall from starpos to targetPos as squares, but pyhsics coordinates
	//virtual void init(b2Vec2 pos, GLfloat angle, GLuint id);
	void init(b2Vec2 position, int entityID);
	void update();
	void render();
	void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture) override	{}
	void use();

	//void destroyWall()	{ world->DestroyBody(body); }


	//static void loadEntities();
	//static void deleteEntities();

protected:
	ElementPolygon polpol;

	int m_id;
	b2Vec2 m_position;

	//static lua_State* luaStateEntity;

	static GLuint sheetEntityID;
	static SpriteSheet2D* sheetEntity;
	static std::vector<entity_object> listOfEntities;
};

