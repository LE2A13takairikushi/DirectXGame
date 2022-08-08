#include "FPSfix.h"
#include <sstream>

int FPSfix::Initialize()
{
	if (QueryPerformanceFrequency(&timeFreq) == FALSE)
	{
		return(E_FAIL);
	}
	QueryPerformanceCounter(&timeStart);
}

void FPSfix::Update()
{
	//今の時間を取得
	QueryPerformanceCounter(&timeEnd);
	//(今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FREAM_TIME)
	{
		DWORD sleepTime = static_cast<DWORD>((MIN_FREAM_TIME - frameTime) * 1000);

		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);

		return;
	}

	if (frameTime > 0.0f) {
		fps = (fps * 0.99f) + (0.01f / frameTime);

#ifdef _DEBUG

#ifdef UNICODE
		std::wstringstream stream;
#else
		std::stringstream stream;
		
#endif UNICODE
		stream << fps << "FPS" << std::endl;
		OutputDebugString(stream.str().c_str());
#endif // _DEBUG

	}
	timeStart = timeEnd;
}