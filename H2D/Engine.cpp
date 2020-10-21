#include "Engine.h"
#include <gtx\transform.hpp>
#include <glm.hpp>

	GLfloat Engine::SCREEN_HEIGHT = 720.f;
	GLfloat Engine::SCREEN_WIDTH = 1270.f;
	bool Engine::FULLSCREEN = false;
	bool Engine::started = false;
	GLFWwindow* Engine::window = NULL;
	
	GLfloat Engine::mouse_x = 0.f;
	GLfloat Engine::mouse_y = 0.f;
	bool Engine::mouse_left=false;
	bool Engine::mouse_right=false;
	bool Engine::mouse_wheel_up=false;
	bool Engine::mouse_wheel_down=false;
	bool Engine::mouse_wheel_pressed=false;

	double Engine::mouseActiveLastTick;

	float Engine::scaleVX=1.f;
	float Engine::scaleVY=1.f;

	//Shader Programme
	TexturedPolygon2D Engine::textureProgram;
	FontProgram2D Engine::fontProgram;
	BorderPolygon2D Engine::borderPolyProgram;

Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}

GLfloat Engine::screenHeight()
{
	return SCREEN_HEIGHT;
}
GLfloat Engine::screenWidth()
{
	return SCREEN_WIDTH;
}
bool Engine::fullscreen()
{
	return FULLSCREEN;
}

void Engine::setScreenSize(short width,short height)
{
	
	glfwSetWindowSize(window,width,height);

	int w=0,h=0;

	glfwGetFramebufferSize(window,&w,&h);
	printf("Size: %i | %i \n",w,h);

	
	SCREEN_WIDTH=w;
	SCREEN_HEIGHT=h;

	scaleVX=1920/SCREEN_WIDTH;
	scaleVY=1080/SCREEN_HEIGHT;
	//printf("Screenthings changed %f | %f \n",scaleVX,scaleVY);
	//printf("Screenthings changed %f | %f \n",SCREEN_WIDTH,SCREEN_HEIGHT);

	updateShader();

}
void Engine::setFullscreen(bool x)
{
	//Does not work yet, might have to close Window and reopen it
	FULLSCREEN=x;
}

bool Engine::isStarted()
{
	return started;
}

GLFWwindow* Engine::getWindow()
{
	return window;
}

void Engine::createWindow()
{
	//window = glfwCreateWindow(1280,720,TITLE,glfwGetPrimaryMonitor(),NULL);
	window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Game 2013",NULL,NULL);
	//window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Game 2013",glfwGetPrimaryMonitor(),NULL);

	int w=0,h=0;
	glfwGetFramebufferSize(window,&w,&h);
		
	SCREEN_WIDTH=w;
	SCREEN_HEIGHT=h;

	scaleVX=1920/SCREEN_WIDTH;
	scaleVY=1080/SCREEN_HEIGHT;

	if(!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
		started = false;
	}
	started=true;
	printf("Initialized Window \n");
}

//Shader

void Engine::setTextureProgram()
{
	textureProgram.loadProgram();
	textureProgram.bind();

	textureProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,0.5f,1080.5f,-1.f,0.f));//(0.0f,SCREEN_WIDTH,0.0f,SCREEN_HEIGHT,1.f,-1.f));//Left 0 | Right Screen width | Bottom 0 | Top Screen height | 
	//texPro.setProjectionMatrix(glm::ortho<GLfloat>(0.0f,1920.f,1080.f,0.0f,1.f,-1.f));

	textureProgram.updateProjectionMatrix();
	textureProgram.setModelViewMatrix(glm::mat4());
	textureProgram.updateModelViewMatrix();
	textureProgram.setTextureColor(1.f,1.f,1.f,1.f);
	textureProgram.setTextureUnit(0);
}

void Engine::setFontProgram()
{
	fontProgram.loadProgram();
	fontProgram.bind();
	fontProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,0.5f,1080.5f,-1.f,0.f));
	fontProgram.updateProjectionMatrix();
	fontProgram.setModelViewMatrix(glm::mat4());
	fontProgram.updateModelViewMatrix();
	fontProgram.setTextColor(1.f,1.f,1.f,1.f);
	fontProgram.setTextureUnit(0);
}

void Engine::setBorderPolyProgram()
{
	borderPolyProgram.loadProgram();
	borderPolyProgram.bind();
	borderPolyProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	borderPolyProgram.updateProjectionMatrix();
	borderPolyProgram.setModelViewMatrix(glm::mat4());
	borderPolyProgram.updateModelViewMatrix();
	borderPolyProgram.setColor(1.f,1.f,1.f,1.f);
}

bool Engine::getMouseActive(float seconds)
{
		if((glfwGetTime()-mouseActiveLastTick)*1000>((double)seconds*1000))
		{
			return false;
		}
		else
		{
			return true;
		}

		
}

void Engine::setMouseActive()
{
	mouseActiveLastTick=glfwGetTime();
}

bool Engine::mouseHover(b2Vec2 objSizes,b2Vec2 sizes,float offsetX,float offsetY)
{

	objSizes.x=objSizes.x+offsetX;


	if(mouse_x>=objSizes.x && mouse_x <= (objSizes.x+sizes.x))
	{
		objSizes.y+=offsetY;
		if(mouse_y<=objSizes.y && mouse_y >= (objSizes.y-sizes.y))
		{
			return true;
		}
	}
	return false;
}

bool Engine::mouseHoverCenter(b2Vec2 center,b2Vec2 sizes,float offsetX,float offsetY)
{
	center.x+=offsetX;

	sizes.x/=2.f;

	if(mouse_x >= (center.x-sizes.x) && mouse_x <= (center.x+sizes.x))
	{
		center.y+=offsetY;
		sizes.y/=2.f;
		if(mouse_y<=(center.y+sizes.y) && mouse_y >= (center.y-sizes.y))
		{
			return true;
		}
	}

	return false;
}

bool Engine::mouseHover(Rect objSizes,float offsetX,float offsetY)
{

	objSizes.x=objSizes.x+offsetX;

	if(mouse_x>=objSizes.x && mouse_x <= (objSizes.x+objSizes.w))
	{
		objSizes.y+=offsetY;
		if(mouse_y>=objSizes.y && mouse_y <= (objSizes.y+objSizes.h))
		{
			return true;
		}
	}
	return false;
}

void Engine::setMousePos(Pos2D pos)
{
	//Engine::mouse_x=(pos.x+0.5f)*Engine::scaleVX;
	//Engine::mouse_y=(pos.y+0.5f)*Engine::scaleVY;

	glfwSetCursorPos(window,pos.x/Engine::scaleVX,pos.y/Engine::scaleVY);

	Engine::mouse_x=(pos.x+0.5f)*Engine::scaleVX;
	Engine::mouse_y=1080-(pos.y+0.5f)*Engine::scaleVY;

	//setMouseActive();
}

