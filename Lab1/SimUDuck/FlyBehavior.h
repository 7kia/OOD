#pragma once


#include <iostream>
#include <memory>

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class CFlyWithWings : public IFlyBehavior
{
public:
	CFlyWithWings() : m_flightsCount(0)
	{
	}

	void Fly() override
	{
		std::cout << "I'm flying with wings!" << std::endl
			<< "It's my " << ++m_flightsCount << " flight" << std::endl;
	}

private:
	size_t m_flightsCount;
};

class CFlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};
