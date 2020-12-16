#pragma once

#include "OpenGLH.h"
#include "Texture2D.h"
#include "LightProgram.h"
#include "Element2D.h"
#include "BaseObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

class Light
{
public:
	static Texture2D backgroundLight;
	static Texture2D lightTex;
	static GLuint lightMaskBuf;
	static GLuint lightTextureID;

	static void initLightRendering();
	static void activateLightRendering();
	static void deactivateLightRendering();
};

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();

	void createLight(b2Vec2 pos, GLfloat radius,Color4f lightColor, b2Vec2 rotationOffset = b2Vec2(0.f,0.f));
	void updateLight(b2Vec2 pos, GLfloat angle);
	void renderLight();

private:
	b2Vec2 m_pos;
	GLfloat radius;
	GLfloat scaleFactor;

	b2Vec2 rOffset;
	GLfloat m_angle;
	b2Vec2 renderPos;
	Color4f m_lightColor;
	ElementPolygon polyFan;

};

class SpotLight : public Light
{
public:
	SpotLight();
	~SpotLight();

	void createLight(b2Vec2 pos, GLfloat lightAngle, GLfloat radius, Color4f lightColor, b2Vec2 rotationOffset = b2Vec2(0.f, 0.f));
	void updateLight(b2Vec2 pos, GLfloat lightAngle, GLfloat angle);
	void renderLight();

private:
	b2Vec2 m_pos;
	GLfloat radius;
	GLfloat scaleFactor;

	b2Vec2 rOffset;
	GLfloat m_angle;
	b2Vec2 renderPos;
	Color4f m_lightColor;
	ElementPolygon polyFan;

	GLfloat m_lightAngle;
};
