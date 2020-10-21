#include "GUILabel.h"


GUILabel::GUILabel(void)
{
}


GUILabel::~GUILabel(void)
{
}

bool GUILabel::create(Pos2D pos,Pos2D parentPosition,float w,float h,std::string *t,GLfloat fontSize,float r, float g, float b, float a)
{
	position=Rect(pos,RectSize(w,h));

	parentPos=parentPosition;

	mVAO=Square2D::initVAO(&position,20.f);

	text.initWrap(*t,fontSize,w,3.f);
	color.r=r;
	color.g=g;
	color.b=b;
	color.a=a;
	
	//textSize=(h/5)*4;
	//textY=(h/5)/7;
	//textX=textY;

	textSize=20;
	textY=5;
	textX=5;
	return true;
}

void GUILabel::render()
{
	//Render Squares
	/*Engine::borderPolyProgram.bind();
	Engine::borderPolyProgram.setColor(color.r,color.g,color.b,color.a);
	Square2D::render(mVAO,parentPos.x+position.x,parentPos.y+position.y,1.f,1.f,0.f,&color);*/

	// Buttonsize mit Font verändern, wenn kein Rect vorgegeben wird
	text.render(pos.x,pos.y);
	//Render Text
	//font->setTextColor(1.f,1.f,1.f,1.f);
	//font->renderText(parentPos.x+position.x+textX,parentPos.y+position.y+textY,title,textSize);
}