#include "OpenGLH.h"

#include "Game.h"

#include "Engine.h"


#include "StateMenu.h"
#include "Level.h"

#include "StateManagement.h"

//Freetype
//#include <ft2build.h>
//#include FT_FREETYPE_H

//GLFWwindow* window;

void error_callback(int error, const char* description)
{
	printf(description,stderr);
}

void quitProgram()
{
	 glfwSetWindowShouldClose(Engine::getWindow(), GL_TRUE);
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	Engine::setScreenSize(Engine::screenWidth(),Engine::screenHeight());
	isPaused=false;
}

void windowMoveCallback(GLFWwindow* window, int xpos, int ypos)
{
	//glfwSetWindowPosCallback(window, window_pos_callback);
	render();

	int a=0,b=0;
	glfwGetFramebufferSize(Engine::getWindow(),&a,&b);
	//printf("Size: %i | %i \n",a,b);


	glfwSwapBuffers(Engine::getWindow());
	glfwPollEvents();
}

int main(void)
{
	//GLFWwindow* wind;
	int height, width;
	
	//Initialize GLFW
	glfwSetErrorCallback(error_callback);
	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
		return -1;
	}
	
	//wind = glfwCreateWindow(1280,720,"Space Invaders",NULL,NULL);
	Engine::createWindow();
	if(!Engine::getWindow())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
		return -1;
	}

	glfwMakeContextCurrent(Engine::getWindow());

	glfwSetKeyCallback(Engine::getWindow(), key_callback);
	glfwSetMouseButtonCallback(Engine::getWindow(),mousebutton_callback);
	glfwSetCursorPosCallback(Engine::getWindow(),cursorpos_callback);
	
	//Initialize GLEW
	GLenum GlewInitResult = glewInit();
	if(GLEW_OK != GlewInitResult)
	{
		printf("Error initializing GLEW\n");
		exit(EXIT_FAILURE);
	}

	//Blend Func and Texturing
	//glEnable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//siehe Game.cpp

	if(!Engine::isStarted())
	{
		return -1;
	}

	//Initialize Freetype
	//FT_Library ft;

	//if(FT_Init_FreeType(&ft))
	//{
		//fprintf(stderr,"Could not init freetype library\n");
	//}

	//Main Loop
	glfwGetFramebufferSize(Engine::getWindow(),&width,&height);
	//glViewport(0.f,0.f,width,height);
	glfwSetWindowSizeCallback(Engine::getWindow(),resizeCallback);

	//glfwSetWindowPosCallback(Engine::getWindow(), windowMoveCallback);



	init();
	//currentState = std::make_shared<Level>();
	glfwSwapInterval(1);
	//Main Loop
	while(!glfwWindowShouldClose(Engine::getWindow()))
	{
		render();

		int a=0,b=0;
		glfwGetFramebufferSize(Engine::getWindow(),&a,&b);
		//printf("Size: %i | %i \n",a,b);


		glfwSwapBuffers(Engine::getWindow());
		glfwPollEvents();
	}

	exit();
	
	glfwDestroyWindow(Engine::getWindow());
	glfwTerminate();
	//exit(EXIT_FAILURE);

	return 0;
}

/*	
	====TO DO LIST====
	- GUI
	- Mouse Callback
	- Key Callback in ne Klasse

	---PLANNED---
	- Rigged Bodies
	- Completely destructable environment


	====TO LEARN LIST====	
	- Callbacks - Für Physics Engine
	- Singleton
	
	
	====Physics Engine====
	- vllt.  DevIL based für Pixelated hit detection
	- Callback - Sobald ein Object mit einem anderen Kollidiert, callbacken


*/