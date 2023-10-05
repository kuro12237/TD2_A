#include"Audio.h"

Audio::Audio()
{
}

Audio::~Audio()
{
}

Audio* Audio::GetInstance()
{
	static Audio instance;
	return &instance;
}

void Audio::Initialize()
{
	HRESULT hr{};
	if (!Audio::GetInstance()->InitializeFlag)
	{
		Audio::GetInstance()->InitializeFlag = true;
	}
	else {
		LogManager::Log("Audio::Initialize_ERROR\n");

		assert(0);
	}

	hr = XAudio2Create(&Audio::GetInstance()->xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	//master�̃{�C�X�̍쐬
	hr = Audio::GetInstance()->xAudio->CreateMasteringVoice(&Audio::GetInstance()->masterVoice);
	assert(SUCCEEDED(hr));
}

void Audio::Finalize()
{
	Audio::GetInstance()->xAudio.Reset();
}

uint32_t Audio::SoundLoadWave(const char* filename)
{
	//HRESULT result{};
	Audio::GetInstance()->soundDataCount_++;
	ifstream file;
	file.open(filename, std::ios_base::binary);
	assert(SUCCEEDED(file.is_open()));

	//file��Riff�Ɉ�v���邩Type��Wave��
	RiffHeader riff = {};
	file.read((char*)&riff, sizeof(riff));
	if (strncmp(riff.chunk.id,"RIFF",4) != 0)
	{assert(0);}
	if (strncmp(riff.Type, "WAVE", 4) != 0)
	{assert(0);}

	//Format�̃`�����N�ǂݍ���
	FormatChunk format = {};
	//�`�����N�w�b�_�[�̊m�F
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);
	
	//Data�`�����N�̓ǂݍ���
	ChunkHeader data = {};
	file.read((char*)&data, sizeof(data));
	if (strncmp(data.id,"JUNK",4) == 0){

		file.seekg(data.size, ios_base::cur);
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data", 4) != 0)
	{assert(0);}
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
	file.close();
	//���
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataCount_].wfex = format.fmt;
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataCount_].pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->soundData_[Audio::GetInstance()->soundDataCount_].bufferSize = data.size;

	return Audio::GetInstance()->soundDataCount_;
}

void Audio::SoundUnLoad()
{
	for (int i = Audio::GetInstance()->soundDataCount_; i >0 ; i--)
	{
		delete[] Audio::GetInstance()->soundData_[i].pBuffer;
		Audio::GetInstance()->soundData_[i].pBuffer = 0;
		Audio::GetInstance()->soundData_[i].bufferSize = 0;
		Audio::GetInstance()->soundData_[i].wfex = {};
	}
	Audio::GetInstance()->soundDataCount_ = 0;
}

void Audio::AudioPlayWave(uint32_t soundHandle)
{
	HRESULT result{};
    IXAudio2SourceVoice* pSourcevoice = nullptr;
	result = Audio::GetInstance()->xAudio->CreateSourceVoice(&pSourcevoice, &Audio::GetInstance()->soundData_[soundHandle].wfex);
	assert(SUCCEEDED(result));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = Audio::GetInstance()->soundData_[soundHandle].pBuffer;
	buf.AudioBytes = Audio::GetInstance()->soundData_[soundHandle].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	result = pSourcevoice->SubmitSourceBuffer(&buf);
	result = pSourcevoice->Start();

	assert(SUCCEEDED(result));
}
