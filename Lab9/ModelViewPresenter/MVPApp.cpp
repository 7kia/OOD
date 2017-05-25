
// MVPApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MVPApp.h"

#include "View/AddHarmonicDlg.h"
#include "View/MainDlgView.h"
#include "Presenter/ApplicationPresenter.h"
#include "Model/ApplicationModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMVPApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CMVPApp theApp;

BOOL CMVPApp::InitInstance()
{
	CWinApp::InitInstance();

	CMainDlgView dlg;
	CApplicationModel harmonics;
	CAddHarmonicDlg addDlg;
	CApplicationPresenter presenter(harmonics.GetHarmonicCollection(), dlg, addDlg);
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

