#pragma once

#include <cassert>
#include <vector>

#include "QuackBehavior.h"
#include "FlyBehavior.h"
#include "DanceBehavior.h"

class Duck
{
public:
	Duck(
		std::unique_ptr<IFlyBehavior> && flyBehavior
		, std::unique_ptr<IQuackBehavior> && quackBehavior
		, std::unique_ptr<IDanceBehavior> && danceBehavior
	)
		: m_quackBehavior(std::move(quackBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(std::move(flyBehavior));
		SetDanceBehavior(std::move(danceBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	virtual void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior> && flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}
	void SetDanceBehavior(std::unique_ptr<IDanceBehavior> && danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = std::move(danceBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() {};
private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(
			std::make_unique<FlyWithWings>()
			, std::make_unique<QuackBehavior>()
			, std::make_unique<DanceWaltz>()
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(
			std::make_unique<FlyWithWings>()
			, std::make_unique<QuackBehavior>()
			, std::make_unique<DanceMinuet>()
			)
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(
			std::make_unique<FlyNoWay>()
			, std::make_unique<MuteQuackBehavior>()
			, std::make_unique<DanceNoWay>()
		)
	{
	}
	void Display() const override
	{
		std::cout << "I'm deckoy duck" << std::endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(
			std::make_unique<FlyNoWay>()
			, std::make_unique<QuackBehavior>()
			, std::make_unique<DanceNoWay>()
		)
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(
			std::make_unique<FlyNoWay>()
			, std::make_unique<QuackBehavior>()
			, std::make_unique<DanceNoWay>()
			)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};