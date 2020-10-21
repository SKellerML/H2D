//#pragma once
//
//#include "OpenGLH.h"
//#include "Gamestate.h"
//#include "Entity.h"
//
//#include <vector>
//
//enum DoorAlignment
//{
//	DOOR_TO_RIGHT,
//	DOOR_TO_LEFT,
//	DOOR_UP,
//	DOOR_DOWN
//};
//
//class Door : public Entity
//{
//public:
//	Door();
//	~Door();
//
//	void initDoor(b2Vec2 pos, GLuint alignment, bool open, int floor = -1);
//	virtual void update() override;
//	virtual void render() override;
//	virtual void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture) override	{ /*if (!isDestroyed) deleteObject( m_listID, m_floor, false); isDestroyed = true;*/ }
//
//private:
//	b2Vec2 pivot;
//	b2Vec2 openPos;
//	bool isOpen;
//	GLfloat closedAngle;
//};
//
