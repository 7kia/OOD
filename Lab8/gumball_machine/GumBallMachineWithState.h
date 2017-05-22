#pragma once

#include <iostream>
#include <boost/format.hpp>
#include "IGumballMachine.h"

namespace with_state
{

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachineWithState & gumballMachine);
	
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	bool CanRefill() override;

	std::string ToString() const override;
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachineWithState & gumballMachine);

	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	bool CanRefill() override;

	std::string ToString() const override;
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachineWithState & gumballMachine);

	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	bool CanRefill() override;

	std::string ToString() const override;
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachineWithState & gumballMachine);
	
	bool InsertQuarter() override;
	bool EjectQuarter() override;
	bool TurnCrank() override;
	bool Dispense() override;
	bool CanRefill() override;

	std::string ToString() const override;
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CGumballMachine : public IGumballMachineWithState
{
public:
	CGumballMachine(unsigned ballCount, unsigned maxQuarter);

	unsigned GetBallCount() const override;
	unsigned GetCoinsCount() const override;

	bool EjectQuarters() override;
	bool InsertQuarter() override;
	bool TurnCrank() override;

	bool Refill(unsigned numBalls) override;

	std::string ToString()const override;
private:

	bool AddCoin()  override;
	bool UseCoin() override;
	bool ReturnAllCoins() override;
	bool ReleaseBall() override;

	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;
private:
	unsigned m_ballsCount = 0;
	unsigned m_quarterCount = 0;
	const unsigned m_maxQuarterCount = 1;

	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState * m_state;
	
};

}
