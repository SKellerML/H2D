#include "Entity.h"

GLuint Entity::sheetEntityID;
SpriteSheet2D* Entity::sheetEntity;
lua_State* Entity::luaStateEntity = lua_open();
std::vector<entity_object> Entity::listOfEntities;

typedef int(*lua_CFunction) (lua_State *L);

int distanceSquared(lua_State *L)
{
	//isInArea(xpos1,ypos1,xpos2,ypos2)
	lua_pushnumber(L,b2DistanceSquared(b2Vec2(lua_tonumber(L, 1), lua_tonumber(L, 2)), b2Vec2(lua_tonumber(L, 3), lua_tonumber(L, 4))));
	return 1;
}
int setPosition(lua_State *L)
{

	//isInArea(xpos1,ypos1,xpos2,ypos2)
	lua_pushnumber(L, b2DistanceSquared(b2Vec2(lua_tonumber(L, 1), lua_tonumber(L, 2)), b2Vec2(lua_tonumber(L, 3), lua_tonumber(L, 4))));
	return 1;
}
int distanceSquared(lua_State *L)
{
	//isInArea(xpos1,ypos1,xpos2,ypos2)
	lua_pushnumber(L, b2DistanceSquared(b2Vec2(lua_tonumber(L, 1), lua_tonumber(L, 2)), b2Vec2(lua_tonumber(L, 3), lua_tonumber(L, 4))));
	return 1;
}
int distanceSquared(lua_State *L)
{
	//isInArea(xpos1,ypos1,xpos2,ypos2)
	lua_pushnumber(L, b2DistanceSquared(b2Vec2(lua_tonumber(L, 1), lua_tonumber(L, 2)), b2Vec2(lua_tonumber(L, 3), lua_tonumber(L, 4))));
	return 1;
}
int distanceSquared(lua_State *L)
{
	//isInArea(xpos1,ypos1,xpos2,ypos2)
	lua_pushnumber(L, b2DistanceSquared(b2Vec2(lua_tonumber(L, 1), lua_tonumber(L, 2)), b2Vec2(lua_tonumber(L, 3), lua_tonumber(L, 4))));
	return 1;
}


void Entity::loadEntities()
{
	luaStateEntity = lua_open();

	luaL_openlibs(luaStateEntity);


	sheetEntityID = BaseObject::addSheet(&std::string("items2.png"));
	sheetEntity = BaseObject::getSpriteSheet(sheetEntityID);

	//sheetEntity->addClipSprite(Rect(0.f, 0.f, 128.f, 192.f));

	// Declare C++ Functions usable in LUA
	lua_register(luaStateEntity, "distanceSquared", distanceSquared);


	// END DECLARE FUNCTIONS


	luaL_dofile(luaStateEntity, "..//Debug//test.lua");

	// Get number of entities to load
	int numberOfEntities = 0;

	lua_getglobal(luaStateEntity, "definition");
	lua_call(luaStateEntity, 0, 1);

	numberOfEntities = lua_tointeger(luaStateEntity, 1);
	printf("Number of Entities: %i ", numberOfEntities);

	lua_pop(luaStateEntity, lua_gettop(luaStateEntity));


	// Load Entities
	int spritePos[4];
	//std::string numbers[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	std::string currentNumberString = "0";
	std::string load = "load";
	for (int i = 0; i < numberOfEntities; i++)
	{
		currentNumberString = std::to_string(i);
		std::cout << "\nPeter ist nicht lustig! " << load + currentNumberString << std::endl;
		lua_getglobal(luaStateEntity, (load + currentNumberString).c_str());

		lua_call(luaStateEntity, 0, 9);

		for (int i = 0; i < 4; i++)
		{
			spritePos[i] = (int)lua_tointeger(luaStateEntity, (i + 1));
			//lua_remove(L, 1);
			printf("Summe: %i ", spritePos[i]);
		}
		// Select Sprite from SpriteSheet
		sheetEntity->addClipSprite(Rect(spritePos[0], spritePos[1], spritePos[2], spritePos[3]));

		printf("\n");
		std::cout << "Top: " << lua_gettop(luaStateEntity) << std::endl;
		listOfEntities.reserve(numberOfEntities);

		entity_object obj(lua_tostring(luaStateEntity, 5), 0, lua_tostring(luaStateEntity, 6), lua_tostring(luaStateEntity, 7), lua_tostring(luaStateEntity, 8), lua_tostring(luaStateEntity, 9));
		obj.id = 0;
		std::cout << "Const char*************: " << obj.render << std::endl;

		listOfEntities.push_back(obj);
		lua_pop(luaStateEntity, lua_gettop(luaStateEntity));
	}
	// Clear lua Stack, for security
	lua_pop(luaStateEntity, lua_gettop(luaStateEntity));
	//lua_pop(L, 5);	// currently: empty whole stack

	//std::cout << "Name: " << num << std::endl;
	//std::cout << "Top: " << lua_gettop(luaStateEntity) << std::endl;

	/* SINGLE ENTITY ONLY ATM */

	//sheetEntity->addClipSprite(Rect(148.f, 25.f, 24.f, 16.f));
	//sheetEntity->addClipSprite(Rect(192.f, 0.f, 64.f, 10.f));
	//sheetEntity->addClipSprite(Rect(256.f, 0.f, 64.f, 64.f));
	//sheetEntity->addClipSprite(Rect(320.f, 0.f, 64.f, 64.f));
	//sheetEntity->addClipSprite(Rect(384.f, 0.f, 64.f, 64.f));

}
void Entity::deleteEntities()
{
	lua_close(luaStateEntity);
}


void Entity::init(b2Vec2 position, int entityID)
{
	m_id = entityID;
	m_position = position;
	//initBaseObject()
	// Call Lua function

	// Better put this in initObject
	currentRenderSpriteSheet = sheetEntityID;
	currentRenderSprite=m_id;

	lua_getglobal(luaStateEntity, listOfEntities[m_id].init.c_str());
	lua_call(luaStateEntity, 0, 0);

	initObject(m_id, COLLISIONOBJECTTYPE_CAR, position, 90.f, b2_dynamicBody, 1000.f, .2f, 0.f, true, NULL, NULL, -1);

}
void Entity::update()
{
	if (listOfEntities[m_id].update.size() != 0)
	{
		// Call Lua function
		lua_getglobal(luaStateEntity, listOfEntities[m_id].update.c_str());

		lua_pushboolean(luaStateEntity, GameState::handler->isPressed(GameHandler::KEY_USE));// maybe check in c++, check only area around using object || check states etc.

		//if (Engine::mouseHover()) // NEED UPPER LEFT AND SIZE
		lua_pushboolean(luaStateEntity, false);

		lua_call(luaStateEntity, 2, 0);
	}
}
void Entity::render()
{
	if (listOfEntities[m_id].render.size() != 0)
	{
		// Call Lua function
		lua_getglobal(luaStateEntity, listOfEntities[m_id].render.c_str());
		lua_call(luaStateEntity, 0, 0);
	}
	sheetEntity->renderSprite(0, 100 * m_position.x + worldPos.x, 100 * m_position.y + worldPos.y);
}