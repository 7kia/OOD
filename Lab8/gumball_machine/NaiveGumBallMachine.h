#pragma once

#include <iostream>
#include <boost/format.hpp>
#include "IGumballMachine.h"

namespace naive
{
class CGumballMachine : public IGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned ballCount, unsigned maxQuarter);

	unsigned GetBallCount() const override;
	unsigned GetCoinsCount() const override;

	bool InsertQuarter() override;
	bool EjectQuarters() override;
	bool TurnCrank() override;

	bool Refill(unsigned numBalls) override;

	std::string ToString() const override;

private:
	bool AddCoin()  override;
	bool UseCoin() override;
	bool ReturnAllCoins() override;
	bool ReleaseBall() override;

	void Dispense();
private:
	unsigned m_ballsCount;	// Количество шариков
	unsigned m_quarterCount = 0;
	const unsigned m_maxQuarterCount = 1;
	State m_state = State::SoldOut;
};
}