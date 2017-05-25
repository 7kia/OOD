#pragma once

#include <memory>
#include "IHarmonic.h"

using IHarmonicPtr = std::shared_ptr<IHarmonic>;

class IHarmonicCollection
{
public:
	typedef signals::Signal<void()> HarmonicsChangeSignal;

	virtual ~IHarmonicCollection() = default;
	
	virtual float CalculateAt(float x) const = 0;
	virtual IHarmonicPtr GetHarmonic(size_t index) const = 0;
	virtual std::vector<IHarmonicPtr> GetHarmonics() const = 0;

	virtual void AddHarmonic(const std::shared_ptr<IHarmonic> & pHarmonic) = 0;
	virtual void DeleteHarmonic(size_t index) = 0;

	virtual size_t GetCount() const = 0;

	virtual signals::Connection DoOnChangeHarmonics(const HarmonicsChangeSignal::slot_type & handler) = 0;
};