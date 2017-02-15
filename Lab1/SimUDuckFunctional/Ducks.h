#pragma once

#include <cassert>
#include <vector>

#include "QuackBehavior.h"
#include "FlyBehavior.h"
#include "DanceBehavior.h"

class CDuck
{
public:
	CDuck(
		FlyBehavior const & flyBehavior
		, QuackBehavior const & quackBehavior
		, DanceBehavior const & danceBehavior
	)
		: m_quackBehavior(quackBehavior)
	{
		SetFlyBehavior(flyBehavior);
		SetDanceBehavior(danceBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	virtual void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(FlyBehavior const & flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(DanceBehavior const & danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}
	virtual void Display() const = 0;
	virtual ~CDuck() {};
private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(
			FlyBehaviorTypes::FlyWithWings
			, QuackBehaviorTypes::Quack
			, DanceBehaviorTypes::DanceWaltz
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck()
		: CDuck(
			FlyBehaviorTypes::FlyWithWings
			, QuackBehaviorTypes::Quack
			, DanceBehaviorTypes::DanceMinuet
			)
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

class CDeckoyDuck : public CDuck
{
public:
	CDeckoyDuck()
		: CDuck(
			FlyBehaviorTypes::FlyNoWay
			, QuackBehaviorTypes::MuteQuack
			, DanceBehaviorTypes::DanceNoWay
		)
	{
	}
	void Display() const override
	{
		std::cout << "I'm deckoy duck" << std::endl;
	}
};

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(
			FlyBehaviorTypes::FlyNoWay
			, QuackBehaviorTypes::Quack
			, DanceBehaviorTypes::DanceNoWay
		)
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

class CModelDuck : public CDuck
{
public:
	CModelDuck()
		: CDuck(
			FlyBehaviorTypes::FlyNoWay
			, QuackBehaviorTypes::Quack
			, DanceBehaviorTypes::DanceNoWay
			)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};