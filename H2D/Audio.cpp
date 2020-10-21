#include "Audio.h"

irrklang::ISoundEngine* Audio::engine=irrklang::createIrrKlangDevice();

std::map<std::string,boost::shared_ptr<ISoundSource>> Audio::soundSources;

GLfloat Audio::audioVolume;
GLfloat Audio::musicVolume;

ISound* Audio::currentMusic=NULL;

Audio::Audio(void)
{
	
}


Audio::~Audio(void)
{
}


ISound* Audio::playSound(ik_c8* filename)
{
	ISound* x = engine->play2D(filename,false,false,false);
	return x;
}

void Audio::playSoundLooped(ik_c8* filename)
{
	engine->play2D(filename,true,false,false);
}

void Audio::playMusic(ik_c8* filename,bool killCurrentMusic)
{
		if(currentMusic==NULL)
		{
			currentMusic = engine->play2D(filename,false,true,true);
			currentMusic->setIsPaused(false);
		}
		else if(killCurrentMusic)
		{
			currentMusic->stop();
			currentMusic->drop();
			currentMusic = engine->play2D(filename,false,true,true);
			currentMusic->setIsPaused(false);
		}
}

void Audio::addSound(ik_c8* filename)
{
	//AudioSources.insert(std::pair<std::string,boost::shared_ptr<IAudioSource>>("Hello",
	engine->addSoundSourceFromFile(filename,ESM_NO_STREAMING,true);

}
void Audio::deleteSound(ik_c8* filename)
{
	engine->removeSoundSource(filename);
}

void Audio::pauseMusic()
{
	if(currentMusic != NULL)	if(currentMusic->getIsPaused()) currentMusic->setIsPaused(true);
}
void Audio::resumeMusic()
{
	if(currentMusic != NULL)	if(currentMusic->getIsPaused()) currentMusic->setIsPaused(false);
}

void Audio::pauseSounds()
{
	engine->setAllSoundsPaused(true);
}
void Audio::resumeSouns()
{
	engine->setAllSoundsPaused(false);
}

void Audio::stopSounds()
{
	engine->drop();
	engine=irrklang::createIrrKlangDevice();
}
void Audio::stopMusic()
{
	if(currentMusic != NULL)
	{
		currentMusic->stop();
		currentMusic->drop(); 
	}
}