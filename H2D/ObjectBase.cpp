#include "ObjectBase.h"
/*
b2World* ObjectBase::world = new b2World(b2Vec2(0.f,0.f));
b2Vec2 ObjectBase::worldPos=b2Vec2(0.f,0.f);

boost::ptr_vector<pObject> ObjectBase::objects;
GLint ObjectBase::velocityIterations=8;
GLint ObjectBase::positionIterations=3;

ObjectBase::ObjectBase(void)
{
}


ObjectBase::~ObjectBase(void)
{
}

void ObjectBase::setWorldPos(b2Vec2 pos)
{
	worldPos=pos;
	return;
}
b2Vec2 ObjectBase::getWorldPos()
{
	return worldPos;
}
b2World* ObjectBase::getWorld()
{
	return world;
}

void ObjectBase::update()
{
	world->Step(1.f/TICKS_PER_SECOND,velocityIterations, positionIterations); //TICKS_PER_SECOND
	world->ClearForces();
}

b2Vec2 ObjectBase::getGravity()
{
	return world->GetGravity();
}
void ObjectBase::setGravity(b2Vec2 gravity)
{
	world->SetGravity(gravity);
}

GLuint  ObjectBase::addObjectInternal(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].init(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,&objects[number],materialT);
	return number;
}
GLuint  ObjectBase::addPolygonInternal(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].initPolygon(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,vertices,&objects[number],materialT);
	return number;
}
GLuint ObjectBase::addCircleInternal(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT, void* xxx)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].initCircle(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,&objects[number],materialT,xxx);
	return number;
}

int ObjectBase::testFunc()
{
	return 3;
}

pObject*  ObjectBase::addObject(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT)
{
	GLuint objectID = addObjectInternal(position,objectType,angle,density,friction,restitution,sheet,sprite,materialT);
	body = objects[objectID].getBody();
	return object = &objects[objectID];

}
pObject* ObjectBase::addCircle(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT, void* xxx)
{
	GLuint objectID = addCircleInternal(position,objectType,angle,density,friction,restitution,sheet,sprite,materialT,xxx);
	body = objects[objectID].getBody();
	return object = &objects[objectID];
}
pObject*  ObjectBase::addPolygon(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT)
{
	GLuint objectID = addPolygonInternal(position,objectType,angle,density,friction,restitution,sheet,sprite,vertices,materialT);
	body = objects[objectID].getBody();
	return object = &objects[objectID];
}



void ObjectBase::renderObjects()
{
	for(int i=objects.size()-1;i>=0;i--)
	{
			objects[i].render();
	}
}
*/