#pragma once

#include "OpenGLH.h"
#include "Font2D.h"
#include "Game.h"

#include "TexturedPolygon2D.h"
#include "FontProgram2D.h"
#include "BorderPolygon2D.h"

#include <Box2D\Box2D.h>
/*
	Klasse für rein statische Funktionen
	Vllt. Singleton benutzen
*/
class Engine
{
public:
	Engine(void);
	~Engine(void);

	static GLfloat screenHeight();
	static GLfloat screenWidth();
	static bool fullscreen();

	static void setScreenSize(short width,short height);
	static void setFullscreen(bool x);
	static bool isStarted();

	static GLFWwindow* getWindow();
	static void createWindow();

	//Public Felder / Shader Programme

	static void setTextureProgram();
	static void setFontProgram();
	static void setBorderPolyProgram();

	static TexturedPolygon2D textureProgram;
	static FontProgram2D fontProgram;
	static BorderPolygon2D borderPolyProgram;

	
	static float scaleVX,scaleVY;

	// Mouse Stuff
	static GLfloat mouse_x,mouse_y;
	static bool mouse_left,mouse_right;

	
	static bool getMouseActive(float seconds);
	static void setMouseActive();
	static bool mouse_wheel_up,mouse_wheel_down,mouse_wheel_pressed;

	static bool mouseHoverCenter(b2Vec2 center,b2Vec2 sizes,float offsetX=0.f,float offsetY=0.f);
	static bool mouseHover(b2Vec2 upperLeft,b2Vec2 sizes,float offsetX=0.f,float offsetY=0.f);
	static bool mouseHover(Rect objSizes,float offsetX=0.f,float offsetY=0.f);

	static void setMousePos(Pos2D pos);

private:
	static GLfloat SCREEN_HEIGHT;
	static GLfloat SCREEN_WIDTH;
	static bool FULLSCREEN;
	//static String TITLE;
	static bool started;
	static GLFWwindow* window;

	static double mouseActiveLastTick;
};

