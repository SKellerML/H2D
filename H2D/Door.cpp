//#include "Door.h"
//
//
//Door::Door()
//{
//	isOpen = false;
//}
//
//
//Door::~Door()
//{
//}
//
//void Door::initDoor(b2Vec2 pos, GLuint alignment, bool open, int floor)
//{
//	GLuint direction = alignment;
//	isOpen = open;
//
//	currentRenderSprite = 2;
//	currentRenderSpriteSheet = sheetEntityID;
//
//	m_pos = pos;
//	std::vector<b2Vec2> vs;
//	/*vs.push_back(b2Vec2(-.1f, -.1f));
//	vs.push_back(b2Vec2(.54f, -.1f));
//	vs.push_back(b2Vec2(.54f, .1f));
//	vs.push_back(b2Vec2(-.1f, .1f));*/
//
//	initObject(GAMEOBJECTTYPE_OBJECT, COLLISIONOBJECTTYPE_WALL, pos, 0.f, b2_staticBody, 1.f, 1.f, .0f, true, NULL, NULL, floor);
//	// = body->GetPosition();
//
//
//	closedAngle = 0.f;
//	switch (direction)
//	{
//	case 	DOOR_TO_RIGHT:
//		closedAngle = 90.f;
//		openPos = m_pos + b2Vec2(.27f, .27f);
//		body->SetTransform(m_pos, toRad(closedAngle));
//		break;
//	case 		DOOR_TO_LEFT:
//		closedAngle = 90.f;
//		openPos = m_pos + b2Vec2(-.27f, .27f);
//		body->SetTransform(m_pos, toRad(closedAngle));
//		break;
//	case 		DOOR_UP:
//		openPos = m_pos + b2Vec2(-.27f, .27f);
//		break;
//	default://case 		DOOR_DOWN:
//		openPos = m_pos + b2Vec2(-.27f, -.27f);
//		break;
//	}
//
//	if (!isOpen)
//	{
//		body->SetTransform(openPos, toRad((closedAngle + 90.f)));
//		printf("Angle: %f || %f \n", toAngle(toRad(closedAngle + 90.f)), closedAngle + 90.f);
//		isOpen = true;
//	}
//	else
//	{
//		body->SetTransform(m_pos, toRad(closedAngle));
//		printf("Angle: %f \n", toAngle(body->GetAngle()));
//		isOpen = false;
//	}
//}
//
//void Door::update()
//{
//	// DEBUG ONLY
//	if (GameState::handler->isPressed(GameHandler::KEY_USE))
//	{
//		if (!isOpen)
//		{
//			body->SetTransform(openPos, toRad((closedAngle + 90.f)));
//			printf("Angle: %f || %f \n", toAngle(toRad(closedAngle + 90.f)), closedAngle + 90.f);
//			isOpen = true;
//		}
//		else
//		{
//			body->SetTransform(m_pos, toRad(closedAngle));
//			printf("Angle: %f \n", toAngle(body->GetAngle()));
//			isOpen = false;
//		}
//	}	
//}
//
//void Door::render()
//{
//	b2Vec2 rpos = 100 * body->GetPosition();// -b2Vec2(.22f, 0.f));
//	sheetEntity->renderSprite(currentRenderSprite, worldPos.x + rpos.x, worldPos.y + rpos.y, 1.f, 1.f, toAngle(body->GetAngle()));
//}