#include "Mask.h"

#include "Light.h"

ElementPolygon Mask::maskPolygon;

bool Mask::tb = true;;
GLuint Mask::maskBuf;
GLuint Mask::renderedTexture;
GLuint Mask::mVAOID;
MaskProgram Mask::maskP;

std::vector< TileObject >* Mask::tileMap = NULL;
GLuint Mask::sizeX;
GLuint Mask::sizeY;
ElementLines Mask::faceLines;

TickCounter Mask::tc;
Texture2D Mask::fovMap;
b2Vec2 Mask::maskCenterPosition;

bool SortVector(b2Vec3 i, b2Vec3 j)	{ 
	return ((i.z < j.z)); 
}	// b2_pi > (i.z - j.z) < b2_pi; || -b2_pi > (i.z - j.z) < b2_pi

bool CompareVectorZ(b2Vec3 i, b2Vec3 j)	{ 
	return (i.z == j.z); 
}


GLuint manhattanDistance(b2Vec2 t1, b2Vec2 t2)
{
	return 10 * (abs(t2.x - t1.x) + abs(t2.y - t1.y));
}
GLuint manhattanDistance(GLuint tileID_1, GLuint tileID_2, GLuint sizeX, GLuint sizeY)
{
	b2Vec2 p1(tileID_1%sizeX, floor(tileID_1 / sizeY));
	b2Vec2 p2(tileID_2%sizeX, floor(tileID_2 / sizeY));

	return manhattanDistance(p1, p2);
}
b2Vec2 getTilePos(b2Vec2 pos)
{
	return b2Vec2(round(pos.x * 100 / TILE_WIDTH), round(pos.y * 100 / TILE_WIDTH));
}
GLuint getTile(b2Vec2 pos, GLuint sizeX)
{
	return sizeX*pos.y + pos.x;
}

b2Vec2 getPos(GLuint tileID, GLuint sizeX)
{
	return b2Vec2(tileID%sizeX, floor(tileID / sizeX));
}

void Mask::setTileMap(std::vector<TileObject>* vecTileMap, GLuint sX, GLuint sY)
{
	tileMap = vecTileMap;
	sizeX = sX;
	sizeY = sY;
}

Mask::Mask()
{
}


Mask::~Mask()
{
}

//GLuint manhattanDistance(b2Vec2 t1, b2Vec2 t2)
//{
//	return 10 * (abs(t2.x - t1.x) + abs(t2.y - t1.y));
//}

enum FaceType
{
	FACETYPE_LEFT,
	FACETYPE_RIGHT,
	FACETYPE_UP,
	FACETYPE_DOWN,
	FACETYPE_DIAG,
};

struct FaceObject{

	FaceObject()	{}
	FaceObject(GLuint ID, b2Vec2 v, b2Vec2 vv, GLfloat distance, GLuint face_type) : id(ID), v1(v), v2(vv), faceType(face_type) {}

	GLuint id;
	b2Vec2 v1;
	b2Vec2 v2;
	GLint next;
	GLint previous;
	GLfloat distanceManhattan;
	GLuint faceType;
};

bool faceCompareByDistance(FaceObject i, FaceObject j) { return i.distanceManhattan > j.distanceManhattan; }

void Mask::updateMask(b2Vec2 centerPosition, std::shared_ptr<b2World> world)
{
//		// Timer for mask update
	GLfloat t1 = glfwGetTime();
	b2Vec2 pPoint = centerPosition;//b2Vec2(Engine::mouse_x * 100, Engine::mouse_y * 100); //
	maskCenterPosition = pPoint;
//	/*
//		LIST OF ALL FORWARD FACING EDGES
//	*/
//	std::vector<FaceObject> faceContainer;	// ID | Faceobject
//	std::vector<b2Vec2> drawFacesVector;
//	GLuint size = tileMap->size();
//
//	b2Vec2 currentTilePos;
//	GLint currentFace = -1;
//	for (/*std::vector<std::shared_ptr<TileObject>>::iterator it = tileMap->begin();it != tileMap->end();++it)*/int i = 0; i < size; i++)
//	{
//		if (tileMap->at(i)->isWall)	// If it is a wall Tile
//		{
//			// Tile should be ignored if down Tile or left Tile is a wall
//			b2Vec2 pos = tileMap->at(i)->position;
//			// Check the surrounding tiles
//
//			GLfloat distanceToTile = manhattanDistance(pos, pPoint);
//			//printf("Pos: %f || pPoint: %f \n", pos.x, pPoint.x);
//	//printf("Pos: %f || pPoint: %f \n", pos.x, pPoint.x);
//			
//			if (pos.x < pPoint.x) // Right Face visible
//			{
////				printf("Size %i || %i || %i \n", sizeX*sizeY - sizeX, i, tileMap->at(i + 1)->isWall);
//				if (i + 1 < sizeX*sizeY - sizeX && !tileMap->at(i + 1)->isWall)
//				{
//					
//					faceContainer.push_back(FaceObject(i, pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2), pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2), distanceToTile,FACETYPE_RIGHT));
//					drawFacesVector.push_back(pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2));
//					drawFacesVector.push_back(pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2));
//					
//				}
//			}		
//			else if (pos.x > pPoint.x) // Left Face visible
//			{
//				if (i - 1 >= 0 && !tileMap->at(i - 1)->isWall)
//				{
//					++currentFace;
//					faceContainer.push_back(FaceObject(i, pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2), pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2), distanceToTile, FACETYPE_LEFT));
//					drawFacesVector.push_back(pos + b2Vec2(-TILE_WIDTH / 2, -TILE_WIDTH / 2));
//					drawFacesVector.push_back(pos + b2Vec2(-TILE_WIDTH / 2, TILE_WIDTH / 2));
//				}
//			}
//
//			if (pos.y < pPoint.y)// Up Face visible 
//			{
//				if (i + sizeX < sizeX*sizeY - sizeX && !tileMap->at(i + sizeX)->isWall)
//				{
//					++currentFace;
//					faceContainer.push_back(FaceObject(i, pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2), pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2), distanceToTile, FACETYPE_UP));
//					drawFacesVector.push_back(pos + b2Vec2(-TILE_WIDTH / 2, TILE_WIDTH / 2));
//					drawFacesVector.push_back(pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2));
//				}
//			}		
//			else if (pos.y > pPoint.y)// Down Face visible		
//			{
//				if ( (int)(i - sizeX) >= 0 && !tileMap->at(i - sizeX)->isWall)
//				{
//					++currentFace;
//					faceContainer.push_back(FaceObject(i, pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2), pos + b2Vec2(TILE_WIDTH / 2, TILE_WIDTH / 2), distanceToTile, , FACETYPE_DOWN));
//					drawFacesVector.push_back(pos + b2Vec2(-TILE_WIDTH / 2, -TILE_WIDTH / 2));
//					drawFacesVector.push_back(pos + b2Vec2(TILE_WIDTH / 2, -TILE_WIDTH / 2));
//				}
//			}
//		}
//	}
//	// No need to sort, because of map!
//	std::sort(faceContainer.begin(), faceContainer.end(), faceCompareByDistance);
//	faceLines.initElement(&drawFacesVector,10,Color4f(1.f,1.f,1.f,1.f),0xFFFF,1.f,false);
//	//printf("Pos: %f \n", drawFacesVector[drawFacesVector.size()-2].x);
//	//printf("Pos: %f \n", drawFacesVector[drawFacesVector.size() - 1].x);
//	drawFacesVector.clear();
//	conLines.initElement(&drawFacesVector, 10, Color4f(1.f, 0.f, 0.f, 1.f), 0xFFFF, 1.f, false);
//	for (std::vector<FaceObject>::iterator it = faceContainer.begin(); it != faceContainer.end(); ++it)
//	{
//		if (it->id)
//	}


		querycall qc;
		b2AABB aabb;

		

		//b2Vec2 aabbHalfSize = b2Vec2(25.f,25.f);

		aabb.upperBound.Set(pPoint.x + 6, pPoint.y + 6);
		aabb.lowerBound.Set(pPoint.x - 6, pPoint.y - 6);
		world->QueryAABB(&qc, aabb);

		b2Vec3 lastPoint;

		std::vector<b2Vec3> renderVertices;
		GLfloat maxDistance = 8.5f;

		b2Vec2 testArr[8];
		GLfloat sqrtTile = 0.9f;//sqrt(TILE_WIDTH*TILE_WIDTH*2);
		//printf("Ergh %f \n", sqrtTile);
		b2Body* body;
		b2Shape* shape;
		b2PolygonShape* poly;
		int numberOfVertices;
		//printf("Size: %i ", qc.fixtureList.size());
		if (qc.fixtureList.size() > 0)
		{
			for (int i = qc.fixtureList.size() - 1; i >= 0; i--)
			{
				body = qc.fixtureList[i]->GetBody();

				shape = qc.fixtureList[i]->GetShape();
				if (shape->m_type == b2Shape::e_polygon)
				{
					poly = (b2PolygonShape*)shape;

					numberOfVertices = poly->m_count;

					for (int c = numberOfVertices - 1; c >= 0; c--)
					{
						testArr[c].Set(atan2(body->GetWorldPoint(poly->m_vertices[c]).x - pPoint.x, body->GetWorldPoint(poly->m_vertices[c]).y - pPoint.y), b2Distance(pPoint, body->GetWorldPoint(poly->m_vertices[c])));
					}

					for (int c = numberOfVertices - 1; c >= 0; c--)
					{
						if (c == numberOfVertices - 1)
						{
							if (abs(testArr[0].x - testArr[c].x) < 0.0001f) //floor(testArr[c + 1].x * 10000) == floor(testArr[c].x * 10000))
							{
								if (testArr[0].y > testArr[c].y)	testArr[0].x = -777.f;
								else testArr[c].x = -777.f;
							}
						}
						else if (abs(testArr[c + 1].x - testArr[c].x) < 0.0001f) //floor(testArr[c + 1].x * 10000) == floor(testArr[c].x * 10000))
						{
							if (testArr[c + 1].y > testArr[c].y)	testArr[c + 1].x = -777.f;
							else testArr[c].x = -777.f;
						}

					}

					for (int u = numberOfVertices - 1; u >= 0; u--)
					{
						if (testArr[u].x != -777.f)
						{

							castcall castt;
							GLfloat angle = testArr[u].x;//atan2(body->GetWorldPoint(poly->GetVertex(u)).x - pPoint.x, body->GetWorldPoint(poly->GetVertex(u)).y - pPoint.y);
							angle += b2_pi;
							GLfloat distance = testArr[u].y;// b2Distance(pPoint, body->GetWorldPoint(poly->GetVertex(u)));

							world->RayCast(&castt, pPoint, pPoint - 0.99f * distance * b2Vec2(sinf(angle), cosf(angle)));//0.999*body->GetWorldPoint(poly->GetVertex(u)) );

							//if (castt.isHit) g_debugDraw.DrawSegment(pPoint, castt.hitPoint, b2Color(0.f, 1.f, 0.f, 1.f));
							//g_debugDraw.DrawPoint( body->GetWorldPoint( poly->GetVertex(u) ), 5.f, b2Color(1.f, 0.f, 0.f, 1.f));
							b2Vec2 vertex = body->GetWorldPoint(poly->m_vertices[u]);

							//g_debugDraw.DrawPoint(castt.hitPoint, 3, b2Color(0.f, 0.f, 1.f));


							//printf("Angle: %f \n", angle);

							if (!castt.isHit)// Only if the vertex is hit	//printf("Angle: %f \n", angle);//(castt.hitPoint.x == vertex.x && castt.hitPoint.y == vertex.y));
							{
								renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));

								//GLfloat dist = (distance > maxDistance) ? distance : maxDistance;

								castcall castL;
								angle += 0.00001f;

								b2Vec2 tp = pPoint - maxDistance * b2Vec2(sinf(angle), cosf(angle));

								world->RayCast(&castL, pPoint, tp);
								if (castL.isHit)//(distance*1.1f > castL.mfraction*maxDistance)
								{
									renderVertices.push_back(b2Vec3(castL.hitPoint.x, castL.hitPoint.y, angle));
								}
								else if (!castL.isHit) //add point at maxDistance
								{
									renderVertices.push_back(b2Vec3(tp.x, tp.y, angle));
									//renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
								}

								castcall castR;
								angle -= 0.00002f;
								b2Vec2 tpp = pPoint - maxDistance * b2Vec2(sinf(angle), cosf(angle));
								world->RayCast(&castR, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
								if (castR.isHit)
								{
									renderVertices.push_back(b2Vec3(castR.hitPoint.x, castR.hitPoint.y, angle));
								}
								else if (!castR.isHit)//add point at maxDistance
								{
									renderVertices.push_back(b2Vec3(tpp.x, tpp.y, angle));
									//renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
								}
							}
							else
							{
								renderVertices.push_back(b2Vec3(castt.hitPoint.x, castt.hitPoint.y, angle));
							}
						}
					}
				}
				//else if (shape->m_type == b2Shape::e_chain)
				//{
				//	b2ChainShape* chain = (b2ChainShape*)shape;
				//	numberOfVertices = chain->GetChildCount();
				//	b2EdgeShape* edge = new b2EdgeShape();
				//	for (int i = 3; i; --i)
				//	{
				//		chain->GetChildEdge(edge, i);
				//		edge->m_vertex0;

				//		castcall castt;
				//		GLfloat angle = atan2(body->GetWorldPoint(edge->m_vertex0).x - pPoint.x, body->GetWorldPoint(edge->m_vertex0).y - pPoint.y);

				//		GLfloat distance = b2Distance(pPoint, body->GetWorldPoint(edge->m_vertex0));

				//		world->RayCast(&castt, pPoint, pPoint + 0.99f * distance * b2Vec2(sinf(angle), cosf(angle)));//0.999*body->GetWorldPoint(poly->GetVertex(u)) );

				//		//if (castt.isHit) g_debugDraw.DrawSegment(pPoint, castt.hitPoint, b2Color(0.f, 1.f, 0.f, 1.f));
				//		//g_debugDraw.DrawPoint( body->GetWorldPoint( poly->GetVertex(u) ), 5.f, b2Color(1.f, 0.f, 0.f, 1.f));
				//		b2Vec2 vertex = body->GetWorldPoint(edge->m_vertex0);

				//		//g_debugDraw.DrawPoint(castt.hitPoint, 3, b2Color(0.f, 0.f, 1.f));

				//		angle += b2_pi;
				//		//printf("Angle: %f \n", angle);

				//		if (!castt.isHit)// Only if the vertex is hit	//printf("Angle: %f \n", angle);//(castt.hitPoint.x == vertex.x && castt.hitPoint.y == vertex.y));
				//		{
				//			renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
				//		}
				//	}
				//}
			}
			
		}
		
		//check for corners
		b2Vec2 tpp;
		GLfloat angle;
		for (float i = -45.01f; i < 270.f; i += 90.f)
		{
			castcall castC;
			angle = toRad(i) + b2_pi / 2.f;
			tpp = pPoint - maxDistance * b2Vec2(sinf(angle), cosf(angle));
			world->RayCast(&castC, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
			if (!castC.isHit)//add point at maxDistance
			{
				renderVertices.push_back(b2Vec3(tpp.x, tpp.y, angle));
			}
		}


		//sort vertices
		std::sort(renderVertices.begin(), renderVertices.end(), SortVector);
		//std::unique(renderVertices.begin(), renderVertices.end(), CompareVectorZ);

		//b2Vec2 previousPos;

		std::vector<b2Vec3>::iterator it = renderVertices.begin();
		std::vector<b2Vec3>::iterator itP;// = renderVertices.begin();
		//printf("Size before: %i || ", renderVertices.size());
		//++it;
		//int v = 0;
		while (it != renderVertices.end())
		{
			//++v;
			if (it != renderVertices.begin())
			{
				itP = it - 1;
				if (abs(itP->z - it->z) < 0.000001f)
				{
					if (b2DistanceSquared(pPoint, b2Vec2(it->x, it->y)) > b2DistanceSquared(pPoint, b2Vec2(itP->x, itP->y)))	it = renderVertices.erase(it);
					else 	it = renderVertices.erase(itP);
				}
				else		++it;
			}
			else	++it;
		}

		//printf("Size after: %i \n", renderVertices.size());
		//printf("\n\n\n");
		GLuint size = renderVertices.size();
	
		std::vector<b2Vec2> v3;
		v3.reserve(size + 1);
		v3.push_back(100 * pPoint);
		/*b2Vec2* vert3;
		vert3 = new b2Vec2[size];
		vert3[size] = pPoint;*/



		//bool insert = true;
		//bool insertNext = true;
		for (int i = 0; i < size; i++)
		{
			v3.push_back(b2Vec2(100 * renderVertices[i].x, 100 * renderVertices[i].y));
		}

		if ((renderVertices[renderVertices.size() - 1].z - renderVertices[0].z) > b2_pi)
		{
			v3.push_back(100 * b2Vec2(renderVertices[0].x, renderVertices[0].y));
		}

		//v3.push_back(100 * pPoint);
		//g_debugDraw.DrawSolidPolygon(&v3[0], size + 2, b2Color(0.f, 1.f, 0.f));
		maskPolygon.initElement(&v3, Color4f(1.f, 0.f, 0.f, 1.f));

		//printf("Time for Mask: %f\n", (glfwGetTime() - t1));
}

void Mask::initMask()
{
	
	maskP.loadProgram();
	maskP.bind();

	maskP.setProjectionMatrix(glm::ortho<GLfloat>(0.5f, 1920.5f, 0.5f, 1080.5f, -1.f, 0.f));
	maskP.updateProjectionMatrix();

	maskP.setModelViewMatrix(glm::mat4());
	maskP.updateModelViewMatrix();
	maskP.setTextureColor(1.f, 1.f, 1.f, 1.f);
	maskP.setTextureUnit(0, 1, 2, 3);

	glGenFramebuffers(1, &maskBuf);
	glBindFramebuffer(GL_FRAMEBUFFER, maskBuf);
	// The texture we're going to render to

	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 2048, 2048, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)	printf("Framebuffer incomplete!\n");







	GLuint vbo;
	GLuint ibo;

	GLfloat texLeft = (float)1920 / (float)2048;
	GLfloat texRight = 0.f;
	GLfloat texTop = 0.f;
	GLfloat texBottom = (float)1080 / (float)2048;


	GLfloat posLeft = 960.f;
	GLfloat posRight = -960.f;
	GLfloat posTop = -540.f;
	GLfloat posBottom = 540.f;


	TexturedVertexPos2D quadPos[4];

	quadPos[0].pos.x = posLeft; quadPos[0].pos.y = posBottom;
	quadPos[1].pos.x = posRight; quadPos[1].pos.y = posBottom;
	quadPos[2].pos.x = posRight; quadPos[2].pos.y = posTop;
	quadPos[3].pos.x = posLeft; quadPos[3].pos.y = posTop;

	quadPos[0].texCoord.s = texLeft; quadPos[0].texCoord.t = texBottom;
	quadPos[1].texCoord.s = texRight; quadPos[1].texCoord.t = texBottom;
	quadPos[2].texCoord.s = texRight; quadPos[2].texCoord.t = texTop;
	quadPos[3].texCoord.s = texLeft; quadPos[3].texCoord.t = texTop;


	//Create VBOs 
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TexturedVertexPos2D), quadPos, GL_STATIC_DRAW);


	//VAO
	glGenVertexArrays(1, &mVAOID);
	glBindVertexArray(mVAOID);
	//Pointers
	//glEnableVertexAttribArray(0);
	maskP.enableDataPointers();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//VertexPointer
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);

	maskP.setVertexPointer(sizeof(TexturedVertexPos2D), (GLvoid*)offsetof(TexturedVertexPos2D, pos));
	maskP.setTexCoordPointer(sizeof(TexturedVertexPos2D), (GLvoid*)offsetof(TexturedVertexPos2D, texCoord));

	//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
	//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));

	glBindVertexArray(NULL);
	fovMap.loadPixelsFromFile32("FOVMap.png");
	fovMap.loadTextureFromPixels32();
}

void Mask::renderMask(b2Vec2 wp, GLuint backRenderTexture, GLuint frontRenderTexture)
{

	glBindFramebuffer(GL_FRAMEBUFFER, maskBuf);
	glClearBufferuiv(GL_COLOR, 0, &maskBuf);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 2048, 2048, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);

	//glClearBufferuiv(GL_COLOR, 0, &maskBuf);
	//glViewport(0, 0, 1920.f, 1080.f); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	//testTexB.render(960.f, 540.f);



	maskPolygon.render(b2Vec2(wp.x, wp.y));
	fovMap.render(100 * maskCenterPosition.x + wp.x, 100 * maskCenterPosition.y + wp.y, 4.f, 4.f);




	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);


	maskP.bind();
	maskP.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(960.f, 540.f, 0.f)));//960.f+BaseObject::getWorldPos().x, 540.f+BaseObject::getWorldPos().y, 0.f));
	maskP.updateModelViewMatrix();
	glBindVertexArray(mVAOID);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backRenderTexture);//scTexture.getTextureID() );

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, frontRenderTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, /*testTexM*/renderedTexture);//maskTex.getTextureID());//maskTex

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, PointLight::lightTextureID);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	glActiveTexture(GL_TEXTURE3);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

	GLuint Fre = glGetError();
	if (Fre != GL_NO_ERROR)
	{
		printf("Error Line of Sight \n");
	}

}

void Mask::debugRender()
{
	faceLines.render(BaseObject::getWorldPos());
}