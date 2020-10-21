//#include "StateMenu.h"
//
//
//StateMenu::StateMenu(void)
//{
//	selected=0;
//
//	background.loadTextureFromFile32("mainMenu.png");
//
//
//	GUIButtonTextOnly *b1=new GUIButtonTextOnly;
//	b1->create("Start New Game",0,Color4f(1.f,1.f,1.f,1.f),Color4f(0.5f,0.5f,0.5f,0.5f),Pos2D(150.f,150.f),0.f,0.f,70,RectSize(450.f,100.f));
//	//Rect(150.f,150.f,450.f,130.f),0.f,0.f,"Start Game",1,Color4f(1.f,1.f,1.f,1.f),25.f);
//	buttons.push_back(b1);
//
//	GUIButtonTextOnly *b2=new GUIButtonTextOnly;
//	b2->create("Continue",1,Color4f(1.f,1.f,1.f,1.f),Color4f(0.5f,0.5f,0.5f,0.5f),Pos2D(150.f,250.f),0.f,0.f,70,RectSize(450.f,100.f));
//	buttons.push_back(b2);
//
//	GUIButtonTextOnly *b3=new GUIButtonTextOnly;
//	b3->create("Quit",2,Color4f(1.f,1.f,1.f,1.f),Color4f(0.5f,0.5f,0.5f,0.5f),Pos2D(150.f,850.f),0.f,0.f,70,RectSize(450.f,100.f));
//	buttons.push_back(b3);
//
//	std::string x="Test";
//
//	panel.create(&x,Pos2D(960.f-576.f/2.f,540.f-448.f/2.f));
//
//	panel.addSlider(Pos2D(50.f,50.f),250.f,0.f,100.f,5);
//
//	panel.addTextfield(Pos2D(50.f,150.f));
//	panel.addTextfield(Pos2D(50.f,200.f));
//
//	panel.addDropdownList(Pos2D(232.f,250.f),"Woha",0);
//	panel.addObjectDropdownList(0,"This really",1);
//	panel.addObjectDropdownList(0,"Works",2);
//
//	panel.addButton(Pos2D(32.f,400.f),"Start",0,true);
//	panel.addButton(Pos2D(132.f,400.f),"End",1,true);
//
//	panel.addDropdownList(Pos2D(232.f,400.f),"1920x1080",0);
//	panel.addObjectDropdownList(1,"1280x720",1);
//	panel.addObjectDropdownList(1,"600x400",2);
//
//
//
//	std::string st="Hallo ihr da draußen, die ist nur ein Test, um eure Fähigkeiten als Buchstabe zu testen, dieser Satz ergibt keinen Sinn und eig. will ich damit auch nur etwas testen und brauche einen langen text.";
//	panel.addLabel(Pos2D(20.f,20.f),RectSize(150.f,150.f),&st);
//
//
//
//	testButt.create("Hallo",-309,Color4f(0.f,0.f,0.f,0.f),Color4f(0.f,0.f,1.f,1.f),Pos2D(600.f,600.f));
//
//
//	//saveKeys();
//
//	/*
//	GUIButtonTextOnly b2;
//	b2.setFontSizeMax(50.f);
//	b2.createJustText(Rect(150.f,250.f,450.f,130.f),0.f,0.f,"Continue",1,Color4f(1.f,1.f,1.f,1.f),25.f);
//	buttons.push_back(b2);
//
//	GUIButtonTextOnly b3;
//	b3.setFontSizeMax(50.f);
//	b3.createJustText(Rect(150.f,450.f,450.f,130.f),0.f,0.f,"Options",1,Color4f(1.f,1.f,1.f,1.f),25.f);
//	buttons.push_back(b3);
//
//	GUIButtonTextOnly b4;
//	b4.setFontSizeMax(50.f);
//	b4.createJustText(Rect(150.f,650.f,450.f,130.f),0.f,0.f,"Quit",1,Color4f(1.f,1.f,1.f,1.f),25.f);
//	buttons.push_back(b4);
//	*/
//	selected=0;
//	setHandler(HANDLER_GUI);
//	panel.setVisible(true);
//
//	//GameState::saveKeys();
//}
//
//
//StateMenu::~StateMenu(void)
//{
//}
//
//void StateMenu::update()
//{
//	/*
//	if(anyKey)
//	{
//		setNextState(STATE_LEVEL1);
//	}
//	*/
//	/*
//	if(anyKey && Engine::screenWidth() == 1024)
//	{
//		Engine::setScreenSize(1920,1080);
//	}
//	*/
//}
//
//void StateMenu::renderBackground()
//{
//	background.render(0.f,0.f);
//}
//
//void StateMenu::render()
//{
//	
//}
//
//void StateMenu::updateRender()
//{
//	int selected_now;
//
//	// Panel is first in order
//	
//	if(panel.isVisible())
//	{
//		panel.update();
//		return;
//	}
//
//	// If mouse hovers over the panel, stop updating anything else and set Keyhandler to GUIHandler, comprende?
//
//	if(Engine::getMouseActive(0.5f))
//	{
//		for(int i=(buttons.size()-1);i>=0;i--)
//		{
//			if((selected_now=buttons[i].update())!=-1)
//			{
//				selected=selected_now;
//			}
//		}
//	}
//	else
//	{	
//		if(handler->isPressed(GUIHandler::KEY_NEXT_ELEMENT))
//		{
//			if(selected+1<buttons.size())
//			{
//				selected+=1;
//			}
//		}
//		else if(handler->isPressed(GUIHandler::KEY_PREVIOUS_ELEMENT))
//		{
//			if(selected-1>=0)
//			{
//				selected-=1;
//			}
//		}
//	}
//
//		for(int i=(buttons.size()-1);i>=0;i--)
//		{
//			if(selected==i)
//			{
//				buttons[i].setSelected(true);
//			}
//			else
//			{
//				buttons[i].setSelected(false);
//			}
//		}
//
//	if(handler->isPressed(GUIHandler::KEY_CONFIRM) || (handler->isPressedB(GUIHandler::B_CONFIRM) && buttons[selected].isHovered()))
//	{
//		// Do stuff that should happen with the pressed button, best with a switch, in panel just return the rv
//		switch(selected)
//		{
//		case 0:	setNextState(STATE_LEVEL1);
//			break;
//		case 1:	setNextState(STATE_LEVEL1);
//			break;
//		case 2: setNextState(STATE_EXIT);
//			break;
//		default:
//			break;
//		}
//	}
//
//	/*
//	// Check if something is selected via keyboard or controller, but only if the mouse is inactive for 1 second
//	if(!Engine::getMouseActive(1))
//	{
//		// Wenn Maus inaktiv, Tastenbefehle übernehmen lassen
//		if(handler->isPressed(GUIHandler::KEY_NEXT_ELEMENT))
//		{
//			if(selected<=0)
//			{
//				selected-=1;
//			}
//		}
//		else if(k_arrowDown)
//		{
//			if(selected<buttons.size())
//			selected+=1;
//		}
//		//printf("%i \n",selected);
//	}
//	else
//	{
//		selected=-1;
//	}
//	
//	
//	/*
//	if(handler.isPressed(GUIHandler::KEY_CONFIRM))
//	{
//		printf("Hello O__O\n It works O__O\n Yeah");
//	}
//	*/
//	/*
//	if(buttons[0].update()!=-1)
//	{
//		
//	}
//	if(buttons[1].update()!=-1)
//	{
//
//	}
//	if(buttons[2].update()!=-1)
//	{
//
//	}
//	if(buttons[3].update()!=-1)
//	{
//		quitProgram();
//	}
//	*/
//}
//
//void StateMenu::renderFinal()	
//{
//	for(int i=(buttons.size()-1);i>=0;i--)
//	{
//		buttons[i].render();
//	}
//	panel.render();
//
//}