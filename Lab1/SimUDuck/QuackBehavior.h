#pragma once

#include <iostream>
#include <memory>

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}
};

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeek!!!" << std::endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};
