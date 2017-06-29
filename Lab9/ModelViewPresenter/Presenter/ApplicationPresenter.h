#pragma once

#include "../Model/FunctionType.h"
#include "../View/AddHarmonicDlg.h"
#include "ConnectionsStorage.h"

class IHarmonicCollection;
class IMainDlgView;

class CApplicationPresenter
{
public:
	CApplicationPresenter(
		IHarmonicCollection & harmonicCollection,
		IMainDlgView & view,
		CAddHarmonicDlg & addHarmonicDlg
	);
	//////////////////////////////////////////////////////////////////////
	// Methods


private:
	void ConnectSignalsForAddHarmonicDlg();
	void ConnectSignalsForMainDlgView();
	void ConnectSignalsForHarmonicCollection();

	void ChangeFrequency(int index, float frequency);
	void ChangePhase(int index, float phase);
	void ChangeAmplitude(int index, float amplitude);
	void ChangeFunctionType(int index, FunctionType functionType);
	void ChangeSelection(int index);

	void AddHarmonic(
		float aplitude,
		FunctionType type,
		float frequency,
		float phase
	);
	bool OpenAddDialog();
	void DeleteHarmonic(int index);
	
	void Update();

	void UpdateChart();
	void UpdateView();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CAddHarmonicDlg & m_addHarmonic;
	IHarmonicCollection & m_harmonicCollection;
	IMainDlgView & m_mainDlgView;

	ScopedConnectionsStorage m_connections;
};

