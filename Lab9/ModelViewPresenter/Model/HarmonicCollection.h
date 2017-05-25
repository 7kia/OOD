#pragma once
#include "IHarmonicCollection.h"
#include <vector>

class CHarmonicCollection :	public IHarmonicCollection
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IHarmonicCollection
	float CalculateAt(float x) const override final;

	IHarmonicPtr GetHarmonic(size_t index) const override final;
	std::vector<IHarmonicPtr> GetHarmonics() const override final;

	void AddHarmonic(const std::shared_ptr<IHarmonic> & pHarmonic) override final;
	void DeleteHarmonic(size_t index) override final;

	size_t GetCount() const override final;

	signals::Connection DoOnChangeHarmonics(const HarmonicsChangeSignal::slot_type & handler) override final;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<IHarmonicPtr> m_harmonics;
	HarmonicsChangeSignal m_harmonicsChangeSignal;
};

