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
	//ŒÅ’è‚µ‚½‚¢Å‘åfps
	//(60‚­‚ç‚¢‚ÅŒÅ’è‚µ‚½‚¢‚Ì‚Å‚¿‚å‚Á‚Æ‚‚ß‚Ì”’l‚ğİ’è‚·‚é)
	const float maxfps = 90;

	const float MIN_FREAM_TIME = 1.0f / maxfps;

	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;

};

