#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::Weapon(GLuint ammo, GLuint weaponID)
{
	initWeapon(ammo, weaponID);
}

Weapon::~Weapon()
{
}

void Weapon::initWeapon(GLuint ammo, GLuint weaponID)
{
	itemID = weaponID;
	this->ammo = ammo;
	amountText.init(std::to_string(ammo), 20, 1.f);
}
void Weapon::useItem(GLuint useType, b2Vec2 position)
{
	if (ammo > 0)
	{
		LaserRayCastCallback cb;
		BaseObject::getWorld()->RayCast(&cb, m_position, m_position + 10 * b2Vec2(cos(angle), sin(angle)));
		BaseObject* obj = cb.getHitObject();
		if (obj != NULL)
		{

			obj->isHit(&HitData(GAMEOBJECTTYPE_BULLET, b2Vec2(1.f, 1.f), 1.f), cb.getImpactPoint(), cb.getHitFixtureUserData()); // Hit object has to render the particle effect?
		}

		amountText.updateText(std::to_string(--ammo));

	}
}


bool Weapon::update(b2Vec2 pos, b2Vec2 offs, GLfloat ang)
{
	m_position = pos;
	offset = offs;
	angle = ang;

	return true;
}
void Weapon::render(b2Vec2 renderPos)
{
	renderPos += offset;
	sheet->renderSprite(2,renderPos.x, renderPos.y,1.f,1.f,toAngle(angle)-135.f,offset.x,offset.y);
}