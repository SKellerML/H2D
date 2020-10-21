#pragma once

#include "Person.h"
#include "ObjectList.h"
#include "Entity.h"
#include "Weapon.h"


#include "SoundLogic.h"

#include <iostream>
#include <fstream>

struct InventoryItem
{
	InventoryItem() {}
	InventoryItem(std::shared_ptr<Item> _item, GLuint _itemType, GLuint _amount, GLuint _hotbarSlot) : item(_item), itemType(_itemType), amount(_amount), hotbarSlot(_hotbarSlot){ item->setIconPos(b2Vec2(832 + hotbarSlot * 64.f, 200.f)); }

	std::shared_ptr<Item> item;
	GLuint itemType;
	GLuint amount;
	GLuint hotbarSlot;
};

class Player : public Person
{
public:
	Player();
	~Player();

	void loadPlayer(std::ifstream* stream);

	virtual void reInit() override;

	virtual void update() override;
	virtual void render() override;
	virtual void renderUI();

	virtual void listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious) {}

	std::shared_ptr<Item> useItem();

private:
	std::vector<InventoryItem> inventory;
	GLuint selectedItem;
	GLuint selectedItemType;

	SoundLogic lll;
};

