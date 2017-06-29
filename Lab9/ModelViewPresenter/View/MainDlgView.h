#pragma once
#include "IMainDlgView.h"
#include "afxwin.h"
#include "ChartView.h"
#include "ChartViewDlg.h"
#include "TableViewDlg.h"

class CMainDlgView : public CDialogEx, public IMainDlgView
{
// Construction
public:
	CMainDlgView(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HARMONICS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	//--------------------------------------------
	// IMainDlgView
	void SetListItems(std::vector<std::wstring>const& list) override final;
	void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) override final;
	IChartView & GetChartView() override final;

	// Signals
	signals::Connection DoOnInit(const InitSignal::slot_type & handler) override final;
	signals::Connection DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	signals::Connection DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	signals::Connection DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	signals::Connection DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler) override final;
	signals::Connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) override final;
	signals::Connection DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler) override final;
	signals::Connection DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler) override final;
	signals::Connection DoOnChangeTab(const ChangeTabSignal::slot_type & handler) override final;
	//--------------------------------------------
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
protected:

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOk();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

private:
	void OnKillFocusAmplitude();
	void OnKillFocusPhase();
	void OnKillFocusFrequency();

	void DisableEditElements();
	void EnableEditElememts();
	void UpdateDataAndSaveSelect(CEdit & edit, ChangeHarmonicSignal & signal);

	void UpdateEdits();
	void EnableEdits(bool enabled);

	InitSignal m_initSignal;
	ChangeHarmonicSignal m_changeAmplitudeSignal;
	ChangeHarmonicSignal m_changeFrequencySignal;
	ChangeHarmonicSignal m_changePhaseSignal;
	ChangeFunctionTypeSignal m_changeFunctionType;
	AddHarmonicSignal m_addHarmonicSignal;
	DeleteHarmonicSignal m_deleteHarmonicSignal;
	ChangeSelectionSignal m_changeSelection;
	ChangeTabSignal m_changeTabSignal;

	std::shared_ptr<CChartViewDlg> m_chartDlg;
	std::shared_ptr<CTableViewDlg> m_tableDlg;

	CTabCtrl m_tabs;
	CListBox m_harmonicsList;
	CEdit m_amplitudeEdit;
	CEdit m_frequencyEdit;
	CEdit m_phaseEdit;
	int m_sinRatio;
	int m_cosRatio;
public:

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLbnSelchangeHarmonicsList();
	afx_msg void OnBtnClickedRadiosin();
	afx_msg void OnBtnClickedRadiocos();
	afx_msg void OnTcnSelchangeTabView(NMHDR *pNMHDR, LRESULT *pResult);
};
