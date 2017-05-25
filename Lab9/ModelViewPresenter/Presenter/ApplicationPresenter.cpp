#include "stdafx.h"
#include "ApplicationPresenter.h"
#include "../Model/Harmonic.h"
#include "../Model/IHarmonicCollection.h"
#include "../Model/HarmonicStringGenerator.h"

#include "../View/IMainDlgView.h"
#include "../View/AddHarmonicDlg.h"
#include "../View/IChartView.h"

CApplicationPresenter::CApplicationPresenter(
	IHarmonicCollection & harmonicCollection,
	IMainDlgView & view,
	CAddHarmonicDlg & addHarmonicDlg
)
	: m_harmonicCollection(harmonicCollection)
	, m_mainDlgView(view)
	, m_addHarmonic(addHarmonicDlg)
{
	ConnectSignalsForMainDlgView();
	ConnectSignalsForAddHarmonicDlg();
	ConnectSignalsForHarmonicCollection();
}


void CApplicationPresenter::ConnectSignalsForMainDlgView()
{
	m_connections += m_mainDlgView.DoOnAddHarmonic(boost::bind(&CApplicationPresenter::OpenAddDialog, this));
	m_connections += m_mainDlgView.DoOnAmplitudeChange(boost::bind(&CApplicationPresenter::ChangeAmplitude, this, _1, _2));
	m_connections += m_mainDlgView.DoOnDeleteHarmonic(boost::bind(&CApplicationPresenter::DeleteHarmonic, this, _1));
	m_connections += m_mainDlgView.DoOnFrequencyChange(boost::bind(&CApplicationPresenter::ChangeFrequency, this, _1, _2));
	m_connections += m_mainDlgView.DoOnFunctionTypeChange(boost::bind(&CApplicationPresenter::ChangeFunctionType, this, _1, _2));
	m_connections += m_mainDlgView.DoOnInit(boost::bind(&CApplicationPresenter::Update, this));
	m_connections += m_mainDlgView.DoOnPhaseChange(boost::bind(&CApplicationPresenter::ChangePhase, this, _1, _2));
	m_connections += m_mainDlgView.DoOnChangeSelect(boost::bind(&CApplicationPresenter::ChangeSelection, this, _1));
}

void CApplicationPresenter::ConnectSignalsForHarmonicCollection()
{
	m_connections += m_harmonicCollection.DoOnChangeHarmonics(boost::bind(&CApplicationPresenter::Update, this));
}

void CApplicationPresenter::ConnectSignalsForAddHarmonicDlg()
{
	m_connections += m_addHarmonic.DoOnAddHarmonic(boost::bind(&CApplicationPresenter::AddHarmonic, this, _1, _2, _3, _4));
}

void CApplicationPresenter::ChangeFrequency(int index, float frequency)
{
	auto harmonic = m_harmonicCollection.GetHarmonic(index);
	harmonic->SetFrequency(frequency);
}

void CApplicationPresenter::ChangePhase(int index, float phase)
{
	auto harmonic = m_harmonicCollection.GetHarmonic(index);
	harmonic->SetPhase(phase);
}

void CApplicationPresenter::ChangeAmplitude(int index, float amplitude)
{
	auto harmonic = m_harmonicCollection.GetHarmonic(index);
	harmonic->SetAmplitude(amplitude);
}

void CApplicationPresenter::ChangeFunctionType(int index, FunctionType functionType)
{
	auto harmonic = m_harmonicCollection.GetHarmonic(index);
	harmonic->SetType(functionType);
}

void CApplicationPresenter::ChangeSelection(int index)
{
	auto pHarmonic = m_harmonicCollection.GetHarmonic(index);
	m_mainDlgView.UpdateSelectedHarmonic(
		pHarmonic->GetAmplitude(),
		pHarmonic->GetType(),
		pHarmonic->GetFrequency(),
		pHarmonic->GetPhase()
	);
}

void CApplicationPresenter::OpenAddDialog()
{
	 m_addHarmonic.DoModal();
}

void CApplicationPresenter::AddHarmonic(
	float aplitude,
	FunctionType const& type,
	float frequency,
	float phase
)
{
	m_harmonicCollection.AddHarmonic(std::make_shared<CHarmonic>(aplitude, type, frequency, phase));
	auto pHarmonic = m_harmonicCollection.GetHarmonic(m_harmonicCollection.GetCount() - 1);
	pHarmonic->DoOnChangeHarmonic(boost::bind(&CApplicationPresenter::Update, this));
}

void CApplicationPresenter::DeleteHarmonic(int index)
{
	m_harmonicCollection.DeleteHarmonic(index);
}

void CApplicationPresenter::Update()
{
	UpdateView();
	UpdateChart();
}

void CApplicationPresenter::UpdateChart()
{
	IChartView::Points2D points;
	for (float x = 0; x <= 10; x += 0.1f)
	{
		points.emplace_back(x, m_harmonicCollection.CalculateAt(x));
	}
	m_mainDlgView.GetChartView().SetData(points);
}

void CApplicationPresenter::UpdateView()
{
	std::vector<std::wstring> harmonicsStr;
	for (size_t i = 0; i < m_harmonicCollection.GetCount(); ++i)
	{
		auto pHarmonic = m_harmonicCollection.GetHarmonic(i);
		auto harmonicString = CHarmonicStringGenerator::CreateHarmonicString(
			pHarmonic->GetAmplitude(), 
			pHarmonic->GetType(), 
			pHarmonic->GetFrequency(), 
			pHarmonic->GetPhase()
		);
		harmonicsStr.push_back(harmonicString);
	}
	m_mainDlgView.SetListItems(harmonicsStr);
}

