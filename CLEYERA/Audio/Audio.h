#pragma once
#include"Pch.h"
#include"LogManager.h"

/// <summary>
/// チャンクヘッダー
/// </summary>
struct ChunkHeader
{
	char id[4];
	int32_t size;
};

/// <summary>
/// Riffヘッダチャンク
/// </summary>
struct RiffHeader
{
	ChunkHeader chunk;
	char Type[4];
};

struct FormatChunk
{
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

struct soundData
{
	WAVEFORMATEX wfex;
	BYTE* pBuffer;
	unsigned int bufferSize;
};

class Audio
{
public:
	Audio();
	~Audio();

	static Audio* GetInstance();

	static void Initialize();

	static void Finalize();

	static uint32_t SoundLoadWave(const char* filename);

	static void SoundUnLoad();

	static void AudioPlayWave(uint32_t soundHandle);

private:

	ComPtr<IXAudio2> xAudio=nullptr;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	uint32_t soundDataCount_{};

	static const uint32_t kSoundDataMax = 4;
    soundData soundData_[kSoundDataMax]{};
	bool InitializeFlag = false;
};

