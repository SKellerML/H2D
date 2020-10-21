#pragma once


#include "BaseObject.h"
#include "Element2D.h"
#include "Entity.h"
#include "FontObject.h"
#include "ObjectList.h"
#include "OpenGLH.h"
#include "TileMap.h"
#include "TileObject.h"


enum ItemID
{
	ITEM_C4_CHARGE,
	ITEM_PISTOL_SILENCED,
	ITEM_SMG,
	ITEM_STONE,
};


enum ItemType
{
	ITEMTYPE_WEAPON,
	ITEMTYPE_PLACEABLE,
	ITEMTYPE_THROWABLE,
};

class Item
{
public:
	Item() {}
	Item(GLuint amount, GLuint id);
	~Item();

	// Create Wall from starpos to targetPos as squares, but pyhsics coordinates
	virtual void init(GLuint amount, GLuint id);
	
	virtual void useItem(GLuint useType, b2Vec2 position) {}
	virtual void placeItem(b2Vec2 position, GLuint tile, bool onWall = false, GLuint direction = DIRECTION_NONE) {}
	virtual void throwItem(b2Vec2 position, GLfloat angle, GLfloat throwImpulse) {}
	virtual bool update(b2Vec2 pos, b2Vec2 offs, GLfloat ang);
	virtual void render(b2Vec2 renderPos);
	virtual void renderIcon();

	void setIconPos(b2Vec2 iconPos) { m_IconPos = iconPos; }

	//virtual void isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture)	{}

	//void destroyWall()	{ world->DestroyBody(body); }

	static void loadItems();

protected:
	ElementPolygon polpol;

	GLuint itemID;
	b2Vec2 m_IconPos;
	FontObject amountText;
	GLuint m_amount;
	static GLuint sheetID;
	static SpriteSheet2D* sheet;
};

class C4Item : public Item
{
public:
	C4Item(){}
	C4Item(GLuint amount, GLuint weaponID){ init(amount, ITEM_C4_CHARGE); }
	~C4Item(){}

	//void initWeapon(GLuint ammo, GLuint weaponID);
	void useItem(GLuint useType, b2Vec2 position);
	virtual void placeItem(b2Vec2 position, GLuint tile, bool onWall = false, GLuint direction = DIRECTION_NONE) override;
	bool update(b2Vec2 pos, b2Vec2 offs, GLfloat ang) override { return true;}
	//void render(b2Vec2 renderPos);

private:
	b2Vec2 position;
	b2Vec2 offset;
	GLfloat angle;
};

class StoneItem : public Item
{
public:
	StoneItem(){}
	StoneItem(GLuint amount){ init(amount, ITEM_STONE); }
	~StoneItem(){}

	//void initWeapon(GLuint ammo, GLuint weaponID);
	void useItem(GLuint useType, b2Vec2 position);
	virtual void placeItem(b2Vec2 position, GLuint tile, bool onWall = false, GLuint direction = DIRECTION_NONE) override;
	virtual void throwItem(b2Vec2 position, GLfloat angle, GLfloat throwImpulse) override;
	bool update(b2Vec2 pos, b2Vec2 offs, GLfloat ang) override { return true; }
	//void render(b2Vec2 renderPos);

private:
	b2Vec2 position;
	b2Vec2 offset;
	GLfloat angle;
};