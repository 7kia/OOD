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
	virtual ~CDuck() {};
private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(
			std::make_unique<CFlyWithWings>()
			, std::make_unique<CQuackBehavior>()
			, std::make_unique<CDanceWaltz>()
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
			std::make_unique<CFlyWithWings>()
			, std::make_unique<CQuackBehavior>()
			, std::make_unique<CDanceMinuet>()
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
			std::make_unique<CFlyNoWay>()
			, std::make_unique<CMuteQuackBehavior>()
			, std::make_unique<CDanceNoWay>()
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
			std::make_unique<CFlyNoWay>()
			, std::make_unique<CQuackBehavior>()
			, std::make_unique<CDanceNoWay>()
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
			std::make_unique<CFlyNoWay>()
			, std::make_unique<CQuackBehavior>()
			, std::make_unique<CDanceNoWay>()
			)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};