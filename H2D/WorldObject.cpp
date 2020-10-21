#include "WorldObject.h"
/*

WorldObject::WorldObject(void)
{
	world=new b2World(b2Vec2(0.f,0.f));
	pObject::setWorld(world);
	world->SetContactListener(new LevelContactListener());
	velocityIterations=8;
	positionIterations=3;

}

WorldObject::~WorldObject(void)
{
}

void WorldObject::update()
{
	world->Step(1.f/TICKS_PER_SECOND,velocityIterations, positionIterations); //TICKS_PER_SECOND
	world->ClearForces();
}

b2Vec2 WorldObject::getGravity()
{
	return world->GetGravity();
}
void WorldObject::setGravity(b2Vec2 gravity)
{
	world->SetGravity(gravity);
}

pObject*  WorldObject::addObject(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].init(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,&objects[number],materialT);
	return &objects[number];
}
pObject*  WorldObject::addPolygon(b2Vec2 position,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,GLuint materialT)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].initPolygon(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,vertices,&objects[number],materialT);
	return &objects[number];
}
pObject* WorldObject::addCircle(b2Vec2 position, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution, GLuint sheet, GLuint sprite, GLuint materialT)
{
	objects.push_back(new pObject());
	int number=objects.size()-1;
	objects[number].initCircle(position.x, position.y,objectType,angle,density,friction,restitution,sheet,sprite,&objects[number],materialT);
	return &objects[number];
}

void WorldObject::renderObjects()
{
	for(int i=objects.size()-1;i>=0;i--)
	{
			objects[i].render();
	}
}
*/