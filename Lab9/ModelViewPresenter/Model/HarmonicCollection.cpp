#include "stdafx.h"
#include "HarmonicCollection.h"
#include "Harmonic.h"

namespace
{
	void CheckIndex(size_t index, size_t max)
	{
		if (index >= max)
		{
			throw std::out_of_range("Index out range");
		}
	};
}

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
	CheckIndex(index, m_harmonics.size());
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
	CheckIndex(index, m_harmonics.size());
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
