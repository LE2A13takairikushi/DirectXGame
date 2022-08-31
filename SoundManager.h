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
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭アドレス
	BYTE* pBuffer;
	//バッファのサイズ
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

