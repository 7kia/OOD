#include "stdafx.h"
#include "NaiveGumBallMachine.h"

using namespace std;
using namespace naive;

CGumballMachine::CGumballMachine(unsigned ballCount, unsigned maxQuarter)
	: m_state(ballCount > 0 ? State::NoQuarter : State::SoldOut)
	, m_ballsCount(ballCount)
	, m_maxQuarterCount(maxQuarter)
{
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_ballsCount;
}

unsigned CGumballMachine::GetCoinsCount() const
{
	return m_quarterCount;
}

bool CGumballMachine::InsertQuarter()
{
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
		AddCoin();
		m_state = State::HasQuarter;
		return true;
	case State::HasQuarter:
		AddCoin();
		break;
	case State::Sold:
		AddCoin();
		break;
	}

	return false;
}

bool CGumballMachine::EjectQuarters()
{
	switch (m_state)
	{
	case State::HasQuarter:
		ReturnAllCoins();
		m_state = State::NoQuarter;
		return true;
	case State::NoQuarter:
		cout << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
	case State::SoldOut:
		if (m_quarterCount == 0)
		{
			cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
		else
		{
			ReturnAllCoins();
			m_state = State::NoQuarter;
			return true;
		}
		break;
	}

	return false;
}

bool CGumballMachine::TurnCrank()
{
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		cout << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		cout << "You turned...\n";
		UseCoin();
		m_state = State::Sold;
		Dispense();
		return true;
	case State::Sold:
		cout << "Turning twice doesn't get you another gumball\n";
		break;
	}

	return false;
}

bool CGumballMachine::Refill(unsigned numBalls)
{
	if (m_state != State::Sold)
	{
		m_ballsCount = numBalls;
		if (m_quarterCount == 0)
		{
			m_state = State::NoQuarter;
		}
		else
		{
			m_state = State::HasQuarter;
		}
		return true;
	}
	return false;
}

string CGumballMachine::ToString()const
{
	string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_ballsCount % (m_ballsCount != 1 ? "s" : "") % state).str();
}

void CGumballMachine::Dispense()
{
	switch (m_state)
	{
	case State::Sold:
		ReleaseBall();
		if (m_ballsCount == 0)
		{
			cout << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else
		{
			m_state = State::NoQuarter;
		}
		break;
	case State::NoQuarter:
		cout << "You need to pay first\n";
		break;
	case State::SoldOut:
		ReleaseBall();
		if (m_ballsCount == 0)
		{
			cout << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else if (m_quarterCount == 0)
		{
			m_state = State::NoQuarter;
		}
		else
		{
			m_state = State::HasQuarter;
		}
		break;
	case State::HasQuarter:
		cout << "No gumball dispensed\n";
		break;
	}
}

bool CGumballMachine::AddCoin()
{
	if (m_quarterCount < m_maxQuarterCount)
	{
		++m_quarterCount;
		cout << "You inserted a quarter\n";
		return true;
	}
	auto fmt = boost::format("You can't add more than %1 coins");
	cout << fmt % m_maxQuarterCount << endl;
	return false;
}

bool CGumballMachine::UseCoin()
{
	if (m_quarterCount != 0)
	{
		--m_quarterCount;
		return true;
	}
	return false;
}

bool CGumballMachine::ReturnAllCoins()
{
	auto fmt = boost::format("%1% quater%2% returned");
	const bool isQuarters = m_quarterCount == 0;
	cout << fmt % m_quarterCount % (m_quarterCount == 0 ? "" : "s") << endl;
	m_quarterCount = 0;
	return isQuarters;
}

bool CGumballMachine::ReleaseBall()
{
	if (m_ballsCount != 0)
	{
		cout << "A gumball comes rolling out the slot...\n";
		--m_ballsCount;
		return true;
	}
	return false;
}
