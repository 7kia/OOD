#pragma once

#include <iostream>
#include <memory>
#include <functional>

typedef std::function<void()> FlyBehavior;

namespace FlyBehaviorTypes
{
	FlyBehavior FlyWithWings()
	{
		size_t flightsCount = 0;
		return [=]() mutable
		{
			std::cout << "I'm flying with wings!" << std::endl
				<< "It's my " << ++flightsCount << " flight" << std::endl;

		};
	}

	void FlyNoWay() {}
};
