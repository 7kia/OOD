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

	void Refill(unsigned numBalls) override;

	std::string ToString() const override;

private:
	void AddCoin()  override;
	void UseCoin() override;
	void ReturnAllCoins() override;
	void ReleaseBall() override;

	void Dispense();
private:
	unsigned m_ballsCount;	// Количество шариков
	unsigned m_coinsCount = 0;
	const unsigned m_maxCoinsCount = 1;
	State m_state = State::SoldOut;
};
}