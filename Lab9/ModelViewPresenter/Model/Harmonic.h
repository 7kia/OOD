#pragma once
#include "IHarmonic.h"
class CHarmonic : public IHarmonic
{
public:
	CHarmonic(
		float amplitude,
		FunctionType  function,
		float frequency,
		float phase
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	FunctionType GetType() const override final;
	void SetType(FunctionType  type) override final;

	float GetAmplitude() const override final;
	void SetAmplitude(float amplitude) override final;

	float GetFrequency() const override final;
	void SetFrequency(float frequency) override final;

	float GetPhase() const override final;
	void SetPhase(float phase) override final;

	float CalculateAt(float x) const override final;
	signals::Connection DoOnChangeHarmonic(const HarmonicChangeSignal::slot_type & handler) override final;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	float m_amplitude = 1.f;
	FunctionType m_function = FunctionType::Sin;
	float m_frequency = 1.f;
	float m_phase = 0.f;

	HarmonicChangeSignal m_harmonicChangeSignal;
};

