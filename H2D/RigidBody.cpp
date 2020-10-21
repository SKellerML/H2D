#include "RigidBody.h"
#include "Game.h"

	/*

	//SpriteSheet2D RigidBody::charSpriteSheet;


RigidBody::RigidBody(void)
{
}


RigidBody::~RigidBody(void)
{
}


void RigidBody::setCharSpriteSheet()
{
	charSpriteSheet.loadTextureFromFile32("sheet_1.png");

}
void RigidBody::deleteCharSpriteSheet()
{

}

void RigidBody::loadChar()
{
	Rect x;
	x.x=0.f;
	x.y=0.f;
	x.w=32.f;
	x.h=64.f;
	part[0]=charSpriteSheet.addClipSprite(x);
	x.x=32.f;
	x.y=0.f;
	part[1]=charSpriteSheet.addClipSprite(x);
	x.x=0.f;
	x.y=64.f;
	part[2]=charSpriteSheet.addClipSprite(x);
	x.x=32.f;
	x.y=64.f;
	part[3]=charSpriteSheet.addClipSprite(x);
	x.x=0.f;
	x.y=128.f;
	part[4]=charSpriteSheet.addClipSprite(x);
	x.h=32.f;
	x.x=32.f;
	x.y=128.f;
	part[5]=charSpriteSheet.addClipSprite(x);
	
	testr=0.f;
}

void RigidBody::render(int x,int y)
{
	if(k_arrowUp)
	{
		testr+=5.f;
	}
	else if(k_arrowDown)
	{
		testr-=5.f;
	}

	charSpriteSheet.renderSprite(part[4],x-16,y-32);

	charSpriteSheet.renderSprite(part[5],x-16,y-40);

	charSpriteSheet.renderSprite(part[0],x-12,y-17,.5f,.5f,-2*testr,16,16);

	charSpriteSheet.renderSprite(part[1],x+12,y-17,.5f,.5f,2*testr,18,16);

	

	charSpriteSheet.renderSprite(part[2],x-8,y+20,1,1,-testr,22,9);

	charSpriteSheet.renderSprite(part[3],x+8,y+20,1,1,testr,11,9);

}
*/