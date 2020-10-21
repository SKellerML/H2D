#include "Person.h"

std::vector<TileObject>* Person::tileMap = NULL;
GLuint Person::sizeX;
GLuint Person::sizeY;
Person::Person()
{
	inRagdoll = false;
}


Person::~Person()
{
}

void Person::setTileMap(std::vector<TileObject>* vecTileMap, GLuint sX, GLuint sY)
{
	tileMap = vecTileMap;
	sizeX = sX;
	sizeY = sY;
}

void Person::init(b2Vec2 pos, GLfloat floor)
{
	currentRenderSpriteSheet = 2;
	currentRenderSprite = 0;
	//printf("Floor: %i \n", floor);
	initObject(GAMEOBJECTTYPE_PERSON, COLLISIONOBJECTTYPE_PERSON, pos, 0.f, b2_dynamicBody, 1.f, 1.f, 0.f, false, this, NULL, floor);
	body->SetGravityScale(0.f);

	worldPos = b2Vec2(0.f, 0.f);//100 * b2Vec2(-9.6f, -5.4f);	// worldPos = camera Pos
	targetPos = 100 * body->GetPosition();

	movingToPos = 100 * body->GetPosition();

	isMoving = false;
}

void Person::reInit()
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
}





void Person::update()
{

	//worldPos -= posChange;
	//worldPos = b2Vec2(0.f, 0.f);
	//worldPos = 
	if (!inRagdoll)
	{
		/*b2Vec2 pos = body->GetPosition();
		b2Vec2 clickPos(b2Vec2(Engine::mouse_x - BaseObject::getWorldPos().x, Engine::mouse_y - BaseObject::getWorldPos().y));
		if (GameState::handler->isPressedB(GameHandler::B_FIRE_PRIMARY))
		{
			moveTo(clickPos, true);
		}
		else
		{
			move();
		}*/
		move();
	}
	else if (inRagdoll)
	{
		if (ragdollTimer.hasPassed(ragdollTime))
		{
			inRagdoll = false;
		}
	}
		/*
	if (GameState::handler->isPressedB(GameHandler::B_FIRE_PRIMARY))
	{
		clickPos.Set(Engine::mouse_x - worldPos.x, Engine::mouse_y - worldPos.y);
		moveTo(clickPos, true);
	}
	move();
	*/

	// Move Person
	//if (isMoving && pathToMove.size() > 0)
	//{
	//	b2Vec2 objectTilePos(round(pos.x * 100 / 128.f), round(pos.y * 100 / 128.f));
	//	GLuint objectTileID = objectTilePos.y*sizeX + objectTilePos.x;
	//	if (targetTileID != objectTileID)
	//	{
	//		GLfloat verticalVal = pos.y * 100 - pathToMove[0].y;
	//		GLfloat horizontalVal = pos.x * 100 - pathToMove[0].x;

	//		GLfloat vertSpeed = maxVel;
	//		if (abs(verticalVal) < vertSpeed)	vertSpeed = verticalVal;

	//		GLfloat horSpeed = maxVel;
	//		if (abs(horizontalVal) < horSpeed)	horSpeed = horizontalVal;

	//		if (verticalVal < 0)
	//		{
	//			body->ApplyLinearImpulse(b2Vec2(0.f, vertSpeed), body->GetWorldCenter(), true);
	//		}
	//		else if (verticalVal > 0)
	//		{
	//			body->ApplyLinearImpulse(b2Vec2(0.f, -vertSpeed), body->GetWorldCenter(), true);
	//		}

	//		if (verticalVal > 0)
	//		{
	//			body->ApplyLinearImpulse(b2Vec2(horSpeed, 0.f), body->GetWorldCenter(), true);
	//		}
	//		else if (verticalVal < 0)
	//		{
	//			body->ApplyLinearImpulse(b2Vec2(-horSpeed, 0.f), body->GetWorldCenter(), true);
	//		}

	//		if (verticalVal == 0 && horizontalVal == 0)
	//		{
	//			pathToMove.erase(pathToMove.begin() + 1);
	//		}
	//		printf("Moving\n");
	//	}
	//}
}

void Person::moveTo(b2Vec2 pos_w, bool calculatePath)
{
	if (calculatePath)
	{
		b2Vec2 position = body->GetPosition();
		// convert to _tm variables
		targetTile.Set(round(pos_w.x / TILE_WIDTH), round(pos_w.y / TILE_WIDTH));
		targetPos.Set(targetTile.x * TILE_WIDTH, targetTile.y*TILE_WIDTH);
		targetTileID = getTile(targetPos, sizeX);


		b2Vec2 objectPos(position.x * 100, position.y * 100);
		b2Vec2 objectTilePos(round(position.x * 100 / TILE_WIDTH), round(position.y * 100 / TILE_WIDTH));
		GLuint objectTileID = objectTilePos.y*sizeX + objectTilePos.x;

		if (targetTileID != objectTileID)
		{
			//std::vector<b2Vec2> vvcas;

			movingToPos = TILE_WIDTH * objectTilePos;

			pathToMove.clear();
			if (findPath(&pathToMove, objectTilePos, targetTile, sizeX, sizeY))
			{
				std::vector<b2Vec2> lineVV;
				for (std::vector<b2Vec2>::iterator it = pathToMove.begin(); it != pathToMove.end(); ++it)
				{
					lineVV.push_back(b2Vec2(it->x * TILE_WIDTH, it->y * TILE_WIDTH));
				}
				line.initElement(&lineVV, 10, Color4f(1.f, 1.f, 1.f, 1.f));
			}
			//firstMove = true;
		}



		// Move to Pos
		//GLfloat vX = 0.f, vY = 0.f;
		//body->SetLinearVelocity(b2Vec2(vX, vY));


		//GLfloat maxVel = 2.f;
		//GLfloat maxVelD = sqrt(maxVel);
		//vX = 0.f;
		//vY = 0.f;
		//body->SetLinearVelocity(b2Vec2(vX, vY));


		
	}
}

void Person::move()
{
	// MOVE

	GLuint tT = 200;
	b2Vec2 position = body->GetPosition();

	b2Vec2 objectPos(position.x * 100, position.y * 100);
	b2Vec2 objectTilePos(round(position.x * 100 / TILE_WIDTH), round(position.y * 100 / TILE_WIDTH));
	GLuint objectTileID = objectTilePos.y*sizeX + objectTilePos.x;

	GLfloat maxVel = 4.f;
	GLfloat maxVelD = sqrt(maxVel);
	body->SetLinearVelocity(b2Vec2(0.f, 0.f));
	if (pathToMove.size() > 0)
	{
		// Generate path to the next node

		if (((abs(movingToPos.x - objectPos.x) < maxVel && abs(movingToPos.y - objectPos.y) < maxVel) && pathToMove.size() > 0))// if it is at the right position	// isMoving == false || 
		{
			b2Vec2 nodePos = objectTilePos;//pathToMove[0];
			int lastItem = -1;
			bool diagonalMovement = false;	// for Diagonal movement, might add it at some point, need difference variables to check if the next tile is on the same diagonal direction

			for (int i = 0; i < pathToMove.size(); i++)
			{
				if ((pathToMove[i].x == nodePos.x && pathToMove[i].y == nodePos.y))
				{
					movingToPos = TILE_WIDTH * pathToMove[i];
					lastItem = i;
				}
				else if (i == 0)
				{
					movingToPos = TILE_WIDTH * pathToMove[i];
				}
				else break;
			}

			if (lastItem > 0)	pathToMove.erase(pathToMove.begin(), pathToMove.begin() + lastItem + 1);
			else if (lastItem > -1)	pathToMove.erase(pathToMove.begin(), pathToMove.begin() + 1);
		}
	}

	if (abs(movingToPos.x - objectPos.x) > maxVel || abs(movingToPos.y - objectPos.y) > maxVel)
	{
		GLfloat verticalVal = objectPos.y - movingToPos.y;
		GLfloat horizontalVal = objectPos.x - movingToPos.x;

		//verticalVal *= 1/30;
		//horizontalVal *= 1/30;
		if (abs(verticalVal) != 0 && abs(horizontalVal) != 0)	maxVel = maxVelD;


		GLfloat vertSpeed = maxVel;
		if (abs(verticalVal) < vertSpeed)	vertSpeed = 0.8f * abs(verticalVal);

		GLfloat horSpeed = maxVel;
		if (abs(horizontalVal) < horSpeed)	horSpeed = 0.8f * abs(horizontalVal);



		if (verticalVal < 0)
		{
			body->ApplyLinearImpulse(b2Vec2(0.f, vertSpeed), body->GetWorldCenter(), true);
		}
		else if (verticalVal > 0)
		{
			body->ApplyLinearImpulse(b2Vec2(0.f, -vertSpeed), body->GetWorldCenter(), true);
		}

		if (horizontalVal < 0)
		{
			body->ApplyLinearImpulse(b2Vec2(horSpeed, 0.f), body->GetWorldCenter(), true);
		}
		else if (horizontalVal > 0)
		{
			body->ApplyLinearImpulse(b2Vec2(-horSpeed, 0.f), body->GetWorldCenter(), true);
		}
		isMoving = true;
	}
	else if ((movingToPos.x != objectPos.x) || abs(movingToPos.y != objectPos.y))
	{
		body->SetTransform(1.f / 100.f * movingToPos, body->GetAngle());
	}
	else
	{
		isMoving = false;
	}
}

void Person::render()
{
	//b2Vec2 pos = body->GetPosition();

	b2Vec2 pos = body->GetPosition();//printf("Pos: %f || %f \n", pos.x, pos.y);
	pos *= 100.f;
	pos += worldPos;
	
	sheetList[currentRenderSpriteSheet].renderSprite(currentRenderSprite, pos.x, pos.y,1.f,1.f,toAngle(body->GetAngle()));
	sheetList[1].renderSprite(0, renderPos.x + worldPos.x, renderPos.y + worldPos.y);
	line.render(worldPos);
}


bool Person::findPath(std::vector<b2Vec2>* pathVector, b2Vec2 startPos, b2Vec2 targetPos, GLuint sizeX, GLuint sizeY)
{
	printf("Finding path... %i || %i \n", targetPos.x, sizeX);
	if (targetPos.x >= sizeX || targetPos.y >= sizeY)		return false;
	if (targetPos.x < 0 || targetPos.y < 0)		return false;
	if (targetPos.x == startPos.x && targetPos.y == startPos.y) return false;


			// A* Algorithm, second try

			const GLuint OPEN_LIST = 1;
			const GLuint CLOSED_LIST = 2;

			std::map<GLuint, PathNode>		nodeList;					// List of all pathNodes
			std::map<GLuint, GLuint>		whichList;					// ID | List	// openList or ClosedList			// List
			std::multimap<GLuint, GLuint>	fList;		//Distance|ID			// List of all Distances	(F=G+H)


			bool noPathFound = false;	GLuint numberOfOpenListItems = 1; // End search for a path if the list did not change
			bool foundShortestPath = false;

			GLuint startTile = getTile(startPos, sizeX);

			GLuint targetTileID = getTile(targetPos, sizeX);
			GLint currentTileID = targetTileID;
			b2Vec2 currentTilePos = targetPos;


			if (!tileMap->at(targetTileID).isPassable())	return false;


			GLuint shortestDistanceValue = manhattanDistance(targetPos, startPos);
			GLuint nodeDistance = 0;
			//openList.insert(std::make_pair(shortestDistanceValue, PathNode(0, shortestDistanceValue, currentTileID, currentTileID);
			nodeList.insert(std::make_pair(currentTileID, PathNode(0, shortestDistanceValue, 0, currentTileID)));
			whichList.insert(std::make_pair(currentTileID, OPEN_LIST));

			GLuint shortestDistanceTile = currentTileID;
			//printf("Distance: %f || %f \n", targetTile.x, targetTile.y);
			//PathNode currentNode;
			// Draw Line
			std::vector<b2Vec2> lineCorner;
			lineCorner.push_back(TILE_WIDTH * b2Vec2(targetPos.x, targetPos.y));
			int vv = 0;

			bool addToOpenList = true;

			bool firstLoop = true;

			while (!foundShortestPath)
			{
				bool upFree = false, downFree = false, leftFree = false, rightFree = false;
				vv++;

				b2AABB aabb;
				aabb.lowerBound = 0.64f * getPos(currentTileID, sizeX) + b2Vec2(-0.2f,-0.2f);
				aabb.upperBound = 0.64f * getPos(currentTileID, sizeX) + b2Vec2(0.2f, 0.2f);
				objQuery qqq;
				world->QueryAABB(&qqq, aabb);

				if (!qqq.hit || firstLoop)
				{
					firstLoop = false;
					// Up Tile
					int tile = currentTileID + sizeX;
					if (((tile) < sizeX*sizeY) && tileMap->at(tile).isPassable())
					{
						upFree = true;

						if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
						{

								PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
									currentTileID, tile);
								nodeList.insert(std::make_pair(tile, currentNode));
								whichList.insert(std::make_pair(tile, OPEN_LIST));
								fList.insert(std::make_pair(currentNode.getNodeValue(), tile));

								++numberOfOpenListItems;

								if (currentNode.getNodeValue() <= shortestDistanceValue)
								{
									shortestDistanceValue = currentNode.getNodeValue();
									shortestDistanceTile = tile;
								}

						}
						else	// if it is on the open List
						{
							if (nodeList[tile].distanceToNode > nodeDistance + 10)
							{

								nodeList[tile].distanceToNode = nodeDistance + 10;
								nodeList[tile].previousNode = currentTileID;
							}
						}


					}
					// Down
					tile = currentTileID - sizeX;
					if (((tile) >= 0) && tileMap->at(tile).isPassable())
					{
						downFree = true;

						if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
						{
							PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() <= shortestDistanceValue)
							{

								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
						else	// if it is on the open List
						{
							if (nodeList[tile].distanceToNode > nodeDistance + 10)
							{
								nodeList[tile].distanceToNode = nodeDistance + 10;
								nodeList[tile].previousNode = currentTileID;
							}
						}
					}
					// Left
					tile = currentTileID - 1;
					if ( ( (currentTilePos.x - 1) >= 0 ) && tileMap->at(tile).isPassable()) // (tile) > 0
					{
						leftFree = true;
						if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
						{
							PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() <= shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
						else	// if it is on the open List
						{
							if (nodeList[tile].distanceToNode > nodeDistance + 10)
							{
								nodeList[tile].distanceToNode = nodeDistance + 10;
								nodeList[tile].previousNode = currentTileID;
							}
						}

					}
					// Right
					tile = currentTileID + 1;
					if (((currentTilePos.x + 1) < sizeX) && tileMap->at(tile).isPassable()) // Up
					{
						rightFree = true;

						if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
						{
							PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() <= shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
						else	// if it is on the open List  if (whichList[tile] == OPEN_LIST)
						{
							if (nodeList[tile].distanceToNode > nodeDistance + 10)
							{
								nodeList[tile].distanceToNode = nodeDistance + 10;
								nodeList[tile].previousNode = currentTileID;
							}
						}
					}

					// Diagonal Movement Start ---------------------------------------------------

					// UP LEFT
					if (upFree && leftFree)
					{
						tile = currentTileID + sizeX - 1;
						if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
						{
							PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() < shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
					}
					// UP RIGHT
					if (upFree && rightFree)
					{
						tile = currentTileID + sizeX + 1;
						if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
						{
							PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() < shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
					}
					// DOWN LEFT
					if (downFree && leftFree)
					{
						tile = currentTileID - sizeX - 1;
						if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
						{
							PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() < shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
					}
					// DOWN RIGHT
					if (downFree && rightFree)
					{
						tile = currentTileID - sizeX + 1;
						if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
						{
							PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
								currentTileID, tile);

							nodeList.insert(std::make_pair(tile, currentNode));
							whichList.insert(std::make_pair(tile, OPEN_LIST));
							fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
							++numberOfOpenListItems;

							if (currentNode.getNodeValue() < shortestDistanceValue)
							{
								shortestDistanceValue = currentNode.getNodeValue();
								shortestDistanceTile = tile;
							}
						}
					}
					// Diagonal Movement End   ---------------------------------------------------

				}

				//--numberOfOpenListItems;
				if (whichList[currentTileID] == OPEN_LIST) --numberOfOpenListItems;
				whichList[currentTileID] = CLOSED_LIST;

				// Found shortest path to all neighbouring plots, erase
				//renderPos.Set((shortestDistanceTile%sizeX) *TILE_WIDTH, floor(shortestDistanceTile / sizeY) *TILE_WIDTH);

				if (shortestDistanceTile != currentTileID)
				{

					//printf("CurrentTile: %i || %f || %f \n", shortestEstimateTile, renderPos.x, renderPos.y);
					//closeList.insert(shortestEstimateTile);
					//openList.erase(shortestEstimate);	

					currentTileID = shortestDistanceTile;
					currentTilePos.Set(currentTileID%sizeX, floor(currentTileID / sizeY));

					lineCorner.push_back(TILE_WIDTH * b2Vec2(currentTilePos.x, currentTilePos.y));
					if (currentTileID == startTile)	foundShortestPath = true;	// if target tile was found, end loop
					else if (vv > 1000)	foundShortestPath = true;

					nodeDistance = nodeList[currentTileID].distanceToNode;
					shortestDistanceValue = nodeList[currentTileID].getNodeValue();
				}
				else // Path not found, select node with lowest F
				{
					for (std::multimap<GLuint, GLuint>::iterator it = fList.begin(); it != fList.end();)
					{
						currentTileID = it->second;//fList.begin()->second.nodeID;
						if (whichList[currentTileID] == CLOSED_LIST)	++it;// it = fList.erase(it);
						else break;//++it;
					}
					//printf("ISD %i B: %i ", currentTile, closeList.find(currentTile) == closeList.end());
					currentTilePos = getPos(currentTileID, sizeX);

					nodeDistance = nodeList[currentTileID].distanceToNode;
					shortestDistanceValue = nodeList[currentTileID].getNodeValue();
				}

				//if (currentTileID == targetTileID)		addToOpenList = false;

				//currentEstimate = shortestEstimate;
				//printf("Size %i || %i \n", numberOfOpenListItems, vv);
				if ((numberOfOpenListItems <= 0 || vv > 1000) && !foundShortestPath)//))// )
				{
					noPathFound = true;
					foundShortestPath = true;
				}
				/*if (vv > 1000)
				{
				foundShortestPath = true;
				noPathFound = true;
				}*/
			}


			//GLfloat angle = atan2((pos.x - targetPos.x),(pos.y - targetPos.y)) + b2_pi;
			//body->ApplyLinearImpulse(2.f * b2Vec2(sinf(angle), cosf(angle)), body->GetWorldCenter(), true);
			//printf("ASDJLIASD %i \n", vv);
			if (!noPathFound)
			{
				// Get Final Path
				bool pathIncomplete = true;
				std::vector<b2Vec2> path;
				GLuint currentID = startTile;

				while (pathIncomplete)
				{
					currentID = nodeList[currentID].previousNode;
					pathVector->push_back(/*TILE_WIDTH * */getPos(currentID, sizeX));

					if (currentID == targetTileID)	pathIncomplete = false;
				}
				//line.initElement(&path, 10, Color4f(1.f, 1.f, 1.f, 1.f));
				return true;
			}
			else
			{

			}
		return false;
}

void Person::isHit(HitData* impactData, b2Vec2 collisionPoint, GLuint hitFixture)
{	
	//printf("Person hit hard! %f \n", impactData->impactImpulse.x);
	if (impactData->weaponType == GAMEOBJECTTYPE_PARTICLE)
	{
		if (impactData->impactImpulse.x > 1.f || impactData->impactImpulse.y > 1.f)
		{
			body->ApplyLinearImpulse(impactData->impactImpulse, collisionPoint, true);
			inRagdoll = true;
			ragdollTimer.start();
		}
	}
	else if (impactData->weaponType == GAMEOBJECTTYPE_BULLET)
	{
		printf("It's a bullet Floor: %i\n", currentFloor);
		addObject(OBJECTTYPE_DEAD_BODY, body->GetPosition(), body->GetAngle(), -1, -1);
		printf("ListID: %i \n", m_listID);
		deleteObject(m_listID, currentFloor, false);
	}
}
void Person::listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious)
{

}



// Civilian
//void Civilian::update() {}
//void Civilian::render() {}
void Civilian::listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious)
{
	printf("CIVILIAN HEARD IT (OR NOT) \n");
	moveTo(100 * (body->GetPosition()+b2Vec2(0.f,0.64f*10.f)), true);
}

// Guard
//void Guard::update() {}
//void Guard::render() {}
void Guard::listenSound(b2Vec2 soundPosition, GLfloat volume, GLfloat distance, bool isSuspicious)
{
	printf("GUARD HEARD IT (OR NOT) \n");
	moveTo(100 * soundPosition, true);
}