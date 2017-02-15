#pragma once


#include <iostream>
#include <memory>

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class CDanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing waltz!!" << std::endl;
	}
};

class CDanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing minuet!!" << std::endl;
	}
};

class CDanceNoWay : public IDanceBehavior
{
public:
	void Dance() override {}
};
