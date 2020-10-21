#pragma once

#include "BaseObject.h"
#include "Item.h"
#include "OpenGLH.h"
#include "RayCastCallbacks.h"

enum WeaponType
{
	WEAPONTYPE_PISTOL_SILENCED = ITEM_PISTOL_SILENCED,
	WEAPONTYPE_SMG,
};

class Weapon : public Item
{
public:
	Weapon();
	Weapon(GLuint ammo, GLuint weaponID);
	~Weapon();

	void initWeapon(GLuint ammo, GLuint weaponID);
	void useItem(GLuint useType, b2Vec2 position);
	bool update(b2Vec2 pos, b2Vec2 offs, GLfloat ang) override;
	void render(b2Vec2 renderPos);

private:
	b2Vec2 m_position;
	b2Vec2 offset;
	GLfloat angle;

	GLuint ammo;
};

