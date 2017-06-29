#pragma once
#include "IChartView.h"

class CChartView
	: public CStatic
	, public IChartView
{
public:
	DECLARE_DYNAMIC(CChartView)

	CChartView();
	~CChartView();

	virtual void SetData(const Points2D& data) override;

	void PreSubclassWindow() override;
private:
	void UpdateBounds();
	Points2D m_points;
	Point2D m_leftTop;
	Point2D m_rightBottom;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

