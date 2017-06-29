#pragma once
#include "IChartView.h"
#include "afxwin.h"
#include "ChartView.h"


// CChartViewDlg dialog

class CChartViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CChartViewDlg)

public:
	CChartViewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChartViewDlg();

	virtual IChartView & GetChart();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_VIEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CChartView m_staticChart;
	virtual BOOL OnInitDialog();
};
