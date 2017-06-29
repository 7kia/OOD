#pragma once
#include "IChartView.h"
#include "afxwin.h"
#include "afxcmn.h"


// CTableViewDlg dialog

class CTableViewDlg : public CDialogEx, public IChartView
{
	DECLARE_DYNAMIC(CTableViewDlg)

public:
	CTableViewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTableViewDlg();

	void SetData(const Points2D & data) final;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABLE_VIEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	
private:
	CListCtrl m_pointsList;
};
