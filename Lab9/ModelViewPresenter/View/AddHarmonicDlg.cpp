// AddHarmonicDlg.cpp : implementation file
//

#include "stdafx.h"

#include <afxdialogex.h>

#include "../Model/HarmonicCollection.h"
#include "./Model/HarmonicStringGenerator.h"
#include "AddHarmonicDlg.h"
#include "FormDataExtractor.h"

using namespace FormDataExtractor;

// CAddHarmonicDlg dialog

IMPLEMENT_DYNAMIC(CAddHarmonicDlg, CDialogEx)

CAddHarmonicDlg::CAddHarmonicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_HARMONIC_DIALOG, pParent)
{

}

CAddHarmonicDlg::~CAddHarmonicDlg()
{

}

signals::Connection CAddHarmonicDlg::DoOnAddHarmonic(AddHarmonicSignal::slot_type const& handler)
{
	return m_addHarmonicSignal.connect(handler);
}

void CAddHarmonicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AMPLITUDE, m_editAmplitude);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_editFrequency);
	DDX_Control(pDX, IDC_EDIT_PHASE, m_editPhase);
	DDX_Control(pDX, IDC_STATIC_PREVIEW_HARMONIC, m_harmonicPreview);
}


void CAddHarmonicDlg::UpdatePreview()
{
	
	float amplitude = GetEditValue(m_editAmplitude);
	float phase = GetEditValue(m_editPhase);
	float frequency = GetEditValue(m_editFrequency);
	FunctionType function = m_useSin ? FunctionType::Sin : FunctionType::Cos;

	auto previewString = HarmonicStringGenerator::CreateHarmonicString(amplitude, function, frequency, phase);
	m_harmonicPreview.SetWindowTextW(previewString.c_str());
}



BEGIN_MESSAGE_MAP(CAddHarmonicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_COS_RADIO, &CAddHarmonicDlg::OnBtnClickedCosRadio)
	ON_BN_CLICKED(IDC_SIN_RADIO, &CAddHarmonicDlg::OnBtnClickedSinRadio)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE, &CAddHarmonicDlg::OnKillFocusAmplitude)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY, &CAddHarmonicDlg::OnKillFocusFrequency)
	ON_EN_KILLFOCUS(IDC_EDIT_PHASE, &CAddHarmonicDlg::OnKillFocusPhase)
END_MESSAGE_MAP()


// CAddHarmonicDlg message handlers


BOOL CAddHarmonicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editPhase.SetWindowTextW(L"0");
	m_editAmplitude.SetWindowTextW(L"1");
	m_editFrequency.SetWindowTextW(L"1");

	m_useSin = true;
	CheckRadioButton(IDC_SIN_RADIO, IDC_COS_RADIO, IDC_SIN_RADIO);

	UpdatePreview();
	return TRUE;
}


void CAddHarmonicDlg::OnBtnClickedCosRadio()
{
	m_useSin = false;

	if (UpdateData())
	{
		UpdatePreview();
	}
}


void CAddHarmonicDlg::OnBtnClickedSinRadio()
{
	m_useSin = true;

	if (UpdateData())
	{
		UpdatePreview();
	}
}

void CAddHarmonicDlg::OnKillFocusAmplitude()
{
	if (UpdateData())
	{
		UpdatePreview();
	}
}

void CAddHarmonicDlg::OnKillFocusFrequency()
{
	if (UpdateData())
	{
		UpdatePreview();
	}
}

void CAddHarmonicDlg::OnKillFocusPhase()
{
	if (UpdateData())
	{
		UpdatePreview();
	}
}

void CAddHarmonicDlg::OnOK()
{
	float amplitude = GetEditValue(m_editAmplitude);
	float phase = GetEditValue(m_editPhase);
	float frequency = GetEditValue(m_editFrequency);
	FunctionType function = m_useSin ? FunctionType::Sin : FunctionType::Cos;

	m_addHarmonicSignal(amplitude, function, frequency, phase);
	CDialogEx::OnOK();
}

void CAddHarmonicDlg::OnCancel()
{
	CDialogEx::OnCancel();
}
