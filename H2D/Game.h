#pragma once

#include "OpenGLH.h"

#include <Box2D\Box2D.h>

bool init();

void render();

void exit();

void quitProgram();	// Definition in Main

void resizeCallback(GLFWwindow* window, int width, int height); // Definition in Main

void updateShader();

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);

void cursorpos_callback(GLFWwindow* window, double pos_x, double pos_y);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

double calcFPS(double timeInterval = 1.0, std::string windowTitle = "NONE");

void setRenderingBuffer(GLfloat sw,GLfloat sh,GLuint bufferID);

// NextState
extern int nextState;
extern int nextStateInfo;


extern b2Vec2 WorldPosition;

extern bool wasPaused;
extern bool isPaused;


extern GLuint frameBuffer;


//Keys
extern bool anyKey;
extern bool k_space;
extern bool k_arrowUp;
extern bool k_arrowDown;
extern bool k_enter;

extern bool k_arrowRight;
extern bool k_arrowLeft;

extern bool k_released[255];
extern bool k_pressed[255];


// 
extern const int TICKS_PER_SECOND;
