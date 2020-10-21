#pragma once

#include "OpenGLH.h"
#include <Box2D\Box2D.h>

struct Pos2D
{
	Pos2D(GLfloat _x,GLfloat _y) : x(_x),y(_y) {}
	Pos2D() {}
	
	GLfloat x;
	GLfloat y;

};

struct RectSize
{
	RectSize(GLfloat _w,GLfloat _h) : w(_w),h(_h) {}
	RectSize() {}

	GLfloat w;
	GLfloat h;
};

struct Rect
{
	Rect(GLfloat _x,GLfloat _y,GLfloat _w,GLfloat _h) : x(_x),y(_y),w(_w),h(_h) {}
	Rect(Pos2D pos,RectSize size) : x(pos.x),y(pos.y),w(size.w),h(size.h) {}
	Rect(b2Vec2 pos,RectSize size) : x(pos.x),y(pos.y),w(size.w),h(size.h) {}
	Rect() {}

	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
};

struct RectVAO
{
	Rect r;
	GLuint fVAO;
};

struct Color4f
{
	Color4f(GLfloat _r,GLfloat _g,GLfloat _b,GLfloat _a) : r(_r), g(_g), b(_b), a(_a) {}
	Color4f() : r(1.f),g(1.f),b(1.f),a(1.f) {}

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

struct OBB
{
	OBB() : x(0.f),y(0.f),hw(0.f),hh(0.f),r(0.f) {}
	OBB(GLfloat _x,GLfloat _y,GLfloat width,GLfloat height,GLfloat _r=0.f) : x(_x),y(_y),hw(width/2),hh(height/2),r(_r) {}
	OBB(Pos2D pos,RectSize size,GLfloat _r=0.f) : x(pos.x),y(pos.y),hw(size.w/2),hh(size.h/2),r(_r) {}

	GLfloat x;	// Central point x
	GLfloat y;	// Central point y
	GLfloat hw;// half width
	GLfloat hh;// half height
	GLfloat r;// rotation?
};



/*
	Note: Structs are just like classes and can have a constructor
	Foo(int value) : a(value) {}
*/