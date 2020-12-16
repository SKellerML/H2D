#include "SoundLogic.h"


SoundLogic::SoundLogic()
{
}


SoundLogic::~SoundLogic()
{
}

void SoundLogic::createSound(b2Vec2 position, GLfloat volume, bool suspicious)
{
	// Get all objects in the Area and add them to the listener List if they can hear it
	SoundLogicListenerCallback* cb = new SoundLogicListenerCallback();
	b2AABB aabb;
	aabb.upperBound.Set(position.x + volume, position.y + volume);
	aabb.lowerBound.Set(position.x - volume, position.y - volume);
	world->QueryAABB(cb, aabb);

	// Check all items in the Listener List for direct A* distance and remove if not inside	
	if (cb->fixtureVector.size() > 0)
	{
		printf("Size;;; %i \n", cb->fixtureVector.size());
		for (int i = cb->fixtureVector.size() - 1; i; --i)
		{
			BaseObject* bo = (BaseObject*)cb->fixtureVector[i]->GetBody()->GetUserData().pointer;

			//BaseObject* bo2 = (BaseObject*)cb->fixtureVector[1]->GetBody()->GetUserData();
			std::vector<b2Vec2> vv;
			bo->listenSound(position, volume, 1.f, suspicious);

			//	startPos = b2Vec2(round(startPos.x * 100 / TILE_WIDTH), round(startPos.y * 100 / TILE_WIDTH));	// These Values are set in Person before getting sent to this Function
			//	targetPos = b2Vec2(round(targetPos.x * 100 / TILE_WIDTH), round(targetPos.y * 100 / TILE_WIDTH)); // These Values are set in Person before getting sent to this Function
			printf("EAAF DIST: %i \n", pathDistance(10, b2Vec2(round(position.x * 100 / TILE_WIDTH), round(position.y * 100 / TILE_WIDTH)), b2Vec2(round(bo->body->GetPosition().x * 100 / TILE_WIDTH), round(bo->body->GetPosition().y * 100 / TILE_WIDTH)), sizeX, sizeY, &vv));//position, bo2->body->GetPosition(), volume * 10 * 4, Person::sizeX, Person::sizeY,&vv));

			std::vector<b2Vec2> lineVV;
			for (std::vector<b2Vec2>::iterator it = vv.begin(); it != vv.end(); ++it)
			{
				lineVV.push_back(b2Vec2(it->x * TILE_WIDTH, it->y * TILE_WIDTH));
			}
			//printf("EAAF SIZE : %i \n", lineVV.size());
			//lineVV.clear();
			//lineVV.push_back(b2Vec2(0.f, 0.f));
			//lineVV.push_back(b2Vec2(1000.f, 1000.f));
			//if (lineVV.size() > 2) lines.initElement(&lineVV, 15.f, Color4f(1.f, 1.f, 1.f, 1.f));
		}
	}


	// call listener function for the object in the Area

}


//GLint SoundLogic::pathDistance(b2Vec2 startPos, b2Vec2 targetPos,GLuint maxDistance ,GLuint sizeX, GLuint sizeY, std::vector<b2Vec2>* pathVectorDebug)
//{
//	printf("Finding path... %f || %i \n", targetPos.x, sizeX);
//	if (targetPos.x >= sizeX || targetPos.y >= sizeY)		return false;
//	if (targetPos.x < 0 || targetPos.y < 0)		return false;
//	if (targetPos.x == startPos.x && targetPos.y == startPos.y) return false;
//
//
//	// A* Algorithm, second try
//
//	const GLuint OPEN_LIST = 1;
//	const GLuint CLOSED_LIST = 2;
//
//	std::map<GLuint, PathNode>		nodeList;					// List of all pathNodes
//	std::map<GLuint, GLuint>		whichList;					// ID | List	// openList or ClosedList			// List
//	std::multimap<GLuint, GLuint>	fList;		//Distance|ID			// List of all Distances	(F=G+H)
//
//
//	bool noPathFound = false;	GLuint numberOfOpenListItems = 1; // End search for a path if the list did not change
//	bool foundShortestPath = false;
//
//	GLuint startTile = getTile(b2Vec2(round(startPos.x * 100 / TILE_WIDTH), round(startPos.y * 100 / TILE_WIDTH)), sizeX);
//
//	GLuint targetTileID = getTile(b2Vec2(round(targetPos.x * 100 / TILE_WIDTH), round(targetPos.y * 100 / TILE_WIDTH)), sizeX);
//	GLint currentTileID = startTile;
//	b2Vec2 currentTilePos = b2Vec2(round(startPos.x * 100 / TILE_WIDTH), round(startPos.y * 100 / TILE_WIDTH));
//
//	startPos = b2Vec2(round(startPos.x * 100 / TILE_WIDTH), round(startPos.y * 100 / TILE_WIDTH));	// These Values are set in Person before getting sent to this Function
//	targetPos = b2Vec2(round(targetPos.x * 100 / TILE_WIDTH), round(targetPos.y * 100 / TILE_WIDTH)); // These Values are set in Person before getting sent to this Function
//
//	if (!tileMap->at(targetTileID).isPassable())	return false;
//
//
//	GLuint shortestDistanceValue = manhattanDistance(targetPos, startPos);
//	GLuint nodeDistance = 0;
//	//openList.insert(std::make_pair(shortestDistanceValue, PathNode(0, shortestDistanceValue, currentTileID, currentTileID);
//	nodeList.insert(std::make_pair(currentTileID, PathNode(0, shortestDistanceValue, 0, currentTileID)));
//	whichList.insert(std::make_pair(currentTileID, OPEN_LIST));
//
//	GLuint shortestDistanceTile = currentTileID;
//	//printf("Distance: %f || %f \n", targetTile.x, targetTile.y);
//	//PathNode currentNode;
//	// Draw Line
//	std::vector<b2Vec2> lineCorner;
//	lineCorner.push_back(TILE_WIDTH * b2Vec2(targetPos.x, targetPos.y));
//	int vv = 0;
//
//	bool addToOpenList = true;
//
//	bool firstLoop = true;
//
//	while (!foundShortestPath)
//	{
//		bool upFree = false, downFree = false, leftFree = false, rightFree = false;
//		vv++;
//
//		//b2AABB aabb;
//		//aabb.lowerBound = 0.64f * getPos(currentTileID, sizeX) + b2Vec2(-0.2f, -0.2f);
//		//aabb.upperBound = 0.64f * getPos(currentTileID, sizeX) + b2Vec2(0.2f, 0.2f);
//		//objQuery qqq;
//		//world->QueryAABB(&qqq, aabb);
//
//		if (true)//!qqq.hit || firstLoop)
//		{
//			firstLoop = false;
//			// Up Tile
//			int tile = currentTileID + sizeX;
//			if (((tile) < sizeX*sizeY) && tileMap->at(tile).isPassable())
//			{
//				upFree = true;
//
//				if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
//				{
//
//					PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//
//				}
//				else	// if it is on the open List
//				{
//					if (nodeList[tile].distanceToNode > nodeDistance + 10)
//					{
//
//						nodeList[tile].distanceToNode = nodeDistance + 10;
//						nodeList[tile].previousNode = currentTileID;
//					}
//				}
//
//
//			}
//			// Down
//			tile = currentTileID - sizeX;
//			if (((tile) >= 0) && tileMap->at(tile).isPassable())
//			{
//				downFree = true;
//
//				if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
//				{
//					PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//				else	// if it is on the open List
//				{
//					if (nodeList[tile].distanceToNode > nodeDistance + 10)
//					{
//						nodeList[tile].distanceToNode = nodeDistance + 10;
//						nodeList[tile].previousNode = currentTileID;
//					}
//				}
//			}
//			// Left
//			tile = currentTileID - 1;
//			if (((currentTilePos.x - 1) >= 0) && tileMap->at(tile).isPassable()) // (tile) > 0
//			{
//				leftFree = true;
//				if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
//				{
//					PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//				else	// if it is on the open List
//				{
//					if (nodeList[tile].distanceToNode > nodeDistance + 10)
//					{
//						nodeList[tile].distanceToNode = nodeDistance + 10;
//						nodeList[tile].previousNode = currentTileID;
//					}
//				}
//
//			}
//			// Right
//			tile = currentTileID + 1;
//			if (((currentTilePos.x + 1) < sizeX) && tileMap->at(tile).isPassable()) // Up
//			{
//				rightFree = true;
//
//				if (whichList.find(tile) == whichList.end() && addToOpenList)	// if it is on no List
//				{
//					PathNode currentNode(nodeDistance + 10, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//				else	// if it is on the open List  if (whichList[tile] == OPEN_LIST)
//				{
//					if (nodeList[tile].distanceToNode > nodeDistance + 10)
//					{
//						nodeList[tile].distanceToNode = nodeDistance + 10;
//						nodeList[tile].previousNode = currentTileID;
//					}
//				}
//			}
//
//			// Diagonal Movement Start ---------------------------------------------------
//
//			// UP LEFT
//			if (upFree && leftFree)
//			{
//				tile = currentTileID + sizeX - 1;
//				if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
//				{
//					PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//			}
//			// UP RIGHT
//			if (upFree && rightFree)
//			{
//				tile = currentTileID + sizeX + 1;
//				if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
//				{
//					PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y + 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//			}
//			// DOWN LEFT
//			if (downFree && leftFree)
//			{
//				tile = currentTileID - sizeX - 1;
//				if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
//				{
//					PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x - 1, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//			}
//			// DOWN RIGHT
//			if (downFree && rightFree)
//			{
//				tile = currentTileID - sizeX + 1;
//				if (((tile) >= 0) && tileMap->at(tile).isPassable() && whichList.find(tile) == whichList.end())
//				{
//					PathNode currentNode(nodeDistance + 14, manhattanDistance(startPos, b2Vec2(currentTilePos.x + 1, currentTilePos.y - 1)),	//openList[currentTile].distance + b2DistanceSquared(b2Vec2(currentX, currentY + 1)
//						currentTileID, tile);
//
//					nodeList.insert(std::make_pair(tile, currentNode));
//					whichList.insert(std::make_pair(tile, OPEN_LIST));
//					fList.insert(std::make_pair(currentNode.getNodeValue(), tile));
//					++numberOfOpenListItems;
//
//					if (currentNode.getNodeValue() <= shortestDistanceValue)
//					{
//						shortestDistanceValue = currentNode.getNodeValue();
//						shortestDistanceTile = tile;
//					}
//				}
//			}
//			// Diagonal Movement End   ---------------------------------------------------
//
//		}
//
//		//--numberOfOpenListItems;
//		if (whichList[currentTileID] == OPEN_LIST) --numberOfOpenListItems;
//		whichList[currentTileID] = CLOSED_LIST;
//
//		// Found shortest path to all neighbouring plots, erase
//		//renderPos.Set((shortestDistanceTile%sizeX) *TILE_WIDTH, floor(shortestDistanceTile / sizeY) *TILE_WIDTH);
//		printf("Tiles: %i \n", shortestDistanceValue);
//		if (shortestDistanceTile != currentTileID)
//		{
//
//			//printf("CurrentTile: %i || %f || %f \n", shortestEstimateTile, renderPos.x, renderPos.y);
//			//closeList.insert(shortestEstimateTile);
//			//openList.erase(shortestEstimate);	
//
//			currentTileID = shortestDistanceTile;
//			currentTilePos.Set(currentTileID%sizeX, floor(currentTileID / sizeY));
//
//			lineCorner.push_back(TILE_WIDTH * b2Vec2(currentTilePos.x, currentTilePos.y));
//			if (currentTileID == startTile)	 foundShortestPath = true; // return nodeList[currentTileID].getNodeValue();	// if target tile was found, end loop
//			else if (vv > 1000)	{ foundShortestPath = true; noPathFound = true; }
//
//			nodeDistance = nodeList[currentTileID].distanceToNode;
//			shortestDistanceValue = nodeList[currentTileID].getNodeValue();
//
//		}
//		else // Path not found, select node with lowest F
//		{
//			
//			for (std::multimap<GLuint, GLuint>::iterator it = fList.begin(); it != fList.end();)
//			{
//				currentTileID = it->second;//fList.begin()->second.nodeID;
//				if (whichList[currentTileID] == CLOSED_LIST)	++it;// it = fList.erase(it);
//				else break;//++it;
//			}
//			
//			//printf("ISD %i B: %i ", currentTile, closeList.find(currentTile) == closeList.end());
//			currentTilePos = getPos(currentTileID, sizeX);
//
//			nodeDistance = nodeList[currentTileID].distanceToNode;
//			shortestDistanceValue = nodeList[currentTileID].getNodeValue();
//		}
//
//		//if (currentTileID == targetTileID)		addToOpenList = false;
//		if (shortestDistanceValue >= maxDistance)
//		{
//			return -1;
//			noPathFound = true;
//			foundShortestPath = true;
//		}
//
//
//		//currentEstimate = shortestEstimate;
//		//printf("Size %i || %i \n", numberOfOpenListItems, vv);
//		if ((numberOfOpenListItems <= 0 || vv > 1000) && !foundShortestPath)//))// )
//		{
//			noPathFound = true;
//			foundShortestPath = true;
//		}
//
//
//		/*if (vv > 1000)
//		{
//		foundShortestPath = true;
//		noPathFound = true;
//		}*/
//	}
//
//
//	//GLfloat angle = atan2((pos.x - targetPos.x),(pos.y - targetPos.y)) + b2_pi;
//	//body->ApplyLinearImpulse(2.f * b2Vec2(sinf(angle), cosf(angle)), body->GetWorldCenter(), true);
//	//printf("ASDJLIASD %i \n", vv);
//	if (!noPathFound)
//	{
//		// Get Final Path
//		bool pathIncomplete = true;
//		std::vector<b2Vec2> path;
//		GLuint currentID = startTile;
//
//		while (pathIncomplete)
//		{
//			currentID = nodeList[currentID].previousNode;
//			pathVectorDebug->push_back(/*TILE_WIDTH * */getPos(currentID, sizeX));
//
//			if (currentID == targetTileID)	pathIncomplete = false;
//		}
//		//line.initElement(&path, 10, Color4f(1.f, 1.f, 1.f, 1.f));
//		return shortestDistanceValue;
//	}
//	else
//	{
//
//	}
//	return -1;
//}

GLfloat SoundLogic::pathDistance(GLuint maxDistance, b2Vec2 startPos, b2Vec2 targetPos, GLuint sizeX, GLuint sizeY, std::vector<b2Vec2>* pathVector)
{
	printf("Calculating Distance...\n");
	if (targetPos.x >= sizeX || targetPos.y >= sizeY)		return false;
	if (targetPos.x < 0 || targetPos.y < 0)		return false;
	if (targetPos.x == startPos.x && targetPos.y == startPos.y) return false;

	maxDistance *= 10;

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
		aabb.lowerBound = 0.64f * getPos(currentTileID, sizeX) + b2Vec2(-0.2f, -0.2f);
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
			if (((currentTilePos.x - 1) >= 0) && tileMap->at(tile).isPassable()) // (tile) > 0
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
		// If maxDistance < shortest Value - return 0, slower but more exact out of the loop
		if (shortestDistanceValue > maxDistance + 5){
			return -1;
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
		//printf("SDV: %i \n", shortestDistanceValue);
	}

	// If maxDistance < shortest Value - return 0, probably faster inside the loop
	//if (shortestDistanceValue > maxDistance + 5){
	//	return -1;
	//}

	if (!noPathFound)
	{
		// Get Final Path
		if (pathVector != NULL)
		{
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
		}
		return shortestDistanceValue/10.f;
	}
	else
	{

	}
	return -1;
}