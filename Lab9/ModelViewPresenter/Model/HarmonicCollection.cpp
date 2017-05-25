#include "stdafx.h"
#include "HarmonicCollection.h"
#include "Harmonic.h"

float CHarmonicCollection::CalculateAt(float x) const
{
	float result = 0;
	for (auto & harmonic : m_harmonics)
	{
		result += harmonic->CalculateAt(x);
	}
	return result;
}

IHarmonicPtr CHarmonicCollection::GetHarmonic(size_t index) const
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Out of range");
	}
	return m_harmonics[index];
}

std::vector<IHarmonicPtr> CHarmonicCollection::GetHarmonics() const
{
	return m_harmonics;
}

void CHarmonicCollection::AddHarmonic(const std::shared_ptr<IHarmonic> & pHarmonic)
{
	m_harmonics.push_back(pHarmonic);
	m_harmonicsChangeSignal();
}

void CHarmonicCollection::DeleteHarmonic(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Out of range");
	}
	m_harmonics.erase(m_harmonics.begin() + index);
	m_harmonicsChangeSignal();
}

size_t CHarmonicCollection::GetCount() const
{
	return m_harmonics.size();
}

signals::Connection CHarmonicCollection::DoOnChangeHarmonics(const HarmonicsChangeSignal::slot_type & handler)
{
	for (auto & harmonic : m_harmonics)
	{
		harmonic->DoOnChangeHarmonic(handler);
	}

	return m_harmonicsChangeSignal.connect(handler);
}
