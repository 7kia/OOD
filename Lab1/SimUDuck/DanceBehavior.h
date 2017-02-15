#pragma once


#include <iostream>
#include <memory>

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing waltz!!" << std::endl;
	}
};

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing minuet!!" << std::endl;
	}
};

class DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};
