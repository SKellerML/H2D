//#include "Game.h"

#define DEBUG

#include "VertexPos2D.h"
//#include "TexturedPolygon2D.h"
#include <gtx\transform.hpp>
#include <glm.hpp>
#include <exception>


//#include "Texture2D.h"
#include "SpriteSheet2D.h"
#include "Textobject.h"

#include "Font2D.h"
#include "Square2D.h"

#include "GUI_H.h"
#include "Engine.h"

#include "Element2D.h"
#include "Item.h"
// DevIL
#include <IL\il.h>
#include <IL\ilu.h>


#include <vector>

// TinyXML
#include "tinyxml2.h"
#include <boost\algorithm\string.hpp>
#include <set>
#include <map>
#include <list>

#include "StateManagement.h"
#include "ObjectList.h"

#include "InputMapper.h"

#include "ZTestState.h"

// TO LOAD
#include "Audio.h"
#include "Animation.h"
#include "SimpleParticleEmitter.h"

#include "Editor.h"


//FONT DEBUG STUFF

//Screen dimensions
Rect gScreenArea( 0.f, 0.f, 1280.f, 720.f);

//Loaded font
Font2D gFont;

//FBO
GLuint frameBuffer;
GLuint renderBuf;
GLuint texColorBuffer;
Texture2D scTexture;


std::shared_ptr<GameState> currentState = NULL;

int nextState=-1;
int nextStateInfo=-1;


// Constant Game Speed independent of Variable FPS
const int TICKS_PER_SECOND = 30;
const int SKIP_TICKS = 1000/TICKS_PER_SECOND;
int nextGameTick=0;
bool update=true;
float interpolation;

b2Vec2 WorldPosition;
bool isPaused=false;
bool wasPaused=false;

// Debug
#ifdef DEBUG

TickCounter frameTimer;

#endif


bool init()
{
	//Blend Func and Texturing
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	//glDepthFunc(GL_ALWAYS);


	glEnable(GL_LINE_STIPPLE);	// http://www.felixgers.de/teaching/jogl/stippledLines.html
	glEnable(GL_LINE_WIDTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor( 0.f, 0.f, 0.f, 1.f );


	//Initialize Shader programs
	Engine::setBorderPolyProgram();
	Engine::setFontProgram();
	Engine::setTextureProgram();

	Texture2D::setTexturedPolygonProgram2D(&Engine::textureProgram);

	Font2D::setFontProgram2D(&Engine::fontProgram);

	/*SOUNDS*/
	Sound::loadSoundSourcesFile("");

	
	GameState::setFont2D(&gFont);
	GUI::setFont(&gFont);
	FontObject::setFont2D(&gFont);
	Square2D::setBorderPolygon2D(&Engine::borderPolyProgram);
	gFont.loadBitmap("Graphics/fonttt.png");
	GUI::addSpriteSheet(&std::string("GUI_Sheet.png"));
	//currentState = new StateMenu();


	Element2D::loadElementProgram();
	
	// Init FBO
	
	glGenFramebuffers(1,&frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);

	scTexture.createScreenTexture(1920,1080);	
	
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,scTexture.getTextureID(),0);
	
	GLuint Frameerror=glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if(Frameerror!=GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Framebuffer is not complete! \n");			
	}

	

	//Renderbuf
	glGenRenderbuffers(1,&renderBuf);
	glBindRenderbuffer(GL_RENDERBUFFER,renderBuf);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL_INDEX,1920,1080);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_RENDERBUFFER,renderBuf);
	
	scTexture.changeScreenTextureSize();

	Engine::textureProgram.unbind();

	//glBindFramebuffer(GL_FRAMEBUFFER,0);
	glClearColor(0,0,0,1);
	
	GameState::init();
	GameState::loadDefaultKeys();
	GameState::saveKeys();

	//GameState::loadDefaultKeys();
	
	Animation::loadAnimations();	// Load all animation sheets

	SimpleParticleEmitter::loadParticleProgram();
	ComplexTexturedParticleEmitter::loadParticleProgram();
	ComplexPlainParticleEmitter::loadParticleProgram();

	ObjectList::loadObjectList();
	BaseObject::loadSheets();
	Item::loadItems();
	Entity::loadEntities();
	TileMap::loadTileMapBaseData();
	PointLight::initLightRendering();

	/*
	BaseObject::loadBaseObjectSpriteSheets();
	Ship::loadShipList();
	Entity::loadEntityList();
	Weapon::loadWeaponSprites();
	Missile::loadMissiles();
	Shield::loadShieldSprites(Ship::shieldFixture,Ship::shieldDeactivatedFixture);
	*/
	//currentState = new Level(0);//new Level(LEVELTYPE_TUTORIAL);

	//currentState = std::make_shared<Editor>();
	//currentState->init();
	setNextState(STATE_LEVEL1,0);
	return true;
}

float gameTime=0.f;
float actualTime=0.f;
float deltat=0.f;

void render()
{

	#ifdef DEBUG

	frameTimer.reset();

	#endif

	/*
		If window loses focus, stop rendering, Interpolation=0.f
	*/
	// Check for game Pause
	if(isPaused)
	{
		if(!wasPaused)
		{
			wasPaused=true;
			TickCounter::pauseTime();
		}
		printf("Paised!\n");
		return;
	}
	else if(wasPaused)
	{
		TickCounter::resumeTime();
		wasPaused=false;
	}
	TickCounter::updateEngineTime();


	changeState();


	actualTime=(float)glfwGetTime()*1000;
	deltat=actualTime-gameTime;
	//interpolation=SKIP_TICKS/(((float)glfwGetTime()*1000+SKIP_TICKS-nextGameTick)*1000);
	interpolation=(deltat/SKIP_TICKS);


	// Key Actions and Basic Update Stuff
	if(deltat > SKIP_TICKS)
	{
		nextGameTick+=SKIP_TICKS;
		//glfwSetTime(0.0);
		gameTime=(float)glfwGetTime()*1000;
		currentState->update();
		interpolation=0.f;
		update=true;
	}
	else	update=false;
	
	currentState->setInterpolation(interpolation);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Render Background
	setRenderingBuffer(1920,1080,frameBuffer);


			setRenderingBuffer(1920,1080,frameBuffer);

			Engine::textureProgram.bind();
			Engine::textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
			Engine::textureProgram.updateProjectionMatrix();
			
			Engine::fontProgram.bind();
			Engine::fontProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
			Engine::fontProgram.updateProjectionMatrix();

			// Bind, update and Render
			currentState->renderBackground();

			// Render Background to FBO 0
			setRenderingBuffer(Engine::screenWidth(),Engine::screenHeight(),0);

			glBindTexture(GL_TEXTURE_2D,scTexture.getTextureID());
			glGenerateMipmap(GL_TEXTURE_2D);
			scTexture.render(0,0);

	// Render Game to specialFBO
			setRenderingBuffer(1920,1080,frameBuffer);

			//glBindTexture(GL_TEXTURE_2D,scTexture.getTextureID());

			// Bind, update and Render

			Engine::textureProgram.bind();
			Engine::textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
			Engine::textureProgram.updateProjectionMatrix();
			
			Engine::fontProgram.bind();
			Engine::fontProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
			Engine::fontProgram.updateProjectionMatrix();

			// Render Game Area
			currentState->render();
	
			// Advanced Update Stuff (Pixel Hit Detection, Lightning)
			if(update)
			{
				currentState->updateRender();
			}

			// Final Render
			currentState->renderFinal();



	//Render FBO to FBO 0
	setRenderingBuffer(Engine::screenWidth(),Engine::screenHeight(),0);

	//Engine::textureProgram.bind();
	//Engine::textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,Engine::screenWidth()+.5f,0.5f,Engine::screenHeight()+.5f,-1.f,0.f));
	//Engine::textureProgram.updateProjectionMatrix();

	glBindTexture(GL_TEXTURE_2D,scTexture.getTextureID());
	glGenerateMipmap(GL_TEXTURE_2D);
	scTexture.render(0,0);



	if(update)
	{
		GameState::eatKeyActions();
	}

	calcFPS();
	
	#ifdef DEBUG

	//printf("Frametime: %f \n",frameTimer.getTime());

	#endif

	/*
		If paused - render sc Texture again and again until focus is gained again.
	*/
}

void exit()
{
	Entity::deleteEntities();
	glDeleteFramebuffers(1,&frameBuffer);
	glDeleteRenderbuffers(1,&renderBuf);
}

void setNextState(int state,int stateInfo)
{
	nextState = state;
	nextStateInfo=stateInfo;
}

void updateShader()
{
	//Engine::textureProgram.bind();
	//Engine::textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.0f,(GLfloat)Engine::screenWidth(),(GLfloat)Engine::screenHeight(),0.0f,1.f,-1.f));
	//Engine::textureProgram.updateProjectionMatrix();
	//glViewport(0.f,0.f,(GLfloat)Engine::screenWidth(),(GLfloat)Engine::screenHeight());
	

	//gFontProgram2D.setProjectionMatrix(glm::ortho<GLfloat>(0.0f,(GLfloat)Engine::screenWidth(),(GLfloat)Engine::screenHeight(),0.0f,1.f,-1.f));
	//gFontProgram2D.updateProjectionMatrix();
	scTexture.changeScreenTextureSize();
	printf("Screensize changed.\n");
}



void setRenderingBuffer(GLfloat sw,GLfloat sh,GLuint bufferID)
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
	glViewport(0,0,sw,sh);
	Engine::textureProgram.bind();
	Engine::textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,sw+0.5f,0.5f,sh+0.5f,1.f,-1.f));
	Engine::textureProgram.updateProjectionMatrix();

	Engine::textureProgram.setModelViewMatrix(glm::mat4());
	Engine::textureProgram.updateModelViewMatrix();

	return;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*

	[in]	window	The window that received the event.
	[in]	key	The keyboard key that was pressed or released.
	[in]	scancode	The system-specific scancode of the key.
	[in]	action	GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
	[in]	mods	Bit field describing which modifier keys were held down.

	*/

	GameState::keyHandleFunc(key,action);
}

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
	GameState::mouseHandleFunc(button,action);
}

void cursorpos_callback(GLFWwindow* window, double pos_x, double pos_y)
{
	Engine::mouse_x=(pos_x+0.5f)*Engine::scaleVX;
	Engine::mouse_y=1080-(pos_y+0.5f)*Engine::scaleVY;

	//printf("MousePos: %f || %f \n",Engine::mouse_x,Engine::mouse_y);

	Engine::setMouseActive();
}


bool anyKey = false;
bool k_space = false;
bool k_arrowUp = false;
bool k_arrowDown = false;
bool k_enter = false;

bool k_arrowRight = false;
bool k_arrowLeft = false;

bool k_released[255];
bool k_pressed[255];