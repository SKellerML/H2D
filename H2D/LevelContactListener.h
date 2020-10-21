#pragma once


#include <Box2D\Box2D.h>

class LevelContactListener : public b2ContactListener
{
public:

	LevelContactListener();
	~LevelContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact*contact);
	void PreSolve(b2Contact*contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact *contact, const b2ContactImpulse* impulse);
};

