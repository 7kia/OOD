#pragma once

#include "IBeverage.h"
#include <map>

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


enum class TeaType
{
	Green,
	Black,
	Carcade,
	White,
};

static std::map<TeaType, std::string> TypeDescription
{
	{ TeaType::Green, "Green" }
	,{ TeaType::Black, "Black" }
	,{ TeaType::Carcade, "Carcade" }
	,{ TeaType::White, "White" }
};
// Чай
class CTea : public CBeverage
{
public:
	

	CTea(TeaType type)
		: CBeverage(TypeDescription.find(type)->second + " Tea")
		, m_type(type)
	{}

	double GetCost() const override 
	{
		return 30; 
	}

private:
	TeaType m_type;
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
