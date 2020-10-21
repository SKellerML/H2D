#pragma once

#include "Texture2D.h"

class particleObject
{
public:
	particleObject(void);
	~particleObject(void);

	void init();
	void update();
	void render();

private:
	Texture2D tex;
	Rect position;
	GLfloat rotation;

};

