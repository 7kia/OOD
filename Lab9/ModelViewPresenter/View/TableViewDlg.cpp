// TableViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Model/HarmonicCollection.h"
#include "TableViewDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// CTableViewDlg dialog

IMPLEMENT_DYNAMIC(CTableViewDlg, CDialogEx)

CTableViewDlg::CTableViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABLE_VIEW_DIALOG, pParent)
{

}

CTableViewDlg::~CTableViewDlg()
{
}

void CTableViewDlg::SetData(const Points2D & data)
{
	m_pointsList.DeleteAllItems();

	std::for_each(data.crbegin(), data.crend(), 
		[&](auto & point) {
			int index = m_pointsList.InsertItem(0, std::to_wstring(point.x).c_str());
			m_pointsList.SetItemText(index, 1, std::to_wstring(point.y).c_str());
		}
	);
}

void CTableViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POINTS_LIST, m_pointsList);
}


BEGIN_MESSAGE_MAP(CTableViewDlg, CDialogEx)
END_MESSAGE_MAP()


// CTableViewDlg message handlers


BOOL CTableViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pointsList.DeleteAllItems();
	m_pointsList.InsertColumn(0, L"x", LVCFMT_LEFT, 200);
	m_pointsList.InsertColumn(1, L"y", LVCFMT_LEFT, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
