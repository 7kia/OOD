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

class CTea : public CBeverage
{
public:
	enum class SortType
	{
		Green ,
		Black ,
		Carcade ,
		White ,
	};

	CTea(SortType type)
		: CBeverage(GetTypeDescription(type) + " Tea")
		, m_type(type)
	{}

	double GetCost() const override 
	{
		return 30; 
	}
private:
	static std::string GetTypeDescription(SortType sort)
	{
		std::string description;
		switch (sort)
		{
		case SortType::Green:
			description = "Green";
			break;
		case SortType::Black:
			description = "Black";
			break;
		case SortType::Carcade:
			description = "Carcade";
			break;
		case SortType::White:
			description = "White";
			break;
		default:
			break;
		}
		return description;
	}
private:
	SortType m_type;
};

class CMilkshake : public CBeverage
{
public:
	enum class PortionType
	{
		Small,
		Medium,
		Big,
	};

	CMilkshake(PortionType type)
		: CBeverage(GetTypeDescription(type) + " milkshake")
		, m_type(type)
	{}

	double GetCost() const override 
	{ 
		double cost = 0.;
		switch (m_type)
		{
		case PortionType::Small:
			cost = 50.;
			break;
		case PortionType::Medium:
			cost = 60.;
			break;
		case PortionType::Big:
			cost = 80.;
			break;
		default:
			break;
		}

		return cost;
	}
private:
	static std::string GetTypeDescription(PortionType sort)
	{
		std::string description;
		switch (sort)
		{
		case PortionType::Small:
			description = "Small";
			break;
		case PortionType::Medium:
			description = "Medium";
			break;
		case PortionType::Big:
			description = "Big";
			break;
		default:
			break;
		}
		return description;
	}
private:
	PortionType m_type;
};
