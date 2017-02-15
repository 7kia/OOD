#pragma once

#include <iostream>
#include <memory>
#include <functional>

typedef std::function<void()> FlyBehavior;

namespace FlyBehaviorTypes
{
	void FlyWithWings()
	{
		std::cout << "I'm flying with wings!" << std::endl;
	}

	void FlyNoWay() {}
};
