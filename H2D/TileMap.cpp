#include "TileMap.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtx\transform.hpp>


#include <fstream>
#include <ostream>
#include <sstream>

TileProgram TileMap::tileProgram;
std::vector< TexCoords4 > TileMap::texCoords;
GLuint TileMap::tileMapSheet;
GLuint TileMap::tileMapSheetTextureID;

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

void TileMap::loadTileMapBaseData()
{
	tileProgram.loadProgram();
	tileProgram.bind();

	tileProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f, 1920.5f, 1080.5f, 0.5f, -1.f, 0.f));
	tileProgram.updateProjectionMatrix();

	tileProgram.setModelViewMatrix(glm::mat4());
	tileProgram.updateModelViewMatrix();
	tileProgram.setTextureUnit(0);

	GLuint tileWidth = TILE_WIDTH; // IMPORTANT

	tileMapSheet = 1;
	SpriteSheet2D* tileSheet = BaseObject::getSpriteSheet(tileMapSheet);
	tileMapSheetTextureID = tileSheet->getTextureID();
	GLfloat texS = tileSheet->getImgWidth();
	//texCoords.reserve
	//glm::vec2 texCoord[4];
	TexCoords4 texCoord;
	for (GLuint i = 0; i < tileSheet->getImgWidth(); i += tileWidth + 0.f)
	{
		for (GLuint u = 0; u < tileSheet->getImgWidth(); u += tileWidth + 0.f)
		{
			GLfloat texLeft = (float)(u + 1) / ((float)texS);
			GLfloat texRight = (float)((u - 1) + tileWidth) / ((float)texS);
			GLfloat texTop = (float)((i + 1)) / ((float)texS);
			GLfloat texBottom = (float)((i - 1) + tileWidth) / ((float)texS);


			texCoord.t0.x = texLeft; texCoord.t0.y = texBottom;
			texCoord.t1.x = texRight; texCoord.t1.y = texBottom;
			texCoord.t2.x = texRight; texCoord.t2.y = texTop;
			texCoord.t3.x = texLeft; texCoord.t3.y = texTop;

			texCoords.push_back(texCoord);//(texLeft, texRight, texTop, texBottom));
		}
	}
}


void TileMap::create(std::ifstream *myfile, GLuint sX, GLuint sY)
{

	tileMapVBO;
	//tileMapSheet = 1;

	/*
		Create Border
	*/
	//b2BodyDef bd;
	//bd.position = b2Vec2(0.f, 0.f);
	//b2FixtureDef fd;
	//GLfloat twH = TILE_WIDTH / 200;
	//b2ChainShape* border = new b2ChainShape();
	//b2Vec2 vs[4];
	//vs[0] = b2Vec2(-twH, -twH);
	//vs[1] = b2Vec2(sizeX * TILE_WIDTH / 100 - twH, -twH);
	//vs[2] = b2Vec2(sizeX * TILE_WIDTH / 100 - twH, sizeY * TILE_WIDTH / 100 - twH);
	//vs[3] = b2Vec2(-twH, sizeY * TILE_WIDTH / 100 - twH);
	//border->CreateLoop(vs, 4);

	//fd.shape = border;

	//b2Body* borderB = BaseObject::getWorld()->CreateBody(&bd);
	//borderB->CreateFixture(&fd);
	/*
		Boder End
	*/
	
	


	//GLfloat posLeft = -TILE_WIDTH/2.f;
	//GLfloat posRight = TILE_WIDTH / 2.f;
	//GLfloat posTop = TILE_WIDTH / 2.f;
	//GLfloat posBottom = -TILE_WIDTH / 2.f;


	//b2Vec2 quadPos[4];

	//quadPos[0].x = posLeft; quadPos[0].y = posBottom;
	//quadPos[1].x = posRight; quadPos[1].y = posBottom;
	//quadPos[2].x = posRight; quadPos[2].y = posTop;
	//quadPos[3].x = posLeft; quadPos[3].y = posTop;




	//std::vector<TexCoords4> texC;
	//std::vector<b2Vec2> vertices;
	////glm::vec2* texC = new glm::vec2[sizeOverall * 4];

	//texC.reserve(sizeOverall);
	//tileMap.reserve(sizeOverall);

	//startCount.reserve(sizeOverall);
	//count.reserve(sizeOverall);
	//for (int y = 0; y < sizeY; y++)
	//{
	//	//tileMap.push_back( std::vector < std::shared_ptr<TileObject> >() ); //.reserve[sizeY];
	//	//tileMap[x].reserve[sizeY];
	//	for (int x = 0; x < sizeX; x++)
	//	{
	//		GLuint currentID = y*sizeX + x;

	//		float asd = rand() % 100;
	//		GLfloat id = 0;
	//		tileMap.push_back(TileObject());
	//		if (asd > debugValue) id = 1;//std::make_shared<WallTile>());
	//		else id = 0;

	//		tileMap[currentID].init(b2Vec2((float)x * TILE_WIDTH, (float)y * TILE_WIDTH), id);
	//		//tileMap[currentID]->pos.Set((float)x * 128.f, (float)y * 128.f);
	//		//tileMap[currentID]->spriteID = 

	//		vertices.push_back(tileMap[currentID].position + quadPos[0]);
	//		vertices.push_back(tileMap[currentID].position + quadPos[1]);
	//		vertices.push_back(tileMap[currentID].position + quadPos[2]);
	//		vertices.push_back(tileMap[currentID].position + quadPos[3]);

	//		texC.push_back(texCoords[tileMap[currentID].spriteID]);
	//		startCount.push_back(currentID * 4);
	//		count.push_back(4);
	//	}
	//}

	////Create VBOs 
	//
	//glGenBuffers(1, &vertexVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(b2Vec2), &vertices[0], GL_STATIC_DRAW);

	///*GLuint positionVBO;
	//glGenBuffers(1, &positionVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	//glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(b2Vec2), &positions[0], GL_STATIC_DRAW);*/

	//
	//glGenBuffers(1, &textureVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	//glBufferData(GL_ARRAY_BUFFER, texC.size() * sizeof(TexCoords4), &texC[0], GL_STATIC_DRAW);

	//tileProgram.bind();

	////VAO
	//glGenVertexArrays(1, &mVAOID);
	//glBindVertexArray(mVAOID);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);


	////VertexPointer


	//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

	//glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

	//glBindVertexArray(NULL);
	//
	//saveTileMap();
	loadTileMap(myfile,sX,sY);
}

void TileMap::setTileMaps()
{
	Person::setTileMap(&tileMap, sizeX, sizeY);
	Mask::setTileMap(&tileMap, sizeX, sizeY);
}

void TileMap::render()
{
	b2Vec2 wp = BaseObject::getWorldPos();

	tileProgram.bind();
	tileProgram.setModelViewMatrix( glm::translate<GLfloat>(wp.x, wp.y, 0.f) );
	tileProgram.updateModelViewMatrix();
	glBindVertexArray(mVAOID);

	glBindTexture(GL_TEXTURE_2D, tileMapSheetTextureID);//tileMapSheet);

	//glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, sizeOverall);

	glMultiDrawArrays(GL_TRIANGLE_FAN, &startCount[0], &count[0], sizeOverall);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, sizeOverall);//4);
	if (glGetError() != GL_NO_ERROR)	printf("Error rendering!\n");
	glBindVertexArray(NULL);
	for (int i = wallVector.size()-1; i > 0; i--)
	{
		wallVector[i].render();
	}

}

void TileMap::changeTile(GLuint tileID, TileObject tileObj)
{
	if (tileID >= 0 && tileID < tileMap.size())
	{
		tileMap[tileID] = tileObj;//.reset(tileObj);// = std::make_shared<TileObject>();
		TexCoords4 data;
		data = texCoords[tileObj.spriteID];
	
		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferSubData(GL_ARRAY_BUFFER, tileID * sizeof(TexCoords4), sizeof(TexCoords4), &data);	// or tileID+1
	}
}

void TileMap::saveTileMap(std::ofstream &sstream)
{	//http://www.cplusplus.com/doc/tutorial/files/
	//myfile.open("example.txt");

 	std::vector< TileObject >::iterator it = tileMap.begin();
	while (it != tileMap.end())
	{
		sstream << it->spriteID << '\n';
		++it;
	}



}

void TileMap::loadTileMap(std::ifstream *myfile, GLuint sX, GLuint sY)
{
	sizeX = sX;
	sizeY = sY;
	sizeOverall = sY*sX;

	if (myfile)
	{	
		std::string line;
		//std::ifstream myfile("example.txt");
		std::string ll[3];

		tileMap.clear();

		std::vector<int> idList;
		while (std::getline(*myfile, line) && line != "N")
		{
			
			//int i = 0;
			//std::stringstream ss(line);
			/*while (ss)
			{
				std::string s;
				if (!std::getline(ss, s, '|')) break;
				ll[i] = s;
				//std::cout << "Line: " << ll[i] << std::endl;
				++i;
			}*/
			//printf("Line: %i \n", std::stoi(line));
			idList.push_back(std::stoi(line));
		}

		GLfloat posLeft = -TILE_WIDTH / 2.f;
		GLfloat posRight = TILE_WIDTH / 2.f;
		GLfloat posTop = TILE_WIDTH / 2.f;
		GLfloat posBottom = -TILE_WIDTH / 2.f;


		b2Vec2 quadPos[4];

		quadPos[0].x = posLeft; quadPos[0].y = posBottom;
		quadPos[1].x = posRight; quadPos[1].y = posBottom;
		quadPos[2].x = posRight; quadPos[2].y = posTop;
		quadPos[3].x = posLeft; quadPos[3].y = posTop;

		std::vector<TexCoords4> texC;
		std::vector<b2Vec2> vertices;
		//glm::vec2* texC = new glm::vec2[sizeOverall * 4];

		texC.reserve(sizeOverall);
		tileMap.reserve(sizeOverall);

		startCount.reserve(sizeOverall);
		count.reserve(sizeOverall);
		for (int y = 0; y < sizeY; y++)
		{
			//tileMap.push_back( std::vector < std::shared_ptr<TileObject> >() ); //.reserve[sizeY];
			//tileMap[x].reserve[sizeY];
			for (int x = 0; x < sizeX; x++)
			{
				GLuint currentID = y*sizeX + x;
				

				float asd = rand() % 100;
				GLfloat id = 0;
				tileMap.push_back(TileObject());
				//if (asd > debugValue) id = 1;//std::make_shared<WallTile>());
				//else id = 0;

				tileMap[currentID].init(b2Vec2((float)x * TILE_WIDTH, (float)y * TILE_WIDTH), idList[currentID]);
				//tileMap[currentID]->pos.Set((float)x * 128.f, (float)y * 128.f);
				//tileMap[currentID]->spriteID = 

				vertices.push_back(tileMap[currentID].position + quadPos[0]);
				vertices.push_back(tileMap[currentID].position + quadPos[1]);
				vertices.push_back(tileMap[currentID].position + quadPos[2]);
				vertices.push_back(tileMap[currentID].position + quadPos[3]);

				texC.push_back(texCoords[tileMap[currentID].spriteID]);
				startCount.push_back(currentID * 4);
				count.push_back(4);

			}
		}
		//Create VBOs 

		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(b2Vec2), &vertices[0], GL_STATIC_DRAW);

		/*GLuint positionVBO;
		glGenBuffers(1, &positionVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(b2Vec2), &positions[0], GL_STATIC_DRAW);*/


		glGenBuffers(1, &textureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferData(GL_ARRAY_BUFFER, texC.size() * sizeof(TexCoords4), &texC[0], GL_STATIC_DRAW);

		tileProgram.bind();

		//VAO
		glGenVertexArrays(1, &mVAOID);
		glBindVertexArray(mVAOID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		//VertexPointer


		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

		glBindVertexArray(NULL);


	}
	else
	{
		GLfloat posLeft = -TILE_WIDTH / 2.f;
		GLfloat posRight = TILE_WIDTH / 2.f;
		GLfloat posTop = TILE_WIDTH / 2.f;
		GLfloat posBottom = -TILE_WIDTH / 2.f;


		b2Vec2 quadPos[4];

		quadPos[0].x = posLeft; quadPos[0].y = posBottom;
		quadPos[1].x = posRight; quadPos[1].y = posBottom;
		quadPos[2].x = posRight; quadPos[2].y = posTop;
		quadPos[3].x = posLeft; quadPos[3].y = posTop;

		std::vector<TexCoords4> texC;
		std::vector<b2Vec2> vertices;
		//glm::vec2* texC = new glm::vec2[sizeOverall * 4];

		texC.reserve(sizeOverall);
		tileMap.reserve(sizeOverall);

		startCount.reserve(sizeOverall);
		count.reserve(sizeOverall);
		for (int y = 0; y < sizeY; y++)
		{
			//tileMap.push_back( std::vector < std::shared_ptr<TileObject> >() ); //.reserve[sizeY];
			//tileMap[x].reserve[sizeY];
			for (int x = 0; x < sizeX; x++)
			{
				GLuint currentID = y*sizeX + x;

				float asd = rand() % 100;
				GLfloat id = 0;
				tileMap.push_back(TileObject());
				//if (asd > debugValue) id = 1;//std::make_shared<WallTile>());
				//else id = 0;

				tileMap[currentID].init(b2Vec2((float)x * TILE_WIDTH, (float)y * TILE_WIDTH), 0);
				//tileMap[currentID]->pos.Set((float)x * 128.f, (float)y * 128.f);
				//tileMap[currentID]->spriteID = 

				vertices.push_back(tileMap[currentID].position + quadPos[0]);
				vertices.push_back(tileMap[currentID].position + quadPos[1]);
				vertices.push_back(tileMap[currentID].position + quadPos[2]);
				vertices.push_back(tileMap[currentID].position + quadPos[3]);

				texC.push_back(texCoords[tileMap[currentID].spriteID]);
				startCount.push_back(currentID * 4);
				count.push_back(4);
			}
		}
		//Create VBOs 

		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(b2Vec2), &vertices[0], GL_STATIC_DRAW);

		/*GLuint positionVBO;
		glGenBuffers(1, &positionVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(b2Vec2), &positions[0], GL_STATIC_DRAW);*/


		glGenBuffers(1, &textureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferData(GL_ARRAY_BUFFER, texC.size() * sizeof(TexCoords4), &texC[0], GL_STATIC_DRAW);

		tileProgram.bind();

		//VAO
		glGenVertexArrays(1, &mVAOID);
		glBindVertexArray(mVAOID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		//VertexPointer


		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(b2Vec2), 0);

		glBindVertexArray(NULL);

	}
	calculateWalls();

}

void TileMap::calculateWalls()
{
	//b2Vec2 pPoint = centerPosition;//b2Vec2(Engine::mouse_x * 100, Engine::mouse_y * 100); //
		
	std::set<int> checkedTiles;
	
	/*
		CHECK FOR CONNECTED WALL TILES
	*/

	GLuint currentTileID = 0;
	bool finished = false;
	GLuint WallObjectID = 0;
	while (!finished && currentTileID < tileMap.size())
	{
		if (checkedTiles.find(currentTileID) == checkedTiles.end() && tileMap[currentTileID].isWall)
		{

			GLuint direction = 0;
			// check surrounding tiles for direction
			if (currentTileID + sizeX < sizeX*sizeY - sizeX && tileMap[currentTileID + sizeX].isWall)	// UP
			{
				direction = 1;
			}
			/*else if (currentTileID - sizeX >= 0 - sizeX && tileMap[currentTileID - sizeX].isWall)	// DOWN
			{
				direction = 2;
			}
			else if (currentTileID - 1 < sizeX*sizeY - sizeX && tileMap[currentTileID - 1].isWall)	// LEFT	// CHANGE IT TO WORK CORRECTLY!!!
			{
				direction = 3;
			}*/
			else if ((currentTileID + 1) < sizeX*sizeY-sizeX && tileMap[currentTileID + 1].isWall)	// RIGHT
			{
				direction = 4;
			}
			GLint tile = currentTileID;
			b2Vec2 startPos = getPos(tile, sizeX);
			b2Vec2 endPos = startPos;			
			switch (direction)
			{
			case 1:
			{
					  Wall w;
					  do
					  {
						  checkedTiles.insert(tile);
						  w.addTile(tile);
						  if (tileMap[tile].isWall)
						  {
							  tileMap[tile].setWallObject(WallObjectID);
							  endPos = getPos(tile, sizeX);
						  }
						  else break;
						  tile += sizeX;
					  } while (tile < sizeX*sizeY - sizeX && checkedTiles.find(tile) == checkedTiles.end());
					  
					  w.init(TILE_WIDTH / 100 * startPos, TILE_WIDTH / 100 * endPos);
					  wallVector.push_back(w);
			}
				break;
			case 4:
			{
					  Wall w;
					  while (tile + 1 < tileMap.size() && checkedTiles.find(tile) == checkedTiles.end())
					  {
						 // printf("RIght side: %i \n", abs(tile + 1) % sizeX != 0);
						  checkedTiles.insert(tile);
						  w.addTile(tile);
						  if (tile < tileMap.size() && abs(tile+1)%sizeX != 0 && tileMap[tile].isWall)
						  {
							  tileMap[tile].setWallObject(WallObjectID);
							  endPos = getPos(tile, sizeX);
						  }
						  else break;
						  tile += 1;
					  }
					  
					  w.init(TILE_WIDTH / 100 * startPos, TILE_WIDTH / 100 * endPos);
					  wallVector.push_back(w);
			}
				break;
			case 0:
			{
					  Wall w;
					  tileMap[tile].setWallObject(WallObjectID);
					  w.addTile(tile);
					  w.init(TILE_WIDTH / 100 * startPos, TILE_WIDTH / 100 * endPos);
					  wallVector.push_back(w);
			}
				break;
				// MIGHT NOT NEED THE FOLLOWING CONDITIONS
			case 3:
				break;
			case 2:
				break;
			}
		++WallObjectID;
		}
		else
		{
			
		}
		++currentTileID;

	}

}

void TileMap::destroyWall(GLuint tile)
{
	//GLuint tile = 53;
	b2Vec2 tilePos = getPos(tile, sizeX);

	if (tileMap[tile].isWall)
	{
		printf("NotWall");
		GLuint wallObject = tileMap[tile].getWallObject();

		// Destroy old wall, create new wall from startPos to tile next to Hole and a second wall from hole to endpos

		// Get Hole and adjacing tiles
		b2Vec2 startPos = wallVector[wallObject].getStartPos();
		b2Vec2 endPos = wallVector[wallObject].getEndPos();

		bool isVertical = abs(endPos.y - startPos.y) > 0.1;
		bool isHorizontal = abs(endPos.x - startPos.x) > 0.1;
		printf("FIASDIASF %i || %i \n", isVertical, isHorizontal);
		wallVector[wallObject].destroyWall();
		
		TileObject t;
		t.init(tilePos, 0);
		changeTile(tile, t);

		if (isVertical)
		{
			if ((tile) >= sizeX && tileMap[tile - sizeX].isWall && tileMap[tile - sizeX].wallObject == wallObject)// Down First
			{
				// Down
				Wall w;
				w.init(startPos, 0.64f * getPos(tile - sizeX, sizeX));
				wallVector[wallObject] = w;
				// Up
				if (tileMap[tile + sizeX].isWall && tileMap[tile + sizeX].wallObject == wallObject)
				{
					GLuint startTile = tile + sizeX;
					GLuint endTile = getTile( getTilePos(endPos), sizeX);

					Wall ww;
					ww.init(0.64f * getPos(tile + sizeX, sizeX), endPos);
					wallVector.push_back(ww);

					GLuint wallObj = wallVector.size() - 1;
					for (int i = endTile; i >= startTile; i -= sizeX)
					{
						tileMap[i].wallObject = wallObj;
					}
				}
			}
			else if (tileMap[tile + sizeX].isWall && tileMap[tile + sizeX].wallObject == wallObject)// Up only
			{
				Wall w;
				w.init(0.64f * getPos(tile + sizeX, sizeX), endPos);
				wallVector[wallObject] = w;
			}
		}
		else if (isHorizontal)
		{
			if (tileMap[tile - 1].isWall && tileMap[tile - 1].wallObject == wallObject)
			{
				// Left
				Wall w;
				w.init(startPos, 0.64f * getPos(tile - 1, sizeX));
				wallVector[wallObject] = w;
				// Right
				if (tileMap[tile + 1].isWall && tileMap[tile + 1].wallObject == wallObject)
				{
					GLuint startTile = tile + 1;
					GLuint endTile = getTile(getTilePos(endPos), sizeX);// getTile(getTilePos(endPos), sizeX);
					Wall ww;
					ww.init(0.64f * getPos(startTile, sizeX), endPos);
					wallVector.push_back(ww);

					GLuint wallObj = wallVector.size() - 1;
					for (int i = endTile; i >= startTile; i--)
					{

						tileMap[i].wallObject = wallObj;
					}
				}
			}
			else if (tileMap[tile + 1].isWall && tileMap[tile + 1].wallObject == wallObject)// Right only
			{
				Wall w;
				w.init(0.64f * getPos(tile + 1, sizeX),endPos);
				wallVector[wallObject] = w;
			}
		}
		else
		{	
			wallVector[wallObject].setActive(false);
			return;
		}
	}
	

	// Done


}