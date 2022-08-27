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
	//固定したい最大fps
	//(60くらいで固定したいのでちょっと高めの数値を設定する)
	const float maxfps = 90;

	const float MIN_FREAM_TIME = 1.0f / maxfps;

	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;

};

