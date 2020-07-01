#include "Framework.h"
#include "Timer.h"

Timer::Timer()
	: frameRate(0), frameCount(0), timeElapsed(0), oneSecCount(0),
	runTime(0), lockFPS(0)
{
	//1�ʵ��� CPU�� �������� ��ȯ�ϴ� �Լ�
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

	//���� CPU������
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

	timeScale = 1.0 / (double)periodFrequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	timeElapsed = (double)(curTime - lastTime) * timeScale;

	if (lockFPS != 0)
	{
		while (timeElapsed < (1.0 / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			timeElapsed = (double)(curTime - lastTime) * timeScale;
		}
	}

	lastTime = curTime;

	//FPS(Frame Per Second)
	frameCount++;
	oneSecCount += timeElapsed;

	if (oneSecCount >= 1)
	{
		frameRate = frameCount;
		frameCount = 0;
		oneSecCount = 0;
	}

	runTime += timeElapsed;
}

void Timer::Render()
{
	wstring str;

	str = L"FPS : " + to_wstring(frameRate);
	TextOut(Program::backBuffer, 0, 0, str.c_str(), str.size());
	str = L"RunTime : " + to_wstring(runTime);
	TextOut(Program::backBuffer, 0, 20, str.c_str(), str.size());
	str = L"Elapsed : " + to_wstring(timeElapsed);
	TextOut(Program::backBuffer, 0, 40, str.c_str(), str.size());
}
