#pragma once
#include "Signals.h"
#include "../Model/FunctionType.h"

class IChartView;
class ITableView;

class IMainDlgView
{
public:
	typedef signals::Signal<void(int, float)> ChangeHarmonicSignal;
	typedef signals::Signal<void(int, FunctionType)> ChangeFunctionTypeSignal;
	typedef signals::Signal<bool()> AddHarmonicSignal;
	typedef signals::Signal<void(int)> DeleteHarmonicSignal;
	typedef signals::Signal<void(int)> ChangeSelectionSignal;
	typedef signals::Signal<void()> InitSignal;
	typedef signals::Signal<void()> ChangeTabSignal;

	virtual IChartView & GetChartView() = 0;
	//virtual ITableView & GetTableView() = 0;

	virtual void SetListItems(std::vector<std::wstring> const& list) = 0;
	virtual void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) = 0;
	// Signals
	virtual signals::Connection DoOnInit(const InitSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler) = 0;
	virtual signals::Connection DoOnChangeTab(const ChangeTabSignal::slot_type & handler) = 0;

	virtual ~IMainDlgView() = default;
};