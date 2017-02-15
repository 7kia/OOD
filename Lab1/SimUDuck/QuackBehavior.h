#pragma once

#include <iostream>
#include <memory>

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class CQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}
};

class CSqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeek!!!" << std::endl;
	}
};

class CMuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};
