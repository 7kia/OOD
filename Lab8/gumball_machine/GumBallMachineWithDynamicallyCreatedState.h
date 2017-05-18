#pragma once
#include <iostream>
#include "IGumballMachine.h"

namespace with_dynamic_state
{

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachineWithState & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			m_gumballMachine.SetNoQuarterState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachineWithState & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		std::cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachineWithState & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You can't insert another quarter\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned\n";
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachineWithState & gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
private:
	IGumballMachineWithState & m_gumballMachine;
};

class CGumballMachine : public IGumballMachineWithState
{
public:
	CGumballMachine(unsigned numBalls)
		: m_count(numBalls)
	{

		if (m_count > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}
	void EjectQuarter() override
	{
		m_currentState->EjectQuarter();
	}
	void InsertQuarter() override
	{
		m_currentState->InsertQuarter();
	}
	void TurnCrank() override
	{
		m_currentState->TurnCrank();
		m_currentState->Dispense();
	}
	std::string ToString()const override
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_currentState->ToString()).str();
	}
private:
	unsigned GetBallCount() const override
	{
		return m_count;
	}
	virtual void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	void SetSoldOutState() override
	{
		m_currentState.reset(new CSoldOutState(*this));
	}
	void SetNoQuarterState() override
	{
		m_currentState.reset(new CNoQuarterState(*this));
	}
	void SetSoldState() override
	{
		m_currentState.reset(new CSoldState(*this));
	}
	void SetHasQuarterState() override
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}
private:
	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;

};

}
