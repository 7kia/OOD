// ChartViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Model/HarmonicCollection.h"
#include "ChartViewDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// CChartViewDlg dialog

IMPLEMENT_DYNAMIC(CChartViewDlg, CDialog)

CChartViewDlg::CChartViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHART_VIEW_DIALOG, pParent)
{

}

CChartViewDlg::~CChartViewDlg()
{
}

IChartView & CChartViewDlg::GetChart()
{
	return m_staticChart;
}

void CChartViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChartViewDlg, CDialog)
END_MESSAGE_MAP()



// CChartViewDlg message handlers


BOOL CChartViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_staticChart.SubclassDlgItem(IDC_STATIC_CHART, this);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
