#include "Sound.h"
#include <iostream>

irrklang::ISoundEngine* Sound::engine=irrklang::createIrrKlangDevice();
std::vector<ISoundSource*> Sound::soundSources;
vec3df Sound::ListenerPosition=vec3df(0.f,0.f,0.f);
Sound::Sound(void)
{
	currentSound=NULL;
}


Sound::~Sound(void)
{
}

std::string Sound::filePath="GameData/Sounds/";

void Sound::addSound(std::string filename)
{
	filename.insert(0,filePath);
	soundSources.push_back(engine->addSoundSourceFromFile(filename.c_str(),ESM_NO_STREAMING,true));
	printf("Size: %i \n",soundSources.size());
}
void Sound::deleteSound(std::string filename)
{
	const char* x=(filePath+filename).c_str();
	engine->removeSoundSource(x);
}

ISound* Sound::playSound2D(GLuint soundSource, bool looped, bool killSound)
{
	if(currentSound!=NULL && !currentSound->isFinished() && !killSound)	return NULL;

	currentSound = engine->play2D(soundSources[soundSource], looped, false, true, true);

	return currentSound;
}
ISound* Sound::playSound3D(GLuint soundSource, b2Vec2 position, bool looped, bool killSound)
{
	if(currentSound!=NULL && !currentSound->isFinished() && !killSound)	return NULL;

	currentSound = engine->play3D(soundSources[soundSource], vec3df(position.x, position.y, 0.f), looped, false, false, true);

	return currentSound;
}
void Sound::stopSound()
{
	if(currentSound)	
	{
		//currentSound->stop();
		engine->stopAllSounds();
	}
}
void Sound::setPosition(b2Vec2 pos)
{
	currentSound->setPosition(vec3df(pos.x,pos.y,0.f));
}
void Sound::setPositionListener(vec3df pos,vec3df lookDirection)
{
	ListenerPosition=pos;
	engine->setListenerPosition(ListenerPosition,lookDirection);
	/*
	If you have an angle (A), in radians, in the range -Pi to Pi, then convert it to a vector (V) with:-
	V.x = cos(A)
	V.y = sin(A)
	(The inverse is A = atan2 ( V.y, V.x ) )

	//double dx=target.X-actor.X;
    //double dy=target.Y-actor.Y;
    //double angle=Atan2(dy, dx)*180/b2_pi;

	Sound::setPositionListener(irrklang::vec3df(position.x,position.y,0.f),irrklang::vec3df(cos(angle),sin(angle),0.f));
	*/
}

bool Sound::loadSoundSourcesFile(std::string filename)
{
	Sound::addSound("shot.wav");
	Sound::addSound("fly.wav");

	// xml File
	return true;
}

void Sound::debugSaveSoundSourcesFile()
{
	addSound("shot.wav");
	addSound("fly.wav");


	/*
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* bindings=doc.NewElement("SOUNDS");
	bindings->InsertEndChild(tinyxml2::createKeyElement(doc,"A","Hello"));

	doc.SaveFile("sound.xml");
	*/
}