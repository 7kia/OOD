#pragma once
#include <afxwin.h>
#include "resource.h"
#include "Signals.h"

#include "../Model/FunctionType.h"

// CAddHarmonicDlg dialog

class CAddHarmonicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddHarmonicDlg)
public:
	CAddHarmonicDlg(CWnd* pParent = NULL);   // standard constructor

public:
	typedef signals::Signal<void(float, FunctionType, float, float)> AddHarmonicSignal;

	virtual ~CAddHarmonicDlg();
	signals::Connection DoOnAddHarmonic(AddHarmonicSignal::slot_type const& handler);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_HARMONIC_DIALOG };
#endif
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBtnClickedCosRadio();
	afx_msg void OnBtnClickedSinRadio();
	afx_msg void OnKillFocusAmplitude();
	afx_msg void OnKillFocusFrequency();
	afx_msg void OnKillFocusPhase();

	virtual void OnOK();
	virtual void OnCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	void UpdatePreview();

	AddHarmonicSignal m_addHarmonicSignal;
	CEdit m_editAmplitude;
	CEdit m_editFrequency;
	CEdit m_editPhase;
	bool m_useSin = false;
	CStatic m_harmonicPreview;
};
