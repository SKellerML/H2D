#include "Wall.h"

GLuint Wall::gameobjectType = GAMEOBJECTTYPE_WALL;

Wall::Wall()
{
	body = nullptr;
	active = false;
}


Wall::~Wall()
{
}

void Wall::init(b2Vec2 startPos, b2Vec2 targetPos)
{
	//currentRenderSpriteSheet = 1;
	//currentRenderSprite = 27;
	m_startPos = startPos;
	m_endPos = targetPos;
	//initObject(0, pos, 0.f, b2_dynamicBody, 1.f, .1f, 0.f, true,NULL,NULL);
	b2BodyDef bdef;
	bdef.position.Set((startPos.x + targetPos.x) / 2.f, (startPos.y + targetPos.y) / 2.f);
	bdef.type = b2_staticBody;
	body = world->CreateBody(&bdef);

	b2PolygonShape shape;
	shape.SetAsBox(	(abs(targetPos.x - startPos.x )) / 2.f + 0.32f, (abs(targetPos.y - startPos.y)) / 2.f +0.32f );
	//printf("PosX: %f \n", (abs(targetPos.x - startPos.x)) / 2.f + 0.32f);
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.f;
	fd.filter.categoryBits = COLLISIONOBJECTTYPE_WALL;

	fd.userData.pointer =  uintptr_t(&gameobjectType);
	body->CreateFixture(&fd);

	std::vector<b2Vec2> vs;
	
	vs.push_back(100 * body->GetWorldPoint(shape.m_vertices[0]));
	vs.push_back(100 * body->GetWorldPoint(shape.m_vertices[1]));
	vs.push_back(100 * body->GetWorldPoint(shape.m_vertices[2]));
	vs.push_back(100 * body->GetWorldPoint(shape.m_vertices[3]));

	bool showDebugColors = true;
	GLfloat randCol[3];
	if (showDebugColors)
	{
		randCol[0] = (float)(rand() % 100) / 100;
		randCol[1] = (float)(rand() % 100) / 100;
		randCol[2] = (float)(rand() % 100) / 100;
		polpol.initElement(&vs, Color4f(randCol[0], randCol[1], randCol[2], 0.5f));
	}

	active = true;
}

void Wall::update()
{

}
void Wall::render()
{
	//if (!body)	return;
	//b2Vec2 pos = body->GetPosition();
	//sheetList[0].renderSprite(0, worldPos.x + pos.x*100.f, worldPos.y + pos.y*100.f, 1.f, 1.f, toAngle(body->GetAngle()));
	if(active)	polpol.render(worldPos);
}