
// HarmonicsDlg.cpp : implementation file
//

#include "stdafx.h"

#include <afxmsg_.h>
#include <afxdialogex.h>

#include <boost/lexical_cast.hpp>

#include "MVPApp.h"
#include "MainDlgView.h"
#include "FormDataExtractor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHarmonicsDlg dialog



CMainDlgView::CMainDlgView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HARMONICS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HARMONICS_LIST, m_harmonicsList);
	DDX_Control(pDX, IDC_EDIT_AMPLITUDE, m_amplitudeEdit);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_frequencyEdit);
	DDX_Control(pDX, IDC_EDIT_PHASE, m_phaseEdit);
	DDX_Control(pDX, IDC_TAB_VIEW, m_tabs);
}

void CMainDlgView::SetListItems(std::vector<std::wstring> const& list)
{
	m_harmonicsList.ResetContent();
	for (auto & string : list)
	{
		m_harmonicsList.AddString(string.c_str());
	}
}

void CMainDlgView::UpdateSelectedHarmonic(
	float amplitude,
	FunctionType type,
	float frequency,
	float phase)
{
	m_amplitudeEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(amplitude).c_str());
	m_phaseEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(phase).c_str());
	m_frequencyEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(frequency).c_str());

	std::map<FunctionType, DWORD> functions = {
		{ FunctionType::Cos, IDC_RADIO_COS},
		{ FunctionType::Sin, IDC_RADIO_SIN },
	};
	
	CheckRadioButton(IDC_RADIO_SIN, IDC_RADIO_COS, functions.at(type));
}

IChartView & CMainDlgView::GetChartView()
{
	std::map<int, IChartView&> chartsMap = {
		{ 0, m_chartDlg->GetChart()},
		{ 1, *m_tableDlg },
	};
	int currentTab = m_tabs.GetCurSel();
	auto it = chartsMap.find(currentTab);
	if (it != chartsMap.cend())
	{
		return it->second;
	}
	throw std::runtime_error("Invalid tab");
	
}

void CMainDlgView::EnableEdits(bool enabled)
{
	m_amplitudeEdit.EnableWindow(enabled);
	m_frequencyEdit.EnableWindow(enabled);
	m_phaseEdit.EnableWindow(enabled);
	GetDlgItem(IDC_RADIO_SIN)->EnableWindow(enabled);
	GetDlgItem(IDC_RADIO_COS)->EnableWindow(enabled);
}

void CMainDlgView::UpdateEdits()
{
	int index = m_harmonicsList.GetCurSel();
	EnableEdits(index > -1);
}

signals::Connection CMainDlgView::DoOnInit(const InitSignal::slot_type & handler)
{
	return m_initSignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changeAmplitudeSignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changeFrequencySignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changePhaseSignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler)
{
	return m_changeFunctionType.connect(handler);
}

signals::Connection CMainDlgView::DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler)
{
	return m_deleteHarmonicSignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler)
{
	return m_addHarmonicSignal.connect(handler);
}

signals::Connection CMainDlgView::DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler)
{
	return 	m_changeSelection.connect(handler);
}

signals::Connection CMainDlgView::DoOnChangeTab(const ChangeTabSignal::slot_type & handler)
{
	return m_changeTabSignal.connect(handler);
}

BEGIN_MESSAGE_MAP(CMainDlgView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainDlgView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainDlgView::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_HARMONICS_LIST, &CMainDlgView::OnLbnSelchangeHarmonicsList)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE, &CMainDlgView::OnKillFocusAmplitude)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY, &CMainDlgView::OnKillFocusFrequency)
	ON_EN_KILLFOCUS(IDC_EDIT_PHASE, &CMainDlgView::OnKillFocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CMainDlgView::OnBtnClickedRadiosin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CMainDlgView::OnBtnClickedRadiocos)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VIEW, &CMainDlgView::OnTcnSelchangeTabView)
END_MESSAGE_MAP()


// CHarmonicsDlg message handlers

BOOL CMainDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_harmonicsList.GetCurSel() == -1)
	{
		DisableEditElements();
	}
	else
	{
		EnableEditElememts();
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_tabs.InsertItem(0, L"Chart");
	m_tabs.InsertItem(1, L"Table");
			
	m_chartDlg = std::make_shared<CChartViewDlg>(&m_tabs);
	m_chartDlg->Create(IDD_CHART_VIEW_DIALOG, &m_tabs);
	m_chartDlg->SubclassDlgItem(IDD_CHART_VIEW_DIALOG, this);
	
	m_tableDlg = std::make_shared<CTableViewDlg>(&m_tabs);
	m_tableDlg->Create(IDD_TABLE_VIEW_DIALOG, &m_tabs);
	
	CRect rc;
	m_tabs.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 10;
	rc.left += 10;
	rc.right -= 10;
	m_chartDlg->MoveWindow(&rc);
	m_tableDlg->MoveWindow(&rc);
	
	m_chartDlg->ShowWindow(TRUE);
	m_tableDlg->ShowWindow(FALSE);

	m_tabs.SetCurSel(0);

	m_initSignal();
	EnableEdits(false);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlgView::OnOk()
{
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlgView::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlgView::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlgView::OnKillFocusAmplitude()
{
	UpdateDataAndSaveSelect(m_amplitudeEdit, m_changeAmplitudeSignal);
}

void CMainDlgView::OnKillFocusPhase()
{
	UpdateDataAndSaveSelect(m_phaseEdit, m_changePhaseSignal);
}

void CMainDlgView::OnKillFocusFrequency()
{
	UpdateDataAndSaveSelect(m_frequencyEdit, m_changeFrequencySignal);
}

void CMainDlgView::DisableEditElements()
{
	m_amplitudeEdit.EnableWindow(FALSE);
	m_frequencyEdit.EnableWindow(FALSE);
	m_phaseEdit.EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_SIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_COS)->EnableWindow(FALSE);
}

void CMainDlgView::EnableEditElememts()
{
	m_amplitudeEdit.EnableWindow(TRUE);
	m_frequencyEdit.EnableWindow(TRUE);
	m_phaseEdit.EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_SIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_COS)->EnableWindow(TRUE);
}

void CMainDlgView::UpdateDataAndSaveSelect(CEdit & edit, ChangeHarmonicSignal & useSignal)
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			useSignal(index, FormDataExtractor::GetEditValue(edit));
		}
		m_harmonicsList.SetCurSel(index);
	}
}

void CMainDlgView::OnBnClickedButtonAdd()
{
	if (m_addHarmonicSignal())
	{
		EnableEditElememts();
	}
	UpdateEdits();
	
}


void CMainDlgView::OnBnClickedButtonDelete()
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_deleteHarmonicSignal(index);
		UpdateEdits();
	}


}


void CMainDlgView::OnLbnSelchangeHarmonicsList()
{
	auto index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_changeSelection(index);
		UpdateEdits();
	}
}


void CMainDlgView::OnBtnClickedRadiosin()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_changeFunctionType(index, FunctionType::Sin);
		}
		m_harmonicsList.SetCurSel(index);
	}
}


void CMainDlgView::OnBtnClickedRadiocos()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_changeFunctionType(index, FunctionType::Cos);
		}
		m_harmonicsList.SetCurSel(index);
	}
}

void CMainDlgView::OnTcnSelchangeTabView(NMHDR *pNMHDR, LRESULT *pResult)
{
	int curSel = m_tabs.GetCurSel();
	std::map<int, std::pair<bool, bool>> tabsMap = {
		{ 0,{ true, false } },
		{ 1,{ false, true } },

	};
	auto it = tabsMap.find(curSel);
	if (it != tabsMap.cend())
	{
		m_chartDlg->ShowWindow(it->second.first);
		m_tableDlg->ShowWindow(it->second.second);
		m_changeTabSignal();
	}
	*pResult = 0;
}
