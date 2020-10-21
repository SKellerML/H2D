#include "pObject.h"
#include <math.h>
#include "Game.h"
#include "ObjectBase.h"

/*

//GLint pObject::velocityIterations = 8;
//sGLint pObject::positionIterations = 3;

b2Vec2 pObject::worldPos=b2Vec2(0.f,0.f);

LevelContactListener pObject::contactL;

boost::ptr_vector<SpriteSheet2D> pObject::sheetList;

b2World* pObject::world=ObjectBase::getWorld();

// Con-/Destructor

pObject::pObject(void)
{
	body=NULL;
}


pObject::~pObject(void)
{
	if(body!=NULL)
	{
		//world->DestroyBody(body);
		body=NULL;
	}
}

void pObject::setWorldPos(b2Vec2 pos)
{
	worldPos=pos;
	return;
}
b2Vec2 pObject::getWorldPos()
{
	return worldPos;
}

void pObject::update()
{
	//world->Step(1.f/TICKS_PER_SECOND,velocityIterations, positionIterations); //TICKS_PER_SECOND
	//world->ClearForces();
}



GLuint pObject::addSheet(std::string *sheetLocation)
{
	
	sheetList.push_back(new SpriteSheet2D());
	int num = sheetList.size()-1;
	sheetList[num].loadTextureFromFile32(*sheetLocation);

	return num;
}
void pObject::deleteSheets()
{
	sheetList.clear();
}
GLuint pObject::addSprite(Rect &obj,GLuint sheet)
{
	GLuint c = sheetList[sheet].addClipSprite(obj);
	return c;
}






b2Body* pObject::getBody()
{
	return body;
}

void pObject::applyForce(const b2Vec2 &force)
{
	body->ApplyForce(force,body->GetWorldCenter(),true);
}

void pObject::applyLinearImpulse(const b2Vec2 &impulse)
{
	body->ApplyLinearImpulse(impulse,body->GetWorldCenter(),true);
}
void pObject::applyAngularImpulse(GLfloat &impulse)
{
	body->ApplyAngularImpulse(impulse,true);
}



b2Body* pObject::init(GLfloat x, GLfloat y, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution,GLuint sheet,GLuint sprite,pObject* data,GLuint materialT)
{	
	materialType=materialT;

	if(!(sheet > sheetList.size()-1))
	{
		spriteSheet = sheet;
		spriteID = sprite;
	}
	else
	{
		spriteSheet = 0;
		spriteID = 0;
	}
	
	RectVAO rv = sheetList[sheet].getRectVAO(sprite);
	halfSize.Set((rv.r.w/100.f)/2,(rv.r.h/100.f)/2);
	
	// Body Definition
	b2BodyDef bodyDefinition;
	bodyDefinition.type = objectType;
	bodyDefinition.position.Set(x-halfSize.x,y+halfSize.y);
	bodyDefinition.userData = data;

	bodyDefinition.angle = (angle*2*b2_pi)/360;
	body=world->CreateBody(&bodyDefinition);

	// Fixture
	b2PolygonShape box;
	box.SetAsBox(halfSize.x,halfSize.y);

	b2FixtureDef fixture;
	fixture.density=density;
	fixture.friction=friction;
	fixture.restitution=restitution;
	fixture.shape = &box;

	body->CreateFixture(&fixture);

	int uasdf = world->GetBodyCount();
	printf("Bodies: %i\n",uasdf);
	return body;
}

b2Body* pObject::initCircle(GLfloat x, GLfloat y, b2BodyType objectType, GLfloat angle, GLfloat density, GLfloat friction, GLfloat restitution,GLuint sheet,GLuint sprite,pObject* data,GLuint materialT, void* xxx)
{	
	materialType=materialT;

	if(!(sheet > sheetList.size()-1))
	{
		spriteSheet = sheet;
		spriteID = sprite;
	}
	else
	{
		spriteSheet = 0;
		spriteID = 0;
	}
	

	RectVAO rv = sheetList[sheet].getRectVAO(sprite);
	halfSize.Set((rv.r.w/100.f)/2,(rv.r.h/100.f)/2);


	// Body Definition
	b2BodyDef bodyDefinition;
	bodyDefinition.type = objectType;
	bodyDefinition.position.Set(x-halfSize.x,y+halfSize.y);
	bodyDefinition.userData = xxx;//data;

	bodyDefinition.angle = (angle*2*b2_pi)/360;
	body=world->CreateBody(&bodyDefinition);

	// Fixture
	b2CircleShape circle;
	circle.m_radius=halfSize.x;

	b2FixtureDef fixture;
	fixture.density=density;
	fixture.friction=friction;
	fixture.restitution=restitution;
	fixture.shape = &circle;


	body->CreateFixture(&fixture);
	return body;
}


b2Body* pObject::initPolygon(GLfloat x, GLfloat y,b2BodyType objectType,GLfloat angle,GLfloat density,GLfloat friction,GLfloat restitution,GLuint sheet,GLuint sprite,std::vector<b2Vec2> vertices,pObject* data,GLuint materialT)
{
	materialType=materialT;

	if(!(sheet > sheetList.size()-1))
	{
		spriteSheet = sheet;
		spriteID = sprite;
	}
	else
	{
		spriteSheet = 0;
		spriteID = 0;
	}
	
	RectVAO rv = sheetList[sheet].getRectVAO(sprite);
	halfSize.Set((rv.r.w/100.f)/2,(rv.r.h/100.f)/2);
	

	// Body Definition
	b2BodyDef bodyDefinition;
	bodyDefinition.type = objectType;
	bodyDefinition.position.Set(x-halfSize.x,y+halfSize.y);
	bodyDefinition.userData = data;//(int*)objectID;

	bodyDefinition.angle = (angle*2*b2_pi)/360;
	body=world->CreateBody(&bodyDefinition);
	
	// Fixture

	GLuint verticesSize=vertices.size();

	b2Vec2 *vs=new b2Vec2[verticesSize];

	for(int i=0;i < verticesSize;i++)
	{
		vs[i] = vertices[i];
	}
	
	b2PolygonShape polygon;

	polygon.Set(vs,verticesSize);

	b2FixtureDef fixture;
	fixture.density=density;
	fixture.friction=friction;
	fixture.restitution=restitution;
	fixture.shape = &polygon;

	body->CreateFixture(&fixture);

	delete[] vs;
	return body;
}

void pObject::destroyBody()
{
	body->SetUserData(NULL);
	world->DestroyBody(body);
	body=NULL;
	printf("Destroyed!\n");
}

void pObject::render()
{

	//sprite.render((pos.x*100+halfSize.x*100),(pos.y*100-halfSize.y*100),1.f,1.f,(body->GetAngle()*360)/(2*b2_pi),-halfSize.x,halfSize.y); // Might need fixing with interpolation
	
	if(body != NULL && sheetList.size()-1 >= spriteSheet  )
	{	
		b2Vec2 pos=body->GetPosition();
		b2Vec2 velocity=body->GetLinearVelocity();
		
		sheetList[spriteSheet].renderSprite(spriteID,(pos.x+worldPos.x)*100,(pos.y+worldPos.y)*100,1.f,1.f,(body->GetAngle()*360)/(2*b2_pi));//-halfSize.x,halfSize.y);
	}
	//   		+halfSize.x		-halfSize.y
	//sprite->render((pos.x*100),(pos.y*100),1.f,1.f,(body->GetAngle()*360)/(2*b2_pi),halfSize.x,halfSize.y); // Might need fixing with interpolation
	
	
	//+(velocity.x*GameState::getInterpolation())/100   +(velocity.x*GameState::getInterpolation())/100            

	// Might need normalizing

	     //private  static var TWO_PI:Number = 2 * Math.PI;
  /**
   * Normalizes an angle to a relative angle.
   * The normalized angle will be in the range from -PI to PI, where PI
   * itself is not included.
   *
   * @param angle the angle to normalize
   * @return the normalized angle that will be in the range of [-PI,PI[
   */
	//public static function normalRelativeAngle( angle:Number) {
    //return ((angle %= TWO_PI) >= 0 ? (angle < Math.PI) ? angle : angle - TWO_PI : (angle >= -Math.PI) ? angle : angle + TWO_PI)* (180 / Math.PI);
/*  

}

void pObject::createDebris()
{

}

SpriteSheet2D* pObject::getSpriteSheet(int id)
{
	if(id < sheetList.size() && id > 0)		return &sheetList[id];
	else	return &sheetList[0];
}


GLuint pObject::getMaterialType()
{
	return materialType;
}

b2Vec2 pObject::getHalfSize()
{
	return halfSize;
}

bool pObject::collision()
{
	// need to check velocity

	if(collisionTimer.isRunning())
	{
		if(collisionTimer.hasPassedMS(1000))
		{
			//Audio::playSound("GameData/Sounds/shot.wav");

			collisionTimer.reset();
			return true;
		}
		return false;
	}
	else
	{
		collisionTimer.start();
		//Audio::playSound("GameData/Sounds/shot.wav");
		return true;
	}
}
*/