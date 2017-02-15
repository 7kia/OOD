#pragma once

#include <iostream>
#include <memory>
#include <functional>

typedef std::function<void()> DanceBehavior;

namespace DanceBehaviorTypes
{
	void DanceWaltz()
	{
		std::cout << "I'm dancing waltz!!" << std::endl;
	}

	void DanceMinuet()
	{
		std::cout << "I'm dancing minuet!!" << std::endl;
	}

	void DanceNoWay() {}
};
