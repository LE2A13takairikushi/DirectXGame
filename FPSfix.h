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
	//�Œ肵�����ő�fps
	//(60���炢�ŌŒ肵�����̂ł�����ƍ��߂̐��l��ݒ肷��)
	const float maxfps = 90;

	const float MIN_FREAM_TIME = 1.0f / maxfps;

	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;

};

