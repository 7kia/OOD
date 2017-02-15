#pragma once

#include <iostream>
#include <memory>
#include <functional>

typedef std::function<void()> QuackBehavior;

namespace QuackBehaviorTypes
{
	void Quack()
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}

	void Squeak()
	{
		std::cout << "Squeek!!!" << std::endl;
	}

	void MuteQuack() {}
};
