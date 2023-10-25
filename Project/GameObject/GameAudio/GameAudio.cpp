#include"GameAudio.h"


GameAudio* GameAudio::GetInstance()
{
	static GameAudio instance;
	return &instance;
}

void GameAudio::Initialize()
{
	GameAudio::GetInstance()->hitSoundHandle_ = Audio::SoundLoadWave("Resources/Sound/hit.wav");
	GameAudio::GetInstance()->shotSoundHandle_ = Audio::SoundLoadWave("Resources/Sound/shot.wav");
	GameAudio::GetInstance()->SelectsoundHandle = Audio::SoundLoadWave("Resources/Sound/popa.wav");
}

void GameAudio::PlayHitSound()
{
	Audio::AudioPlayWave(GameAudio::GetInstance()->hitSoundHandle_);
}

void GameAudio::PlayShotSound()
{
	Audio::AudioPlayWave(GameAudio::GetInstance()->shotSoundHandle_);
}

void GameAudio::PlaySelectSound()
{
	Audio::AudioPlayWave(GameAudio::GetInstance()->SelectsoundHandle);
}
