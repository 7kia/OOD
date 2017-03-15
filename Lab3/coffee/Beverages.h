#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	enum class Type
	{
		OnePortion,
		DoublePortion,
	};

	CCapuccino(Type type)
		: CCoffee((type == Type::OnePortion) ? "Capuccino" : "Double Capuccino")
		, m_type(type)
	{}

	double GetCost() const override 
	{
		double cost = (m_type == Type::OnePortion) ? 80 : 120;
		return cost;
	}


private:
	Type m_type;
};

// Латте
class CLatte : public CCoffee
{
public:
	enum class Type
	{
		OnePortion ,
		DoublePortion ,
	};

	CLatte(Type type)
		: CCoffee((type == Type::OnePortion) ? "Latte" : "Double Latte")
		, m_type(type)
	{}

	double GetCost() const override 
	{
		double cost = (m_type == Type::OnePortion) ? 90 : 130;
		return cost;
	}

private:
	Type m_type;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea() 
		:CBeverage("Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
