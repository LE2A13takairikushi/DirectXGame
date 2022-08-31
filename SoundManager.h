#pragma once
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include "DirectXCommon.h"
#include <fstream>

struct ChunkHeader
{
	char id[4];
	int32_t size;
};

struct RiffHeader
{
	ChunkHeader chunk;
	char type[4];
};

struct FormatChunk
{
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

struct SoundData
{
	//�g�`�t�H�[�}�b�g
	WAVEFORMATEX wfex;
	//�o�b�t�@�̐擪�A�h���X
	BYTE* pBuffer;
	//�o�b�t�@�̃T�C�Y
	unsigned int bufferSize;
};

class SoundManager
{
public:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	void Initialize();

	SoundData SoundLoadWave(const char* filename);

	void SoundUnload(SoundData* soundData);
	void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData);
};

