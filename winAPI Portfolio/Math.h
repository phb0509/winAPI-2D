#pragma once

class Math
{
public:
	enum Dir
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	static int Random(int min, int max);
	static double Random(double min, double max);
	static Point RandomPoint(double min, double max);
};