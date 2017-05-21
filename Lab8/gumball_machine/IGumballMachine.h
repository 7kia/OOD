#pragma once


class IState
{
public:
	virtual bool InsertQuarter() = 0;
	virtual bool EjectQuarter() = 0;
	virtual bool TurnCrank() = 0;
	virtual bool Dispense() = 0;
	virtual bool CanRefill() = 0;
	virtual std::string ToString()const = 0;
	virtual ~IState() = default;
};

class IGumballMachine
{
public:
	virtual ~IGumballMachine() = default;

	virtual unsigned GetBallCount()const = 0;
	virtual unsigned GetCoinsCount() const = 0;

	virtual void ReleaseBall() = 0;
	virtual void AddCoin() = 0;
	virtual void UseCoin() = 0;
	virtual void ReturnAllCoins() = 0;

	virtual bool Refill(unsigned numBalls) = 0;

	virtual bool EjectQuarters() = 0;
	virtual bool InsertQuarter() = 0;
	virtual bool TurnCrank() = 0;
	virtual std::string ToString() const = 0;


};

class IGumballMachineWithState : public IGumballMachine
{
public:

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;
};