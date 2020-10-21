#pragma once

#include "OpenGLH.h"
#include "Sound.h"
//#include "Music.h"

#include <map>
#include <irrKlang.h>

#include <boost\shared_ptr.hpp>
#include <boost\ptr_container\ptr_vector.hpp>
//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

// Alternatives: PortAudio, SFML(not really)


class Audio
{
public:
	Audio(void);
	~Audio(void);

	static ISound* playSound(ik_c8* filename);
	static void playSoundLooped(ik_c8* filename);
	static void playMusic(ik_c8* filename,bool killCurrentMusic=false);

	static void addSound(ik_c8* filename);
	static void deleteSound(ik_c8* filename);

	static void pauseMusic();
	static void resumeMusic();

	static void pauseSounds();
	static void resumeSouns();

	static void stopSounds();
	static void stopMusic();

private:
	static irrklang::ISoundEngine* engine;

	static std::map<std::string,boost::shared_ptr<ISoundSource>> soundSources;

	static GLfloat audioVolume;
	static GLfloat musicVolume;

	static ISound* currentMusic;
};

