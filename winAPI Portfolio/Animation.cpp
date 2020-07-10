#include "Framework.h"

Animation::Animation(double frameUpdateSec)
	: time(0), frameUpdateSec(frameUpdateSec), play(false),
	loop(false), pingpong(false), EndEvent(nullptr),
	EndEventInt(nullptr), nextAction(0)
{
}

Animation::Animation(Texture* texture, double frameUpdateSec) // default값 0.1
	: time(0), frameUpdateSec(frameUpdateSec), play(false),
	loop(false), pingpong(false), EndEvent(nullptr),
	EndEventInt(nullptr), nextAction(0)
{
	maxFrame = texture->MaxFrame();

	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			frames.emplace_back(POINT{ x, y });     // 일차원적으로 인덱스 꺼내쓸수있게 (0,1,2,3....) 해주는곳. 
		}
	}
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (!play)
		return;

	time += DELTA;

	if (time > frameUpdateSec)
	{
		time -= frameUpdateSec;
		curPlayNum++;

		if (curPlayNum > action.size() - 1)
		{
			if (loop)
			{
				curPlayNum = 0;
			}

			else
			{
				curPlayNum--;
				play = false;

				if (EndEvent != nullptr)
					EndEvent();
				if (EndEventInt != nullptr)
					EndEventInt(nextAction);
			}
		}
	}
}

void Animation::SetDefault(bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = 0; i < frames.size(); i++)
	{
		action.emplace_back(i);
	}

	SetPingpong();
}

void Animation::SetArray(int* arr, int arrSize, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = 0; i < arrSize; i++)
	{
		action.emplace_back(arr[i]);
	}

	SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = start; i <= end; i++)
	{
		action.emplace_back(i);              // 4,7일경우 action 0,1,2,3 인덱스에 4,5,6,7
	}

	SetPingpong();
}

void Animation::SetFrame(int left, int top, int width, int height)
{
	RECT rect = { left, top, width, height };
	rectFrames.emplace_back(rect);
	action.emplace_back(action.size());
}

void Animation::SetPingpong()
{
	if (pingpong)
	{
		for (int i = action.size() - 2; i >= 0; i--)    // action : vector<int>
			action.emplace_back(action[i]);
	}
}
