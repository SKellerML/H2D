#include "Light.h"
#include "Rect.h"
#include "VertexPos2D.h"
#include "Mask.h"

//LightProgram PointLight::lightProgram;
Texture2D Light::lightTex;
GLuint Light::lightMaskBuf;
Texture2D Light::backgroundLight;
GLuint Light::lightTextureID;

//bool SortVector(b2Vec3 i, b2Vec3 j) {
//	return ((i.z < j.z));
//}	// b2_pi > (i.z - j.z) < b2_pi; || -b2_pi > (i.z - j.z) < b2_pi
//
//bool CompareVectorZ(b2Vec3 i, b2Vec3 j) {
//	return (i.z == j.z);
//}

void Light::initLightRendering()
{
	//glGenFramebuffers(1, &lightBuf);
	//glBindFramebuffer(GL_FRAMEBUFFER, lightBuf);
	// The texture we're going to render to
	//
	glClearStencil(0);
	glGenTextures(1, &lightTextureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, lightTextureID);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "renderedTexture" as our colour attachement #0
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, lightTexture, 0);

	//// Set the list of draw buffers.
	//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	//glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)	printf("Framebuffer incomplete!\n");
	backgroundLight.loadTextureFromFile32("LightTex.png");
}
void Light::activateLightRendering()
{
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, lightTextureID, 0);
	glClearBufferuiv(GL_COLOR, 0, &frameBuffer);
	backgroundLight.render(960.f,540.f);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
}
void Light::deactivateLightRendering()
{
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDisable(GL_STENCIL_TEST);
}

b2Vec2 rotate_point(float cx, float cy, float angle, b2Vec2 p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	b2Vec2 uu(cx, cy);

	// rotate point
	float xnew = uu.x * c - uu.y * s;
	float ynew = uu.x * s + uu.y * c;

	// translate point back:
	uu.x = xnew + p.x;
	uu.y = ynew + p.y;
	return uu;
}




PointLight::PointLight()
{
	renderPos.Set(0.f, 0.f);
	rOffset.Set(0.f, 0.f);
}

PointLight::~PointLight()
{
}

void PointLight::createLight(b2Vec2 pos, GLfloat radius, Color4f lightColor, b2Vec2 rotationOffset)
{
	m_lightColor = lightColor;
	rOffset = rotationOffset;
	//size.Set(100.f * radius, 100.f * radius);
	this->radius = radius;
	scaleFactor = (100*radius)/500.f ;
	//lightProgram.loadProgram();
	//lightProgram.bind();

	//lightProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f, 1920.5f, 0.5f, 1080.5f, -1.f, 0.f));
	//lightProgram.updateProjectionMatrix();

	//lightProgram.setModelViewMatrix(glm::mat4());
	//lightProgram.updateModelViewMatrix();
	//lightProgram.setTextureColor(m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightColor.a);
	//lightProgram.setTextureUnit(0, 1, 2);

	lightTex.loadTextureFromFile32("pointlight.png");

	std::vector<b2Vec2> shape;
	shape.push_back(b2Vec2(0.f, 0.f));
	shape.push_back(b2Vec2(0.f, 540.f));
	shape.push_back(b2Vec2(1920.f, 540.f));
	shape.push_back(b2Vec2(1920.f, 0.f));

	polyFan.initElement(&shape, Color4f(1.f, 1.f, 1.f, 1.f));
}

void PointLight::updateLight(b2Vec2 pos,GLfloat angle)
{
	m_angle = angle;

	if (rOffset.x != 0.f || rOffset.y != 0)
	{
		renderPos = rotate_point(rOffset.x, rOffset.y, m_angle,pos);
		//renderPos.x = ((rOffset.x - pos.x) * cos(m_angle)) - ((pos.y - rOffset.y) * sin(m_angle)) - pos.x;
		//renderPos.y = ((pos.y - rOffset.y) * cos(m_angle)) - ((rOffset.x - pos.x) * sin(m_angle)) + pos.y;
	}



	m_pos = renderPos;
	b2Vec2 pPoint = renderPos;
	querycall qc;
	b2AABB aabb;
	std::shared_ptr<b2World> world = BaseObject::getWorld();
	//b2Vec2 aabbHalfSize = b2Vec2(25.f,25.f);

	GLfloat hs = radius + .5f;//2.5f+.5f;

	aabb.upperBound.Set(pPoint.x + hs, pPoint.y + hs);
	aabb.lowerBound.Set(pPoint.x - hs, pPoint.y - hs);
	world->QueryAABB(&qc, aabb);

	b2Vec3 lastPoint;

	std::vector<b2Vec3> renderVertices;
	GLfloat maxDistance = hs+1.0f;

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

				numberOfVertices = poly->m_count;// GetVertexCount();

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
			else if (shape->m_type == b2Shape::e_chain)
			{
				//b2ChainShape* chain = (b2ChainShape*)shape;
				//numberOfVertices = chain->GetChildCount();
				//b2EdgeShape* edge = new b2EdgeShape();
				//for (int i = numberOfVertices-1; i>=0; --i)
				//{
				//	printf("THE I: %i ", i);
				//	chain->GetChildEdge(edge, i);
				//	edge->m_vertex0;

				//	castcall castt;
				//	GLfloat angle = atan2(body->GetWorldPoint(edge->m_vertex0).x - pPoint.x, body->GetWorldPoint(edge->m_vertex0).y - pPoint.y);

				//	GLfloat distance = b2Distance(pPoint, body->GetWorldPoint(edge->m_vertex0));

				//	world->RayCast(&castt, pPoint, pPoint + 0.99f * distance * b2Vec2(sinf(angle), cosf(angle)));//0.999*body->GetWorldPoint(poly->GetVertex(u)) );

				//	//if (castt.isHit) g_debugDraw.DrawSegment(pPoint, castt.hitPoint, b2Color(0.f, 1.f, 0.f, 1.f));
				//	//g_debugDraw.DrawPoint( body->GetWorldPoint( poly->GetVertex(u) ), 5.f, b2Color(1.f, 0.f, 0.f, 1.f));
				//	b2Vec2 vertex = body->GetWorldPoint(edge->m_vertex0);

				//	//g_debugDraw.DrawPoint(castt.hitPoint, 3, b2Color(0.f, 0.f, 1.f));

				//	angle += b2_pi;
				//	//printf("Angle: %f \n", angle);

				//	if (!castt.isHit)// Only if the vertex is hit	//printf("Angle: %f \n", angle);//(castt.hitPoint.x == vertex.x && castt.hitPoint.y == vertex.y));
				//	{
				//		renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
				//	}
				//	else
				//	{
				//		renderVertices.push_back(b2Vec3(castt.hitPoint.x, castt.hitPoint.y, angle));
				//	}
				//}
			}
		}
	}

	// check for corners
	b2Vec2 tpp;
	GLfloat ang;
	for (float i = -45.01f; i < 270.f; i += 90.f)
	{
		castcall castC;
		ang = toRad(i) + b2_pi / 2.f;
		tpp = pPoint - maxDistance * b2Vec2(sinf(ang), cosf(ang));
		if (pPoint.x != tpp.x || pPoint.y != tpp.y)
		{
			world->RayCast(&castC, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
			if (!castC.isHit)//add point at maxDistance
			{
				renderVertices.push_back(b2Vec3(tpp.x, tpp.y, ang));
			}
		}
		//else
		//{
		//	renderVertices.push_back(b2Vec3(castC.hitPoint.x, castC.hitPoint.y, angle));
		//}
	}
	//sort vertices
	std::sort(renderVertices.begin(), renderVertices.end(), SortVector);

	std::vector<b2Vec3>::iterator it = renderVertices.begin();
	std::vector<b2Vec3>::iterator itP;
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

	GLuint size = renderVertices.size();

	std::vector<b2Vec2> v3;
	v3.reserve(size + 1);
	v3.push_back(100 * pPoint);

	for (int i = 0; i < size; i++)
	{
		v3.push_back(b2Vec2(100 * renderVertices[i].x, 100 * renderVertices[i].y));
	}

	//if ((renderVertices[renderVertices.size() - 1].z - renderVertices[0].z) > b2_pi)
	//{
		v3.push_back(100 * b2Vec2(renderVertices[0].x, renderVertices[0].y));
	//}

	polyFan.initElement(&v3, Color4f(1.f, 1.f, 1.f, 1.f));
}

void PointLight::renderLight()
{
	b2Vec2 rPos = 100 * renderPos + BaseObject::getWorldPos();


	glClear(GL_STENCIL_BUFFER_BIT);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	

	glStencilFunc(GL_ALWAYS, 1, 1);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.1f);
	//glDisable(GL_TEXTURE_2D);
	// DRAW THE POLYGON
	polyFan.render(BaseObject::getWorldPos());



	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glStencilFunc(GL_EQUAL, 1, 1);
	lightTex.render(rPos.x, rPos.y, m_lightColor, scaleFactor, scaleFactor);
}
































SpotLight::SpotLight()
{
	renderPos.Set(0.f, 0.f);
	rOffset.Set(0.f, 0.f);
}


SpotLight::~SpotLight()
{
}

void SpotLight::createLight(b2Vec2 pos, GLfloat lightAngle, GLfloat radius, Color4f lightColor, b2Vec2 rotationOffset)
{
	m_lightColor = lightColor;
	rOffset = rotationOffset;
	this->radius = radius;
	scaleFactor = (100 * radius) / 500.f;
	m_lightAngle = lightAngle;
	//lightProgram.loadProgram();
	//lightProgram.bind();

	//lightProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f, 1920.5f, 0.5f, 1080.5f, -1.f, 0.f));
	//lightProgram.updateProjectionMatrix();

	//lightProgram.setModelViewMatrix(glm::mat4());
	//lightProgram.updateModelViewMatrix();
	//lightProgram.setTextureColor(m_lightColor.r, m_lightColor.g, m_lightColor.b, m_lightColor.a);
	//lightProgram.setTextureUnit(0, 1, 2);

	lightTex.loadTextureFromFile32("pointlight.png");

	std::vector<b2Vec2> shape;
	shape.push_back(b2Vec2(0.f, 0.f));
	shape.push_back(b2Vec2(0.f, 540.f));
	shape.push_back(b2Vec2(1920.f, 540.f));
	shape.push_back(b2Vec2(1920.f, 0.f));

	polyFan.initElement(&shape, Color4f(1.f, 1.f, 1.f, 1.f));
}

void SpotLight::updateLight(b2Vec2 pos, GLfloat lightAngle, GLfloat angle)
{
	printf("Angle::: %f \n", angle);
	m_angle = angle+b2_pi;
	m_lightAngle = lightAngle;
	if (rOffset.x != 0.f || rOffset.y != 0)
	{
		renderPos = rotate_point(rOffset.x, rOffset.y, m_angle, pos);
		//renderPos.x = ((rOffset.x - pos.x) * cos(m_angle)) - ((pos.y - rOffset.y) * sin(m_angle)) - pos.x;
		//renderPos.y = ((pos.y - rOffset.y) * cos(m_angle)) - ((rOffset.x - pos.x) * sin(m_angle)) + pos.y;
	}

	GLfloat startAngle = (-m_angle) - toRad(m_lightAngle / 2.f);
	while (startAngle < 0)	startAngle += 2 * b2_pi;
	while (startAngle > 2 * b2_pi)	startAngle -= 2 * b2_pi;
	GLfloat endAngle = (-m_angle) + toRad(m_lightAngle / 2.f);
	while (endAngle < 0)	endAngle += 2 * b2_pi;
	while (endAngle > 2 * b2_pi)	endAngle -= 2 * b2_pi;

	if (abs(startAngle - endAngle) > m_lightAngle) std::swap(startAngle, endAngle);

	m_pos = renderPos;
	b2Vec2 pPoint = renderPos;
	querycall qc;
	b2AABB aabb;
	std::shared_ptr<b2World> world = BaseObject::getWorld();
	//b2Vec2 aabbHalfSize = b2Vec2(25.f,25.f);

	GLfloat hs = 2.5f + .5f;

	aabb.upperBound.Set(pPoint.x + hs, pPoint.y + hs);
	aabb.lowerBound.Set(pPoint.x - hs, pPoint.y - hs);
	world->QueryAABB(&qc, aabb);

	b2Vec3 lastPoint;

	std::vector<b2Vec3> renderVertices;
	GLfloat maxDistance = hs + 1.0f;

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
					if (testArr[u].x != -777.f && (testArr[u].x > startAngle && testArr[u].x < endAngle))
					{

						castcall castt;
						GLfloat an = testArr[u].x;//atan2(body->GetWorldPoint(poly->GetVertex(u)).x - pPoint.x, body->GetWorldPoint(poly->GetVertex(u)).y - pPoint.y);
						an += b2_pi;
						GLfloat distance = testArr[u].y;// b2Distance(pPoint, body->GetWorldPoint(poly->GetVertex(u)));

						world->RayCast(&castt, pPoint, pPoint - 0.99f * distance * b2Vec2(sinf(an), cosf(an)));//0.999*body->GetWorldPoint(poly->GetVertex(u)) );

						//if (castt.isHit) g_debugDraw.DrawSegment(pPoint, castt.hitPoint, b2Color(0.f, 1.f, 0.f, 1.f));
						//g_debugDraw.DrawPoint( body->GetWorldPoint( poly->GetVertex(u) ), 5.f, b2Color(1.f, 0.f, 0.f, 1.f));
						b2Vec2 vertex = body->GetWorldPoint(poly->m_vertices[u]);

						//g_debugDraw.DrawPoint(castt.hitPoint, 3, b2Color(0.f, 0.f, 1.f));


						//printf("Angle: %f \n", angle);

						if (!castt.isHit)// Only if the vertex is hit	//printf("Angle: %f \n", angle);//(castt.hitPoint.x == vertex.x && castt.hitPoint.y == vertex.y));
						{
							renderVertices.push_back(b2Vec3(vertex.x, vertex.y, an));

							//GLfloat dist = (distance > maxDistance) ? distance : maxDistance;

							castcall castL;
							angle += 0.00001f;

							b2Vec2 tp = pPoint - maxDistance * b2Vec2(sinf(an), cosf(an));

							world->RayCast(&castL, pPoint, tp);
							if (castL.isHit)//(distance*1.1f > castL.mfraction*maxDistance)
							{
								renderVertices.push_back(b2Vec3(castL.hitPoint.x, castL.hitPoint.y, an));
							}
							else if (!castL.isHit) //add point at maxDistance
							{
								renderVertices.push_back(b2Vec3(tp.x, tp.y, an));
								//renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
							}

							castcall castR;
							angle -= 0.00002f;
							b2Vec2 tpp = pPoint - maxDistance * b2Vec2(sinf(an), cosf(an));
							world->RayCast(&castR, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
							if (castR.isHit)
							{
								renderVertices.push_back(b2Vec3(castR.hitPoint.x, castR.hitPoint.y, an));
							}
							else if (!castR.isHit)//add point at maxDistance
							{
								renderVertices.push_back(b2Vec3(tpp.x, tpp.y, an));
								//renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
							}
						}
						else
						{
							renderVertices.push_back(b2Vec3(castt.hitPoint.x, castt.hitPoint.y, an));
						}
					}
				}
			}
			else if (shape->m_type == b2Shape::e_chain)
			{
				//b2ChainShape* chain = (b2ChainShape*)shape;
				//numberOfVertices = chain->GetChildCount();
				//b2EdgeShape* edge = new b2EdgeShape();
				//for (int i = numberOfVertices-1; i>=0; --i)
				//{
				//	printf("THE I: %i ", i);
				//	chain->GetChildEdge(edge, i);
				//	edge->m_vertex0;

				//	castcall castt;
				//	GLfloat angle = atan2(body->GetWorldPoint(edge->m_vertex0).x - pPoint.x, body->GetWorldPoint(edge->m_vertex0).y - pPoint.y);

				//	GLfloat distance = b2Distance(pPoint, body->GetWorldPoint(edge->m_vertex0));

				//	world->RayCast(&castt, pPoint, pPoint + 0.99f * distance * b2Vec2(sinf(angle), cosf(angle)));//0.999*body->GetWorldPoint(poly->GetVertex(u)) );

				//	//if (castt.isHit) g_debugDraw.DrawSegment(pPoint, castt.hitPoint, b2Color(0.f, 1.f, 0.f, 1.f));
				//	//g_debugDraw.DrawPoint( body->GetWorldPoint( poly->GetVertex(u) ), 5.f, b2Color(1.f, 0.f, 0.f, 1.f));
				//	b2Vec2 vertex = body->GetWorldPoint(edge->m_vertex0);

				//	//g_debugDraw.DrawPoint(castt.hitPoint, 3, b2Color(0.f, 0.f, 1.f));

				//	angle += b2_pi;
				//	//printf("Angle: %f \n", angle);

				//	if (!castt.isHit)// Only if the vertex is hit	//printf("Angle: %f \n", angle);//(castt.hitPoint.x == vertex.x && castt.hitPoint.y == vertex.y));
				//	{
				//		renderVertices.push_back(b2Vec3(vertex.x, vertex.y, angle));
				//	}
				//	else
				//	{
				//		renderVertices.push_back(b2Vec3(castt.hitPoint.x, castt.hitPoint.y, angle));
				//	}
				//}
			}
		}
	}

	// check for corners
	b2Vec2 tpp;
	GLfloat ang;
	//for (float i = -45.01f; i < 270.f; i += 90.f)
	//{
	//	castcall castC;
	//	ang = toRad(i) + b2_pi / 2.f;
	//	tpp = pPoint - maxDistance * b2Vec2(sinf(ang), cosf(ang));
	//	if (pPoint.x != tpp.x || pPoint.y != tpp.y)
	//	{
	//		world->RayCast(&castC, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
	//		if (!castC.isHit)//add point at maxDistance
	//		{
	//			renderVertices.push_back(b2Vec3(tpp.x, tpp.y, ang));
	//		}
	//	}
	//	//else
	//	//{
	//	//	renderVertices.push_back(b2Vec3(castC.hitPoint.x, castC.hitPoint.y, angle));
	//	//}
	//}
	GLfloat partAngle;
	GLuint partCount=4;
	//if (m_lightAngle <= 90.f) partCount=1;
	//else if (m_lightAngle <= 180.f) partCount=2;
	//else if (m_lightAngle <= 270.f) partCount = 3;
	//else partAngle = partCount=4;

	partAngle = abs(startAngle - endAngle) / partCount;

	for (unsigned int i = 0; i <= partCount; i++)
	{

		castcall castC;
		ang = startAngle + i*partAngle+toRad(m_angle);
		tpp = pPoint - maxDistance * b2Vec2(sinf(ang), cosf(ang));
		//printf("IIIIII: %f \n",ang);
		if (pPoint.x != tpp.x || pPoint.y != tpp.y)
		{
			world->RayCast(&castC, pPoint, tpp);//pPoint + maxDistance * b2Vec2(sinf(angle), cosf(angle)));
			if (!castC.isHit)//add point at maxDistance
			{
				renderVertices.push_back(b2Vec3(tpp.x, tpp.y, ang));
			}
		}
	}
	printf("Size:::%i\n", 222);
	//sort vertices
	std::sort(renderVertices.begin(), renderVertices.end(), SortVector);

	std::vector<b2Vec3>::iterator it = renderVertices.begin();
	std::vector<b2Vec3>::iterator itP;
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

	GLuint size = renderVertices.size();

	std::vector<b2Vec2> v3;
	v3.reserve(size + 1);
	v3.push_back(100 * pPoint);

	for (int i = 0; i < size; i++)
	{
		v3.push_back(b2Vec2(100 * renderVertices[i].x, 100 * renderVertices[i].y));
	}

	//if ((renderVertices[renderVertices.size() - 1].z - renderVertices[0].z) > b2_pi)
	//{
	v3.push_back(100 * b2Vec2(renderVertices[0].x, renderVertices[0].y));
	//}

	polyFan.initElement(&v3, Color4f(1.f, 1.f, 1.f, 1.f));
}

void SpotLight::renderLight()
{
	b2Vec2 rPos = 100 * renderPos + BaseObject::getWorldPos();


	glClear(GL_STENCIL_BUFFER_BIT);
	polyFan.render(BaseObject::getWorldPos());
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);


	glStencilFunc(GL_ALWAYS, 1, 1);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.1f);
	//glDisable(GL_TEXTURE_2D);
	// DRAW THE POLYGON
	polyFan.render(BaseObject::getWorldPos());



	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glStencilFunc(GL_EQUAL, 1, 1);
	lightTex.render(rPos.x, rPos.y, m_lightColor, scaleFactor, scaleFactor);
}
