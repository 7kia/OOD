#pragma once
#include <vector>

struct Point2D
{
	Point2D() = default;
	Point2D(float x, float y)
		:x(x), y(y)
	{}
	float x = 0;
	float y = 0;
};

class IChartView
{
public:
	typedef std::vector<Point2D> Points2D;
	virtual void SetData(const Points2D & data) = 0;
	virtual ~IChartView() = default;
};

