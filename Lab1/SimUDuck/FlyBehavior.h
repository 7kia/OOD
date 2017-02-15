#pragma once


#include <iostream>
#include <memory>

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I'm flying with wings!!" << std::endl;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};
