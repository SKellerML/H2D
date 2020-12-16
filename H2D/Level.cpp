#include "Level.h"
#include "Rect.h"
#include "Game.h"
#include "Mask.h"

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

#include <Irrklang\irrKlang.h>

#define Pi 3.14159265359

//bool SortVector(b2Vec3 i, b2Vec3 j)	{ return (i.z < j.z) && (-b2_pi > (i.z - j.z) < b2_pi); }	// b2_pi > (i.z - j.z) < b2_pi;
//bool CompareVectorZ(b2Vec3 i, b2Vec3 j)	{ return (i.z == j.z); }

Level::Level(GLuint levelType)
{
	
	init(levelType);
}


Level::~Level(void)
{

}

void Level::init(GLuint levelType)
{
	BaseObject::initBaseObject(ObjectList::addObject);
	//BaseObject::setWorld(new b2World(b2Vec2(0.f, 0.f)));
	GameState::setHandler(HANDLER_GAME);

	loadLevel("example.txt");
	ObjectList::addObject(0, 0.64f * b2Vec2(4.f, 3.f), 0.f, 0);
	//p.init(0.64f * b2Vec2(2.0f,0.0f));
	//ObjectList::addObject(OBJECTTYPE_PERSON, 0.64f * b2Vec2(2.f, 0.f), 0.f, 1, 0);
	//ObjectList::addObject(OBJECTTYPE_CIVILIAN, 0.64f * b2Vec2(4.f, 2.f), 0.f, 1, 0);
	//ObjectList::addObject(OBJECTTYPE_GUARD, 0.64f * b2Vec2(2.f, 2.f), 0.f, 1, 0);
	player.init(0.64f * b2Vec2(0.0f, 5.0f));
	player.setObject( std::make_shared<Player>(player), 0);


	////pc1.init(0.64f * b2Vec2(4.f, 10.f),0.f,0);
	//ObjectList::addObject(OBJECTTYPE_POLICECAR, 0.64f * b2Vec2(4.f, 10.f), 0.f,1, 0);
	//ObjectList::addObject(OBJECTTYPE_MONEYPILE, 0.64f * b2Vec2(2.f, 2.f), 45.f, 0, 0);
	////ii.init(0.64f * b2Vec2(0.f, 4.f), 0.f, 0);
	//door = ObjectList::addObject(OBJECTTYPE_DOOR, 0.64f * b2Vec2(4.f, 3.f), 0.f,0, DOOR_UP);
	//ente.init(0.64f * b2Vec2(4.f, 3.f), 0);


	std::vector<b2Vec2> vert;
	vert.push_back(b2Vec2(-200.f, -200.f));
	vert.push_back(b2Vec2(200.f, -200.f));
	vert.push_back(b2Vec2(200.f, 200.f));
	vert.push_back(b2Vec2(-200.f, 200.f));
	elem.initElement(&vert, Color4f(1.f, 0.f, 0.f, 1.f));

	std::vector<b2Vec2> vertic;
	vertic.push_back(b2Vec2(200.f, 200.f));
	vertic.push_back(b2Vec2(400.f, 200.f));
	vertic.push_back(b2Vec2(400.f, 400.f));
	vertic.push_back(b2Vec2(200.f, 400.f));
	elemB.initElement(&vertic, Color4f(1.f, 0.f, 0.f, 1.f));

	tex.loadTextureFromFile32("BpihJnOCQAE4zt2.jpg");


	//tileProgram.setTextureUnit(0, 1, 2);


	testTexB.loadTextureFromFile32("TestTexB.png");
	testTexM.loadPixelsFromFile8("TestTexM.png");
	testTexM.loadTextureFromPixels8();
	TestTexF.loadTextureFromFile32("TestTexF.png");


	Mask::initMask();

	glGenTextures(1, &backRenderTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, backRenderTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	std::vector<b2Vec2> v;
	v.push_back(b2Vec2(0.f, 0.f));
	v.push_back(b2Vec2(0.f, 1080.f));
	v.push_back(b2Vec2(1920.f, 1080.f));
	v.push_back(b2Vec2(19200.f, 0.f));
	background.initElement(&v, Color4f(0.1f, 0.1f, 0.1f, 1.f));

	//testLight.createLight(p.body->GetPosition(),5.f,Color4f(1.f,1.f,1.f,1.f));
	/*
	WallTile ww;
	ww.init(64.0f * b2Vec2(3.f, 2.f),0);
	tm.changeTile(103, (TileObject*)&ww);
	*/
}



void Level::update()
{
	if (GameState::handler->isPressed(GameHandler::KEY_MENU))
	{
		printf("URGH");
		setNextState(STATE_EDITOR, 0);
	}

	//ente.update();

	if (GameState::handler->isPressedB(GameHandler::B_FIRE_PRIMARY))
	{
		GLuint tile = getTile(getTilePos(1.f / 100.f * b2Vec2(Engine::mouse_x - BaseObject::getWorldPos().x, Engine::mouse_y - BaseObject::getWorldPos().y)), sizeX);
		printf("Tile::: %i \n", tile);
		//tm[currentFloor].destroyWall(tile);
	}

	if (GameState::handler->isPressedS(GameHandler::KEY_RUN))
	{
		if (GameState::handler->isPressedS(GameHandler::KEY_S_DOWN))
		{
			setCurrentFloor(0);
			printf("DOWN\n");
		}
		if (GameState::handler->isPressedS(GameHandler::KEY_S_UP))
		{
			setCurrentFloor(1);
			printf("UP\n");
		}
	}
	BaseObject::updateWorld();
	//p.update();
	player.update();
	//pc1.update();
	//testLight.updateLight(p.getPosition(),0.f);
	ObjectList::deleteObjects();
	ObjectList::update(0);
	Mask::updateMask(player.body->GetPosition(),BaseObject::getWorld());

	//itemVector.push_back(std::move(player.useItem()));
}

void Level::renderBackground()
{
}


void Level::render()
{

	//Box
	//testTex.render(objX+5.f*interpolation,objY);
	//Bild
	//ground.render(0,0);
}

void Level::updateRender()
{
	//glBindTexture(GL_TEXTURE_2D, backRenderTexture);

	//// Give an empty image to OpenGL ( the last "0" )
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	//GLint color[4] = { 255, 255, 255, 255 };
	//glClearBufferiv(GL_COLOR, frameBuffer, color);
}

void Level::renderFinal()	
{	

	b2Vec2 wp = BaseObject::getWorldPos();
	//printf("WP: %f || %f \n", BaseObject::getWorldPos().x, BaseObject::getWorldPos().y);
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);	

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,backRenderTexture, 0);
	background.render();
	ObjectList::render(0);//tm[currentFloor].render();
	//ente.render();
	//SpriteSheet2D* s = BaseObject::getSpriteSheet(0);

	//for (int i = 0; i < sizeOverall; i++)
	//{
	//	b2Vec2 p = tileMap[i]->pos;
	//	s->renderFast(p);
	//}
	
	//tileProgram.setModelViewMatrix(glm::translate<GLfloat>(BaseObject::getWorldPos().x, BaseObject::getWorldPos().y, 0.f));
	//tileProgram.updateModelViewMatrix();


	//w[0].render();
	//w[1].render();
	//w[2].render();
	//w[3].render();
	
	//p.render();
	player.render();

	//objectContainer[currentFloor].render(0);

	Light::activateLightRendering();
	ObjectList::renderLights(0);
	Light::deactivateLightRendering();
	//glBindFramebuffer(GL_FRAMEBUFFER, backBuf);
	//glViewport(0, 0, 1920,1080);
	//// Background
	//w[0].render();
	//w[1].render();
	//w[2].render();
	//w[3].render();
	//p.render();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, scTexture.getTextureID(), 0);
	

	//// Foreground
	////tex.render(960.f, 540.f);


	//glBindFramebuffer(GL_FRAMEBUFFER, maskBuf);
	//glViewport(0, 0, 1920, 1080);

	//////p.render();

	////// Mask
	////maskP.bind();
	////elem.render();
	//
	//
	//elemB.render(b2Vec2(960.f,540.f));
	//////glBindTexture(GL_TEXTURE_2D, scTexture.getTextureID());
	//elem.render();
	//elemB.render(b2Vec2(960.f, 540.f));// );


	// Render to our framebuffer
	//glBindFramebuffer(GL_FRAMEBUFFER, maskBuf);
	////glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 2048, 2048, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
	//glClearBufferuiv(GL_COLOR, 0, &maskBuf);
	//glViewport(0, 0, 1920.f, 1080.f); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	////testTexB.render(960.f, 540.f);
	//elem.render(b2Vec2(BaseObject::getWorldPos().x, BaseObject::getWorldPos().y));
	//elemB.render(b2Vec2(960.f, 540.f));

	Mask::renderMask(BaseObject::getWorldPos(), backRenderTexture, TestTexF.getTextureID());

	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//
	//maskP.bind();
	//maskP.setModelViewMatrix(glm::translate<GLfloat>(960.f, 540.f, 0.f));//960.f+BaseObject::getWorldPos().x, 540.f+BaseObject::getWorldPos().y, 0.f));
	//maskP.updateModelViewMatrix();
	//glBindVertexArray(mVAOID);

	////glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, backRenderTexture);//scTexture.getTextureID() );

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, TestTexF.getTextureID());

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, /*testTexM*/renderedTexture);//maskTex.getTextureID());//maskTex


	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//

	//glActiveTexture(GL_TEXTURE2);
	//glDisable(GL_TEXTURE_2D);

	//glActiveTexture(GL_TEXTURE1);
	//glDisable(GL_TEXTURE_2D);

	//glActiveTexture(GL_TEXTURE0);
	//glDisable(GL_TEXTURE_2D);

	//GLuint Fre = glGetError();
	//if (Fre != GL_NO_ERROR)
	//{
	//	printf("Error Line of Sight \n");
	//}

	//glBindFramebuffer(GL_FRAMEBUFFER, maskBuf);
	//glViewport(0, 0, 1920, 1080);
	//p.render();

	// Mask
	//maskP.bind();
	//elem.render();
	//p.render();

	//tileProgram.setModelViewMatrix(glm::translate<GLfloat>(BaseObject::getWorldPos().x, BaseObject::getWorldPos().y, 0.f));
	//tileProgram.updateModelViewMatrix();
	//p.render();
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//testLight.renderLight(100.f * p.getPosition() + wp);
	Mask::debugRender();
	//Mask::renderMask();
	player.renderUI();

}

void Level::saveLevel()
{
	std::ofstream saveStream("example.txt", std::ios::out | std::ios::trunc);
	//myfile.open("example.txt");
	if (saveStream.is_open())
	{
		saveStream << "S\n" << std::to_string(sizeX) << "|" << std::to_string(sizeY) << '\n';
	}
	else // If it does not exist, create it
	{

	}
	saveStream.close();
}

void Level::loadLevel(const char* name)
{


	ObjectList::clearAllFloors();

	std::ifstream lvlStream("example.txt");
	std::string line;
	std::string ll[4];

	player.loadPlayer(&lvlStream);

	sizeX = 0;
	sizeY = 0;
	sizeOverall = 0;

	if (lvlStream.is_open())
	{
		
		getline(lvlStream, line);
		if (line.compare("S") == 0)
		{
			getline(lvlStream, line);
			int i = 0;
			std::stringstream ss(line);
			while (ss)
			{
				std::string s;
				if (!std::getline(ss, s, '|')) break;
				ll[i] = s;
				//std::cout << "Line: " << ll[i] << std::endl;
				++i;
				//printf("IIIIII\n");
			}
			sizeX = std::stoi(ll[0]);
			sizeY = std::stoi(ll[1]);
			sizeOverall = sizeX*sizeY;
			printf("SIZE: %i || %i \n", sizeX, std::stoi(ll[1]));
		}
	}

	getline(lvlStream, line);
	if (line.compare("MAP") == 0)
	{
		//printf("SKIP\n");
	}
	while (getline(lvlStream, line) && line == "M") // Read to N, from M
	{
		ObjectList::addFloor(&lvlStream, sizeX, sizeY);
	}
	ObjectList::setFloor(0);
	lvlStream.close();
}

void Level::setCurrentFloor(GLuint floor)
{
	ObjectList::setFloor(floor);
	//Person::changeFloor();
	player.reInit();
}
/*
boost::ptr_vector<pObject>* Level::getObjects()
{
	return &objects;
}
*/


//http://codeflow.org/entries/2012/aug/02/easy-wireframe-display-with-barycentric-coordinates/