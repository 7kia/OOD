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

static std::map<TeaType, std::string> TeaTypeDescription
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
		: CBeverage(TeaTypeDescription.find(type)->second + " Tea")
		, m_type(type)
	{}

	double GetCost() const override 
	{
		return 30; 
	}

private:
	TeaType m_type;
};


enum class MilkshakePortionType
{
	Small ,
	Medium ,
	Big ,
};

static std::map<MilkshakePortionType, std::string>  MilkshakePortionDescription
{
	{ MilkshakePortionType::Small, "Small" }
	,{ MilkshakePortionType::Medium, "Medium" }
	,{ MilkshakePortionType::Big, "Big" }

};
// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionType type)
		: CBeverage(MilkshakePortionDescription.find(type)->second + " milkshake")
		, m_type(type)
	{}

	double GetCost() const override 
	{ 
		double cost = 0.;
		switch (m_type)
		{
		case MilkshakePortionType::Small:
			cost = 50.;
			break;
		case MilkshakePortionType::Medium:
			cost = 60.;
			break;
		case MilkshakePortionType::Big:
			cost = 80.;
			break;
		default:
			break;
		}

		return cost;
	}
private:
	MilkshakePortionType m_type;
};
