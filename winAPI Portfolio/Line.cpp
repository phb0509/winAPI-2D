#include "Framework.h"

Line::Line() : start(0, 0), end(0, 0)
{
}

Line::Line(Vector2 start, Vector2 end)
	: start(start), end(end)
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, (int)start.x, (int)start.y, nullptr);
	LineTo(hdc, (int)end.x, (int)end.y);
}

bool Line::IsBetween(Line* line)
{
	Vector2 A = line->start - start;
	Vector2 B = line->end - start;
	Vector2 C = end - start;

	double crossAC = A.Cross(C);
	double crossBC = B.Cross(C);

	return crossAC * crossBC < 0;
}
