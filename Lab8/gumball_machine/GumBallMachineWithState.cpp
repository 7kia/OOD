#include "stdafx.h"
#include "GumBallMachineWithState.h"

using namespace std;
using namespace with_state;

CSoldState::CSoldState(IGumballMachineWithState & gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

bool CSoldState::InsertQuarter() 
{
	std::cout << "Please wait, we're already giving you a gumball\n";
	return false;
}

bool CSoldState::EjectQuarter() 
{
	if (m_gumballMachine.GetCoinsCount() == 0)
	{
		cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	else
	{
		m_gumballMachine.ReturnAllCoins();
		m_gumballMachine.SetNoQuarterState();
		return true;
	}
	return false;
}

bool CSoldState::TurnCrank() 
{
	std::cout << "Turning twice doesn't get you another gumball\n";
	return false;
}

bool CSoldState::Dispense() 
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

	return true;
}

bool CSoldState::CanRefill()
{
	return false;
}

std::string CSoldState::ToString() const 
{
	return "delivering a gumball";
}



CSoldOutState::CSoldOutState(IGumballMachineWithState & gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

bool CSoldOutState::InsertQuarter() 
{
	std::cout << "You can't insert a quarter, the machine is sold out\n";
	return false;
}

bool CSoldOutState::EjectQuarter() 
{
	if (m_gumballMachine.GetCoinsCount() == 0)
	{
		cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	else
	{
		m_gumballMachine.ReturnAllCoins();
		m_gumballMachine.SetNoQuarterState();
		return true;
	}
	return false;
}

bool CSoldOutState::TurnCrank() 
{
	std::cout << "You turned but there's no gumballs\n";
	return false;
}

bool CSoldOutState::Dispense() 
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else if (m_gumballMachine.GetCoinsCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
	return false;
}

bool CSoldOutState::CanRefill()
{
	return true;
}


std::string CSoldOutState::ToString() const 
{
	return "sold out";
}



CHasQuarterState::CHasQuarterState(IGumballMachineWithState & gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

bool CHasQuarterState::InsertQuarter() 
{
	m_gumballMachine.AddCoin();
	return true;
}

bool CHasQuarterState::EjectQuarter() 
{
	std::cout << "Quarter returned\n";
	m_gumballMachine.ReturnAllCoins();
	m_gumballMachine.SetNoQuarterState();
	return true;
}

bool CHasQuarterState::TurnCrank() 
{
	cout << "You turned...\n";
	m_gumballMachine.UseCoin();
	m_gumballMachine.SetSoldState();
	return true;
}

bool CHasQuarterState::Dispense() 
{
	std::cout << "No gumball dispensed\n";
	return false;
}

bool CHasQuarterState::CanRefill()
{
	return true;
}

std::string CHasQuarterState::ToString() const 
{
	return "waiting for turn of crank";
}



CNoQuarterState::CNoQuarterState(IGumballMachineWithState & gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

bool CNoQuarterState::InsertQuarter() 
{
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.AddCoin();
	m_gumballMachine.SetHasQuarterState();
	return true;
}

bool CNoQuarterState::EjectQuarter() 
{
	std::cout << "You haven't inserted a quarter\n";
	return false;
}

bool CNoQuarterState::TurnCrank() 
{
	std::cout << "You turned but there's no quarter\n";
	return false;
}

bool CNoQuarterState::Dispense() 
{
	std::cout << "You need to pay first\n";
	return false;
}

bool CNoQuarterState::CanRefill()
{
	return true;
}

std::string CNoQuarterState::ToString() const 
{
	return "waiting for quarter";
}


CGumballMachine::CGumballMachine(unsigned ballCount, unsigned maxQuarter)
	: m_soldState(*this)
	, m_soldOutState(*this)
	, m_noQuarterState(*this)
	, m_hasQuarterState(*this)
	, m_state(&m_soldOutState)
	, m_ballsCount(ballCount)
	, m_maxQuarterCount(maxQuarter)
{
	if (m_ballsCount > 0)
	{
		m_state = &m_noQuarterState;
	}
}


bool CGumballMachine::Refill(unsigned numBalls)
{
	if (m_state->CanRefill())
	{
		m_ballsCount = numBalls;
		if (m_quarterCount == 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetHasQuarterState();
		}
		return true;
	}
	return false;
}

bool CGumballMachine::EjectQuarters() 
{
	return m_state->EjectQuarter();
}

bool CGumballMachine::InsertQuarter() 
{
	return m_state->InsertQuarter();
}

bool CGumballMachine::TurnCrank() 
{
	if (m_state->TurnCrank())
	{
		return m_state->Dispense();
	}
	return false;
}

std::string CGumballMachine::ToString()const 
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");

	return (fmt % m_ballsCount % (m_ballsCount != 1 ? "s" : "") % m_state->ToString()).str();
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_ballsCount;
}

unsigned CGumballMachine::GetCoinsCount() const
{
	return m_quarterCount;
}

void CGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}

void CGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}

void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}

void CGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}


void CGumballMachine::AddCoin()
{
	if (m_quarterCount < m_maxQuarterCount)
	{
		++m_quarterCount;
		cout << "You inserted a quarter\n";
	}
	else
	{
		auto fmt = boost::format("You can't add more than %1 coins");
		cout << fmt % m_maxQuarterCount << endl;
	}
}

void CGumballMachine::UseCoin()
{
	if (m_quarterCount != 0)
	{
		--m_quarterCount;
	}
}

void CGumballMachine::ReturnAllCoins()
{
	auto fmt = boost::format("%1% quater%2% returned");
	cout << fmt % m_quarterCount % (m_quarterCount == 0 ? "" : "s") << endl;
	m_quarterCount = 0;
}

void CGumballMachine::ReleaseBall()
{
	if (m_ballsCount != 0)
	{
		cout << "A gumball comes rolling out the slot...\n";
		--m_ballsCount;
	}
}