#pragma once
#include"Audio.h"

class GameAudio
{
public:
	GameAudio() {};
	~GameAudio() {};

	static GameAudio* GetInstance();

	static void Initialize();

	static void PlayHitSound();

	static void PlayShotSound();

	static void PlaySelectSound();
private:

	uint32_t hitSoundHandle_ = 0;
	uint32_t shotSoundHandle_ = 0;
	uint32_t SelectsoundHandle = 0;

};




