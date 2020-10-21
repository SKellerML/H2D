#pragma once

#include "OpenGLH.h"

enum GameObjectTypeEnum
{
	GAMEOBJECT_ENTITY
};

struct GameObjectType
{
	GLuint id;
};

class ObjectBasePolymorphism
{
public:
	ObjectBasePolymorphism(void);
	~ObjectBasePolymorphism(void);

	virtual void isHitByLaser() = 0;

	virtual GLuint getID()=0;

	GameObjectType gameObjectType;
	
	int c;

};

