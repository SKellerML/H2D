#include "BaseObject.h"

std::shared_ptr<b2World> BaseObject::world;
GLint BaseObject::velocityIterations=8;
GLint BaseObject::positionIterations=3;
std::vector< std::shared_ptr<b2World> >* BaseObject::worldContainer;
int BaseObject::currentFloor;

int BaseObject::ScaleFactor = 100;

b2Vec2 BaseObject::worldPos;

boost::ptr_vector<SpriteSheet2D> BaseObject::sheetList;
std::map<GLuint, DeleteData> BaseObject::deletionMap;
std::map<GLuint, GLuint> BaseObject::wallDestructionMap;

GLuint BaseObject::debugSheet1=0;

GLuint BaseObject::standardFixtureValue=0;

BaseObject::addObjectFPTR BaseObject::addObject;


BaseObject::BaseObject(void)
{
	alive=false;
	isDestroyed = false;
}


BaseObject::~BaseObject(void)
{
	//body=NULL;
	alive = false;
}

void BaseObject::loadSheets()
{
	BaseObject::addSheet(&std::string("dSheet.png"));
	for (int i = 0; i < 500; i+=100)	BaseObject::addSprite(Rect((float)i,0.f,50.f,50.f),0);


	BaseObject::addSheet(&std::string("tileMap.png"));
	for (int i = 0; i < 10; i++)
	{
		for (int u = 0; u < 10; u++)
		{
			BaseObject::addSprite(Rect((float)u*64.f, i*64.f, 64.f, 64.f), 1);
		}
	}

	GLuint ss = addSheet(&std::string("PersonSheet.png"));
	addSprite(Rect(0.f, 0.f, 49.f, 49.f), ss);
	addSprite(Rect(49.f, 0.f, 49.f, 49.f), ss);
}

void BaseObject::initBaseObject(GLuint(*func)(GLuint, b2Vec2, GLfloat, int, int))
{
	addObject = func;
	//world=new b2World(b2Vec2(0.f,-10.f));
}
void BaseObject::loadBaseObjectSpriteSheets()
{
	debugSheet1 = addSheet(&std::string("dbug.png"));
	addSprite(Rect(0.f,0.f,100.f,100.f),debugSheet1);
	addSprite(Rect(0.f,100.f,100.f,100.f),debugSheet1);
}
// Sprite Sheet handling methods
GLuint BaseObject::addSheet(std::string *sheetLocation)
{
	
	sheetList.push_back(new SpriteSheet2D());
	int num = sheetList.size()-1;
	sheetList[num].loadTextureFromFile32(*sheetLocation);

	return num;
}
void BaseObject::deleteSheets()
{
	sheetList.clear();
}
GLuint BaseObject::addSprite(Rect &obj,GLuint sheet)
{
	GLuint c = sheetList[sheet].addClipSprite(obj);
	return c;
}
SpriteSheet2D* BaseObject::getSpriteSheet(int id)
{
	if(id < sheetList.size() && id > 0)		return &sheetList[id];
	else	return &sheetList[0];
}


// World handling methods
void BaseObject::setWorld(std::shared_ptr<b2World> w)
{
	world=w;
}
std::shared_ptr<b2World> BaseObject::getWorld()
{
	return world;
}
void BaseObject::updateWorld()
{
	world->Step(1.f/TICKS_PER_SECOND*.5,velocityIterations,positionIterations);
}


void BaseObject::initObject(GLuint gameObjectType, GLuint collisionObjectType, b2Vec2 position, GLfloat angle, b2BodyType bodyType, GLfloat mass, GLfloat friction, GLfloat restitution, bool isSquare, void* obj, int* id, int floor)
{
	// fixture saves object Type
	// body saves object

	objectID = gameObjectType;

	alive = true;

	RectVAO rv = sheetList[currentRenderSpriteSheet].getRectVAO(currentRenderSprite);
	if (isSquare)	halfSize.Set((rv.r.w / 100.f) / 2.f, (rv.r.h / 100.f) / 2.f);
	else			halfSize.Set((rv.r.w / 100.f) / 2.f, -1.f);
	printf("HS: %f \n", halfSize.x);
	// Body Definition
	b2BodyDef bodyDefinition;
	bodyDefinition.type = bodyType;

	bodyDefinition.position.Set(position.x,position.y);
	bodyDefinition.userData = obj;//data;
	bodyDefinition.linearDamping = 10.f;
	bodyDefinition.angularDamping = 5.f;

	bodyDefinition.angle = (angle*2*b2_pi)/360;
	if (floor < 0 || floor >= worldContainer->size())
	{
		body = world->CreateBody(&bodyDefinition);
		m_floor = currentFloor;
	}
	else
	{
		body = worldContainer->at(floor)->CreateBody(&bodyDefinition);
		m_floor = floor;
	}


	// Fixture
	b2FixtureDef fixture;
	fixture.density=0.5;
	fixture.friction=friction;
	fixture.restitution=restitution;
	fixture.userData = &objectID; //see setObject
	fixture.filter.categoryBits = collisionObjectType;

	switch(collisionObjectType)
	{
	case COLLISIONOBJECTTYPE_WALL || COLLISIONOBJECTTYPE_CAR:	fixture.filter.maskBits = COLLISIONOBJECTMASK_ALL;
		break;
	case COLLISIONOBJECTTYPE_PERSON:	fixture.filter.maskBits = COLLISIONOBJECTMASK_PERSON;
		break;
	}

	if(isSquare)
	{
		b2PolygonShape box;
		box.SetAsBox(halfSize.x,halfSize.y);
		fixture.shape = &box;
		body->CreateFixture(&fixture);
	}
	else
	{
		b2CircleShape circle;
		circle.m_radius=halfSize.x;

		fixture.shape = &circle;
	
		body->CreateFixture(&fixture);		
	}
	
	if(mass > 0.f)
	{
		b2MassData* massData=new b2MassData;
		body->GetMassData(massData);
		massData->mass=mass;
		massData->I =mass;
		massData->center=b2Vec2(0.f,0.f);
		body->SetMassData(massData);
		delete massData;
	}
	
}

void BaseObject::initPolygon(GLuint gameObjectType, GLuint collisionObjectType, b2Vec2 position, GLfloat angle, b2BodyType bodyType, GLfloat mass, GLfloat friction, GLfloat restitution, std::vector<b2Vec2> vertices, void* obj, int* id, int floor)
{

	RectVAO rv = sheetList[currentRenderSpriteSheet].getRectVAO(currentRenderSprite);
	halfSize.Set((rv.r.w/100.f)/2,(rv.r.h/100.f)/2);

	objectID = gameObjectType;

	// Body Definition
	b2BodyDef bodyDefinition;
	bodyDefinition.type = bodyType;
	bodyDefinition.position.Set(position.x-halfSize.x,position.y+halfSize.y);
	bodyDefinition.userData = obj;//data;
	bodyDefinition.angularDamping = 0.5f;
	bodyDefinition.angle = (angle*2*b2_pi)/360;
	if (floor < 0 || floor >= worldContainer->size())
	{
		body = world->CreateBody(&bodyDefinition);
		m_floor = currentFloor;
	}
	else
	{
		body = worldContainer->at(floor)->CreateBody(&bodyDefinition);
		m_floor = floor;
	}

	// Fixture
	b2FixtureDef fixture;
	fixture.density=0.5;
	fixture.friction=friction;
	fixture.restitution=restitution;
	fixture.userData = &objectID; // see setObject
	fixture.filter.categoryBits = collisionObjectType;

	switch (collisionObjectType)
	{
	case COLLISIONOBJECTTYPE_WALL || COLLISIONOBJECTTYPE_CAR:	fixture.filter.maskBits = COLLISIONOBJECTMASK_ALL;
		break;
	case COLLISIONOBJECTTYPE_PERSON:	fixture.filter.maskBits = COLLISIONOBJECTMASK_PERSON;
		break;
	}

	b2PolygonShape polygon;
	
	int numberOfVertices = vertices.size();

	b2Vec2 *vs=new b2Vec2[numberOfVertices];

	for(int i=0;i < numberOfVertices;i++)
	{
		vs[i] = vertices[i];
	}

	polygon.Set(vs,numberOfVertices);
	fixture.shape = &polygon;
	fixture.userData = &standardFixtureValue;

	body->CreateFixture(&fixture);

	delete[] vs;

	if(mass > 0.f)
	{
		b2MassData* massData=new b2MassData;
		body->GetMassData(massData);
		massData->mass=mass;
		massData->I =0.1f;
		massData->center=b2Vec2(0.f,0.f);
		body->SetMassData(massData);
		delete massData;
	}
}

b2Vec2 BaseObject::getWorldPos()
{
	return worldPos;
}

std::map<GLuint,DeleteData>* BaseObject::getDeletionMap()
{
	return &deletionMap;
}
void BaseObject::clearDeletionMap()
{
	deletionMap.clear();
}
void BaseObject::deleteObject( GLuint ID, GLuint floor,bool onGround)
{
	deletionMap.insert(std::pair<GLuint, DeleteData>(ID, DeleteData(floor, onGround)));
}

void BaseObject::destroy()
{
	worldContainer->at(m_floor)->DestroyBody(body);
	alive=false;
	body=NULL;
}

bool BaseObject::isInArea(b2Vec2 position,GLfloat radius)
{
	return b2Distance(body->GetPosition(),position) < radius;
}
b2Vec2 BaseObject::getPosition()
{
	return body->GetPosition();
}