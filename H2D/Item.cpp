#include "Item.h"

GLuint Item::sheetID;
SpriteSheet2D* Item::sheet;

Item::Item(GLuint amount, GLuint id)
{
	init(amount, id);
}


Item::~Item()
{
}

void Item::loadItems()
{
	sheetID = BaseObject::addSheet(&std::string("items.png"));
	sheet = BaseObject::getSpriteSheet(sheetID);

	GLuint spritesInLine = sheet->getImgHeight() / TILE_WIDTH;

	for (int y = 0; y < spritesInLine; y++)
	{
		for (int x = 0; x < spritesInLine; x++)
		{
			sheet->addClipSprite(Rect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
			//printf("III: %i \n", y*x);
		}
	}
}

void Item::init(GLuint amount, GLuint id)
{
	itemID = id;
	m_amount = amount;
	GLfloat hh=0.32f, hw=0.32f;
	amountText.init(std::to_string(amount), 20, 1.f);
	//currentRenderSprite = id;
	//currentRenderSpriteSheet = sheetID;
	//initObject(GAMEOBJECTTYPE_OBJECT,COLLISIONOBJECTTYPE_FLOOR,iconPos, 0.f, b2_dynamicBody, 1.f, 1.f, 0.f, true, NULL, NULL);
	/*
	b2BodyDef bdef;
	bdef.position = pos;
	bdef.type = b2_dynamicBody;
	body = world->CreateBody(&bdef);

	b2PolygonShape shape;
	shape.SetAsBox(hh,hw);

	body->CreateFixture(&shape, 1.f);
	body->SetLinearDamping(10.f);
	std::vector<b2Vec2> vsV;
	hh *= 100;
	hw *= 100;
	vsV.push_back(b2Vec2(-hw, -hh));
	vsV.push_back(b2Vec2(hw, -hh));
	vsV.push_back(b2Vec2(hw, hh));
	vsV.push_back(b2Vec2(-hw, hh));
	polpol.initElement(&vsV, Color4f(1.f, 1.f, 0.f, 1.f));*/
}


bool Item::update(b2Vec2 pos, b2Vec2 offs, GLfloat ang)
{
	return true;
}

void Item::render(b2Vec2 renderPos)
{
	//sheet->renderSprite(0,100 * body->GetPosition().x + worldPos.x, 100 * body->GetPosition().y + worldPos.y, 1.f, 1.f, toAngle(body->GetAngle()));
	//polpol.render(100 * body->GetPosition() + worldPos,toAngle(body->GetAngle()));
}

void Item::renderIcon()
{
	sheet->renderSprite(itemID, m_IconPos.x, m_IconPos.y);
	amountText.render(m_IconPos.x+18.f, m_IconPos.y-18.f);
	// render amount
}

void C4Item::useItem(GLuint useType, b2Vec2 position)
{
	if (!m_amount)	return;
	
	ObjectList::addObject(OBJECTTYPE_C4, position, 0.f, -1, -1);
	amountText.updateText(std::to_string(--m_amount));
}

void C4Item::placeItem(b2Vec2 position, GLuint tile, bool onWall, GLuint direction)
{
	//if (!m_amount)	return;

	//
	//if (onWall)
	//{
	//	GLuint sizeX = ObjectList::getSizeX();
	//	position = 0.64f * getPos(tile, sizeX);
	//	GLfloat angle = 0.f;
	//	GLuint wallTile=tile;
	//	switch (direction)
	//	{
	//	case DIRECTION_UP:		position += b2Vec2(0.f, .20f/*7*/);
	//		wallTile += sizeX;
	//		break;
	//	case DIRECTION_LEFT:	position += b2Vec2(-.20f, 0.f); angle = 90.f;
	//		wallTile -= 1;
	//		break;
	//	case DIRECTION_DOWN:	position += b2Vec2(0.f, -.20f); angle = 180.f;
	//		wallTile -= sizeX;
	//		break;
	//	case DIRECTION_RIGHT:	position += b2Vec2(.20f, 0.f); angle = 270.f;
	//		wallTile += 1;
	//		break;
	//	default:
	//		break;
	//	}
	//	C4 obj;
	//	obj.initOnWall(position, angle, 0, wallTile, -1);
	//	std::shared_ptr<C4> cc = std::make_shared<C4>(obj);
	//	ObjectList::addObject(cc, -1, true);
	//	amountText.updateText(std::to_string(--m_amount));
	//}
	//else
	//{
	//	ObjectList::addObject(OBJECTTYPE_C4, position, 0.f, -1, -1);
	//	amountText.updateText(std::to_string(--m_amount));
	//}
}

// Stone

void StoneItem::useItem(GLuint useType, b2Vec2 position)
{
	if (!m_amount)	return;

	ObjectList::addObject(OBJECTTYPE_C4, position, 0.f, -1, -1);
	amountText.updateText(std::to_string(--m_amount));
}

void StoneItem::placeItem(b2Vec2 position, GLuint tile, bool onWall, GLuint direction)
{
	if (!m_amount)	return;


	//if (onWall)
	//{
	//	GLuint sizeX = ObjectList::getSizeX();
	//	position = 0.64f * getPos(tile, sizeX);
	//	GLfloat angle = 0.f;
	//	GLuint wallTile = tile;
	//	switch (direction)
	//	{
	//	case DIRECTION_UP:		position += b2Vec2(0.f, .20f/*7*/);
	//		wallTile += sizeX;
	//		break;
	//	case DIRECTION_LEFT:	position += b2Vec2(-.20f, 0.f); angle = 90.f;
	//		wallTile -= 1;
	//		break;
	//	case DIRECTION_DOWN:	position += b2Vec2(0.f, -.20f); angle = 180.f;
	//		wallTile -= sizeX;
	//		break;
	//	case DIRECTION_RIGHT:	position += b2Vec2(.20f, 0.f); angle = 270.f;
	//		wallTile += 1;
	//		break;
	//	default:
	//		break;
	//	}
	//	C4 obj;
	//	obj.initOnWall(position, angle, 0, wallTile, -1);
	//	std::shared_ptr<C4> cc = std::make_shared<C4>(obj);
	//	ObjectList::addObject(cc, -1, true);
	//	amountText.updateText(std::to_string(--m_amount));
	//}
	//else
	//{
	//	ObjectList::addObject(OBJECTTYPE_C4, position, 0.f, -1, -1);
	//	amountText.updateText(std::to_string(--m_amount));
	//}
}

void StoneItem::throwItem(b2Vec2 position, GLfloat angle, GLfloat throwImpulse)
{
	/*if (m_amount <= 0)	return;
	amountText.updateText(std::to_string(--m_amount));
	Stone st(position + .5f * b2Vec2(cos(angle), sin(angle)), angle, 0);
	st.body->ApplyLinearImpulse(throwImpulse * b2Vec2(cos(angle), sin(angle)), st.body->GetWorldCenter(), true);
	ObjectList::addObject(std::make_shared<Stone>(st), -1, false);
	printf("Trhown %i \n");*/
}