#pragma once
#define PI 3.141592653

struct vec2
{
	float x;
	float y;
};

class rayCast
{
public:
	double angleBetweenPos(vec2 pos1, vec2 pos2)
	{
		double y2 = pos2.y;
		double y1 = pos1.y;
		double x1 = pos1.x;
		double x2 = pos2.x;
		return atan2(y2 - y1, x2 - x1)*180 / PI;
	}

	double anglefromPosition(vec2 p1, vec2 p2)
	{
		double aPos = atan2(p1.y - p2.y, p1.x - p2.x) * 180 / PI;
		aPos *= -1;
		return aPos;
	}

private:




};