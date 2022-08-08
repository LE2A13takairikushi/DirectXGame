#pragma once
#include <Windows.h>
#include <tchar.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class FPSfix
{
public:
	int Initialize();
	void Update();

	float fps = 0;
	float frameTime = 0;

private:
	//å≈íËÇµÇΩÇ¢ç≈ëÂfps
	const float maxfps = 144;

	const float MIN_FREAM_TIME = 1.0f / maxfps;

	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;

};

