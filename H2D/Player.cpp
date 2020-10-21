#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::reInit()
{
	b2Vec2 pos = body->GetPosition();
	body->GetWorld()->DestroyBody(body);
	//ObjectList::getWorld(ObjectList::getPreviousFloor())->DestroyBody(*body);
	body = NULL;
	currentRenderSpriteSheet = 2;
	currentRenderSprite = 0;

	initObject(GAMEOBJECTTYPE_PERSON, COLLISIONOBJECTTYPE_PERSON, pos, 0.f, b2_dynamicBody, 1.f, 1.f, 0.f, false, this, NULL);
	body->SetGravityScale(0.f);
	//printf("EEEEEEEEEEE %i \n", *(int*)body->GetFixtureList()->GetUserData());
	worldPos = b2Vec2(0.f, 0.f);//100 * b2Vec2(-9.6f, -5.4f);	// worldPos = camera Pos
	targetPos = 100 * body->GetPosition();

	movingToPos = 100 * body->GetPosition();

	isMoving = false;
	printf("ELLLLLLL: %i \n", *(int*)body->GetFixtureList()->GetUserData());
}

void Player::loadPlayer(std::ifstream* stream)
{
	inventory.push_back(InventoryItem(std::make_shared<Weapon>(Weapon(150,WEAPONTYPE_PISTOL_SILENCED)), ITEMTYPE_WEAPON, 15,0));
	inventory.push_back(InventoryItem(std::make_shared<C4Item>(C4Item(50,0)), ITEMTYPE_PLACEABLE, 15, 1));
	inventory.push_back(InventoryItem(std::make_shared<StoneItem>(StoneItem(50)), ITEMTYPE_THROWABLE, 20, 2));
	selectedItem = 1;
	selectedItemType = ITEMTYPE_WEAPON;
}

void Player::update()
{
	GLfloat vX = 0.f, vY = 0.f;
	body->SetLinearVelocity(b2Vec2(vX, vY));
	

	GLfloat maxVel = 5.f;
	GLfloat maxVelD = sqrt(maxVel);

	b2Vec2 posChange = b2Vec2(0.f, 0.f);

	if (GameState::handler->isPressedS(GameHandler::KEY_S_UP))
	{
		//posChange.y += 50.f;
		body->ApplyLinearImpulse(b2Vec2(0.f, maxVel), body->GetWorldCenter(), true);
	}
	if (GameState::handler->isPressedS(GameHandler::KEY_S_DOWN))
	{
		//posChange.y -= 50.f;
		body->ApplyLinearImpulse(b2Vec2(0.f, -maxVel), body->GetWorldCenter(), true);
	}
	if (GameState::handler->isPressedS(GameHandler::KEY_S_LEFT))
	{
		//posChange.x -= 50.f;
		body->ApplyLinearImpulse(b2Vec2(-maxVel, 0.f), body->GetWorldCenter(), true);
	}
	if (GameState::handler->isPressedS(GameHandler::KEY_S_RIGHT))
	{
		//posChange.x += 50.f;
		body->ApplyLinearImpulse(b2Vec2(maxVel, 0.f), body->GetWorldCenter(), true);
	}


	b2Vec2 wp = /*posChange - b2Vec2(9.6f, 5.4f);*/  body->GetPosition() - b2Vec2(9.6f, 5.4f);
	wp *= -100.f;
	worldPos = wp;


	// Look at Mouse
	b2Vec2 pos = body->GetPosition();
	GLfloat an = atan2(-1.f * ((Engine::mouse_x - worldPos.x) - 100 * pos.x), ((Engine::mouse_y - worldPos.y) - 100 * pos.y));
	body->SetTransform(pos, an);

	// Get tile the player is looking at
	GLuint playerTile(getTile(getTilePos(pos),50));
	
	an += b2_pi;
	GLuint lookattile=599999;
	GLuint lookatDirection = DIRECTION_NONE;
	GLfloat oneFourthPi = b2_pi / 4.f;

	if (an < oneFourthPi || an > 7 * oneFourthPi)
	{
		lookatDirection = DIRECTION_DOWN;
		lookattile = playerTile - 50;
	}
	else if (an < 3 * oneFourthPi)
	{
		lookatDirection = DIRECTION_RIGHT;
		lookattile = playerTile + 1;
	}
	else if (an < 5 * oneFourthPi)
	{
		lookatDirection = DIRECTION_UP;
		lookattile = playerTile + 50;
	}
	else if (an < 7 * oneFourthPi)
	{
		lookatDirection = DIRECTION_LEFT;
		lookattile = playerTile - 1;
	}
	an -= b2_pi/2;

	//printf("Tile: %i || %i || %f \n", playerTile, lookattile, an);
	if (GameState::handler->isPressed(GameHandler::KEY_ITEM_1))	{ selectedItem = 0; selectedItemType = inventory[selectedItem].itemType; }
	if (GameState::handler->isPressed(GameHandler::KEY_ITEM_2))	{ selectedItem = 1; selectedItemType = inventory[selectedItem].itemType; }
	if (GameState::handler->isPressed(GameHandler::KEY_ITEM_3))	{ selectedItem = 2; selectedItemType = inventory[selectedItem].itemType; }
	//printf("Selitem %i \n",selectedItem);
	if (GameState::handler->isPressedB(GameHandler::B_FIRE_PRIMARY))// && selectedItemType == ITEMTYPE_WEAPON)
	{
		//c4.init(body->GetPosition());
		b2Vec2 clickPos(Engine::mouse_x - worldPos.x, Engine::mouse_y - worldPos.y);
		clickPos *= 1.f / 100.f; // Click position in pyhsics space

		/*if (b2DistanceSquared(clickPos, body->GetPosition()) < (0.64*0.64))
		{		printf("Here!!!");
			ObjectList::addObject(std::make_shared<C4>(C4(clickPos, 0.f, 0)));
		}*/

		bool lookatWall = ObjectList::getCurrentTileMap()->getTileObject(lookattile).isWall;
		switch (inventory[selectedItem].itemType)
		{
		case ITEMTYPE_PLACEABLE:
			printf("LAT: %i || CPT: %i \n", lookattile, getTile(getTilePos(clickPos), sizeX));
			if (lookattile == getTile(getTilePos(clickPos), sizeX))
			{
				if (lookatWall) inventory[selectedItem].item->placeItem(clickPos, playerTile, ObjectList::getCurrentTileMap()->getTileObject(lookattile).isWall, lookatDirection);
				else inventory[selectedItem].item->placeItem(clickPos, playerTile);
			}
			break;
		case ITEMTYPE_WEAPON:	inventory[selectedItem].item->useItem(0, clickPos);
			break;
		case ITEMTYPE_THROWABLE:
		{
								  	//inventory[selectedItem].item->throwItem(pos, body->GetAngle(), 10.f); 
								   lll.createSound(body->GetPosition(), 10.f, true);
		}
			break;
		}

	}
	inventory[selectedItem].item->update(body->GetPosition(), 100 * b2Vec2(0.f, 0.15f), an);

}

void Player::render()
{
	b2Vec2 pos = body->GetPosition();//printf("Pos: %f || %f \n", pos.x, pos.y);
	pos *= 100.f;
	pos += worldPos;

	sheetList[currentRenderSpriteSheet].renderSprite(currentRenderSprite, pos.x, pos.y, 1.f, 1.f, toAngle(body->GetAngle()));

	if (selectedItemType == ITEMTYPE_WEAPON)
	{
		inventory[selectedItem].item->render(pos);
	}


	
	//sheetList[1].renderSprite(0, renderPos.x + worldPos.x, renderPos.y + worldPos.y);
	//line.render(worldPos);
}

void Player::renderUI()
{
	// Render Hotbar
	inventory[0].item->renderIcon();
	inventory[1].item->renderIcon();
	inventory[2].item->renderIcon();
	lll.render();
}