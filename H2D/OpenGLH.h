#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include <stdio.h>
#include <string>

#define toAngle(rad) (rad*180)/(b2_pi) // rad = 2*pi*alpha/360
#define toRad(a) (a*b2_pi)/180 // rad = (a*2*b2_pi)/360 => rad*360=a*2*pi => a=



/*
	//////////////////// IMPORTANT ////////////////////
	"Syntax": 
	
	xxx_ph: Physic world Variables
	xxx_tm: Tilemap Variables
	xxx_r:	Render Variables
	xxx_w:	World Variables (_ph * 100)

*/