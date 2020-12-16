#pragma once

#include "OpenGLH.h"
#include <Irrklang\irrKlang.h>
#include "tinyxml2.h"

#include <Box2D\Box2D.h>
#include <vector>

using namespace irrklang;

enum SoundFiles
{
	SOUND_LASER,
	SOUND_FLY,
	SOUND_LAST,
};

class Sound // private sound class
{
public:
	Sound(void);
	~Sound(void);

	ISound* playSound2D(GLuint soundSource, bool looped = false, bool killSound = false);
	ISound* playSound3D(GLuint soundSource, b2Vec2 position, bool looped = false, bool killSound=false);
	
	void stopSound();
	
	void setPosition(b2Vec2 pos);
	static void setPositionListener(vec3df pos,vec3df lookDirection);


	static bool loadSoundSourcesFile(std::string filename);
	static void debugSaveSoundSourcesFile();

	static void addSound(std::string filename);
	static void deleteSound(std::string filename);

private:
	static ISoundEngine* engine;
	static std::string filePath;
	static vec3df ListenerPosition;


	ISound* currentSound;

	static std::vector<ISoundSource*> soundSources;
	//std::vector<ISoundSource*> soundSourcesExtra;
};

