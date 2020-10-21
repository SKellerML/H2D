#include "Editor.h"

#include <fstream>
#include <ostream>
#include <sstream>


Editor::Editor(GLuint levelType)
{
	init(levelType);
}


Editor::~Editor()
{

}

void Editor::init(GLuint levelType)
{
	BaseObject::initBaseObject(ObjectList::addObject);
	//BaseObject::setWorld(new b2World(b2Vec2(0.f, 0.f)));
	GameState::setHandler(HANDLER_GUI);

	std::vector<b2Vec2> vert;
	vert.push_back(b2Vec2(-200.f, -200.f));
	vert.push_back(b2Vec2(200.f, -200.f));
	vert.push_back(b2Vec2(200.f, 200.f));
	vert.push_back(b2Vec2(-200.f, 200.f));
	elem.initElement(&vert, Color4f(1.f, 0.f, 0.f, 1.f));

	std::vector<b2Vec2> vertic;
	vertic.push_back(b2Vec2(200.f, 200.f));
	vertic.push_back(b2Vec2(400.f, 200.f));
	vertic.push_back(b2Vec2(400.f, 400.f));
	vertic.push_back(b2Vec2(200.f, 400.f));
	elemB.initElement(&vertic, Color4f(1.f, 0.f, 0.f, 1.f));

	tex.loadTextureFromFile32("BpihJnOCQAE4zt2.jpg");



	//tileProgram.setTextureUnit(0, 1, 2);


	testTexB.loadTextureFromFile32("TestTexB.png");
	testTexM.loadPixelsFromFile8("TestTexM.png");
	testTexM.loadTextureFromPixels8();
	TestTexF.loadTextureFromFile32("TestTexF.png");


	//Mask::initMask();

	glGenTextures(1, &backRenderTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, backRenderTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	sizeX = 50;
	sizeY = 50;
	//tm.create(sizeX, sizeY, 75);
	//loadLevel("example.txt");
	loadEmptyLevel(3);

	std::vector<b2Vec2> v;
	v.push_back(b2Vec2(0.f, 0.f));
	v.push_back(b2Vec2(0.f, 1080.f));
	v.push_back(b2Vec2(1920.f, 1080.f));
	v.push_back(b2Vec2(19200.f, 0.f));
	background.initElement(&v, Color4f(0.1f, 0.1f, 0.1f, 1.f));

	std::vector<b2Vec2> square;
	GLfloat twH = TILE_WIDTH / 2;
	square.push_back(b2Vec2(-twH, -twH));
	square.push_back(b2Vec2(twH, -twH));
	square.push_back(b2Vec2(twH, twH));
	square.push_back(b2Vec2(-twH, twH));

	currentTileRenderSquare.initElement(&square, Color4f(0.f, 1.f, 0.f, 0.5f));
	BaseObject::setWorldPos(b2Vec2(0.f,0.f));//b2Vec2(-960.f,-540.f));	
	
	// UI
	std::vector<b2Vec2> uibg;
	uibg.push_back(b2Vec2(1500.f, 0.f));
	uibg.push_back(b2Vec2(1920.f, 0.f));
	uibg.push_back(b2Vec2(1920.f, 1080.f));
	uibg.push_back(b2Vec2(1500.f, 10800.f));
	uiBackground.initElement(&uibg, Color4f(0.5f, 0.5f, 0.5f, 0.8f));

	btn_save.create("Save",4,Color4f(1.f,1.f,1.f,1.f),Color4f(0.f,0.f,0.f,1.f),b2Vec2(1610.f,120.f));
	btn_save.setBackground(Color4f(0.f, 0.f, 0.f, 1.f), Color4f(1.f, 1.f, 1.f, 1.f));
	btn_clear.create("Play", 5, Color4f(1.f, 1.f, 1.f, 1.f), Color4f(0.f, 0.f, 0.f, 1.f), b2Vec2(1610, 40.f));
	btn_clear.setBackground(Color4f(0.f, 0.f, 0.f, 1.f), Color4f(1.f, 1.f, 1.f, 1.f));
	btn_load.create("Load", 6, Color4f(1.f, 1.f, 1.f, 1.f), Color4f(0.f, 0.f, 0.f, 1.f), b2Vec2(1610, 80.f));
	btn_load.setBackground(Color4f(0.f, 0.f, 0.f, 1.f), Color4f(1.f, 1.f, 1.f, 1.f));

	floorText.init("Floor: " + std::to_string(currentFloor) + std::string("/") + std::to_string(tm.size()-1), 30, 1.f);

	// Setup
	setupPanel.create(&std::string("Editor"), Pos2D(960.f, 540.f));
	setupPanel.addButton(Pos2D(150.f, 150.f), "Empty", 3, true);
	setupPanel.addButton(Pos2D(150.f, 200.f), "Load", 4, true);
	setupPanel.addTextfield(b2Vec2(10.f, 10.f));
	setupPanel.setVisible(true);

	setupPanelActive = true;
}



void Editor::update()
{
	
	if (setupPanelActive)
	{
		GLuint panelRV = setupPanel.update();

		if (panelRV != -1)
		{
			printf("RVVV: %i \n", panelRV);
			if (panelRV == 3)
			{
				setupPanel.setVisible(false);
			}
			else if (panelRV == 4)
			{
				loadLevel("example.txt");
				setupPanel.setVisible(false);
			}
			setupPanelActive = false;
			GameState::setHandler(HANDLER_EDITOR);
		}
	}
	else
	{

		//BaseObject::updateWorld();
		b2Vec2 mousePos(Engine::mouse_x, Engine::mouse_y);

		if (mousePos.x > 1500)
		{
			isInGUI = true;

			if (btn_clear.update() != -1)
			{
				setNextState(STATE_LEVEL1, 0);
			}
			if (btn_load.update() != -1)
			{
				loadLevel("example.txt");
				//tm.loadTileMap();
			}
			if (btn_save.update() != -1)
			{
				saveLevel();
				//tm.saveTileMap();
			}
		}
		else if (isInGUI)
		{
			isInGUI = false;
		}
		else
		{


			// move screen area

			GLfloat maxVel = 20.f;
			GLfloat maxVelD = sqrt(maxVel);

			b2Vec2 posChange = b2Vec2(0.f, 0.f);

			// speed modifier with shift
			if (GameState::handler->isPressedS(EditorHandler::KEY_S_SPEEDUP))	maxVel *= 2;

			if (GameState::handler->isPressedS(EditorHandler::KEY_S_UP))
			{
				posChange.y -= maxVel;
			}
			if (GameState::handler->isPressedS(EditorHandler::KEY_S_DOWN))
			{
				posChange.y += maxVel;
			}
			if (GameState::handler->isPressedS(EditorHandler::KEY_S_LEFT))
			{
				posChange.x += maxVel;
			}
			if (GameState::handler->isPressedS(EditorHandler::KEY_S_RIGHT))
			{
				posChange.x -= maxVel;
			}

			b2Vec2 wp = BaseObject::getWorldPos() + posChange;
			//wp *= -100.f;
			BaseObject::setWorldPos(wp);
			// Get Tile under mouse and set render Pos

			mousePos = mousePos - wp;
			b2Vec2 tilePos = getTilePos(1.f / 100.f *mousePos);
			GLuint tile = getTile(tilePos, sizeX);
			printf("Tile: %i \n", tile);
			currentTileRenderPos = TILE_WIDTH* tilePos;//getPos(tile, sizeX);


			// Set Tiles with mouseclicks
			if (GameState::handler->isPressedBS(EditorHandler::B_FIRE_PRIMARY))
			{
				//printf("Fire! \n");
				TileObject wt;
				wt.init(TILE_WIDTH * tilePos, 1);
				tm[currentFloor].changeTile(tile, wt);
			}
			if (GameState::handler->isPressedBS(EditorHandler::B_FIRE_SECONDARY))
			{
				//printf("Fire! \n");
				TileObject wt;
				wt.init(TILE_WIDTH * tilePos, 0);
				tm[currentFloor].changeTile(tile, wt);
			}
		}

		if (GameState::handler->isPressed(EditorHandler::KEY_FLOOR_UP))
		{
			if (tm.size() - 1 > currentFloor)
			{
				setCurrentFloor(++currentFloor);
				printf("EEEEEEEEEEEEEEEEEE %i \n", currentFloor);
			}
		}
		else if (GameState::handler->isPressed(EditorHandler::KEY_FLOOR_DOWN))
		{
			if (0 < currentFloor)
			{
				setCurrentFloor(--currentFloor);
				printf("VVVVVVVVVVVVVVVVVVV %i \n", currentFloor);
			}
		}
	}
}

void Editor::renderBackground()
{
}


void Editor::render()
{
	//Box
	//testTex.render(objX+5.f*interpolation,objY);
	//Bild
	//ground.render(0,0);
}

void Editor::updateRender()
{
	//glBindTexture(GL_TEXTURE_2D, backRenderTexture);

	//// Give an empty image to OpenGL ( the last "0" )
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	//GLint color[4] = { 255, 255, 255, 255 };
	//glClearBufferiv(GL_COLOR, frameBuffer, color);
}

void Editor::renderFinal()
{
	b2Vec2 wp = BaseObject::getWorldPos();

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, backRenderTexture, 0);
	background.render();
	tm[currentFloor].render();

	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, scTexture.getTextureID(), 0);


	//Mask::renderMask(BaseObject::getWorldPos(), backRenderTexture, TestTexF.getTextureID());

	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	currentTileRenderSquare.render(currentTileRenderPos+wp);


	uiBackground.render();
	btn_clear.render();
	btn_load.render();
	btn_save.render();

	setupPanel.render();

	floorText.render(1550.f, 1000.f);
}


void Editor::saveLevel()
{
	std::ofstream saveStream("example.txt", std::ios::out | std::ios::trunc);
	//myfile.open("example.txt");
	if (saveStream.is_open())
	{

		saveStream << "S\n" << std::to_string(sizeX) << "|" << std::to_string(sizeY) << '\n';
		saveStream << "MAP\n";

		for (std::vector<TileMap>::iterator it = tm.begin(); it != tm.end(); ++it)
		{
			saveStream << "M\n";
			it->saveTileMap(saveStream);
			saveStream << "N\n";
		}
	}
	else // If it does not exist, create it
	{

	}
	saveStream.close();
}

void Editor::loadLevel(const char* name)
{
	tm.clear();
	std::ifstream lvlStream("example.txt");
	std::string line;
	std::string ll[3];

	sizeX = 0;
	sizeY = 0;
	sizeOverall = 0;

	if (lvlStream.is_open())
	{

		getline(lvlStream, line);
		if (line.compare("S") == 0)
		{
			getline(lvlStream, line);
			int i = 0;
			std::stringstream ss(line);
			while (ss)
			{
				std::string s;
				if (!std::getline(ss, s, '|')) break;
				ll[i] = s;
				//std::cout << "Line: " << ll[i] << std::endl;
				++i;
				//printf("IIIIII\n");
			}
			sizeX = std::stoi(ll[0]);
			sizeY = std::stoi(ll[1]);
			sizeOverall = sizeX*sizeY;
			printf("SIZE: %i || %i \n", sizeX, std::stoi(ll[1]));
		}
	}

	getline(lvlStream, line);
	if (line.compare("MAP") == 0)
	{
		//printf("SKIP\n");
	}
	while (getline(lvlStream, line) && line == "M") // Read to N, from M
	{
		printf("FUCKFUCKFUCK\n");
		tm.push_back(TileMap(&lvlStream, sizeX, sizeY));
	}

	setCurrentFloor(0);
	lvlStream.close();
}

void Editor::setCurrentFloor(GLuint floor)
{
	currentFloor = floor;
	floorText.updateText("Floor: " + std::to_string(currentFloor) + std::string("/") + std::to_string(tm.size()-1));
	tm[currentFloor].setTileMaps();
}

void Editor::loadEmptyLevel(int numberOfFloors)
{
	tm.clear();
	for (int i = numberOfFloors-1; i>=0; --i)
	{
		printf("Empty Level! %i \n",i);
		tm.push_back(TileMap(NULL, sizeX, sizeY));
	}
	currentFloor = 0;
}