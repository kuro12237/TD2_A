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
}

void GameAudio::PlayHitSound()
{
	Audio::AudioPlayWave(GameAudio::GetInstance()->hitSoundHandle_);
}

void GameAudio::PlayShotSound()
{
	Audio::AudioPlayWave(GameAudio::GetInstance()->shotSoundHandle_);
}
