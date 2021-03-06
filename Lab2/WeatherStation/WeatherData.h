﻿#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string nameStation;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};



class CWeatherStatistic
{

public:
	CWeatherStatistic(std::string const& statisticName)
		: m_statisticName(statisticName)
	{
	}

	void Update(double const& newValue)
	{
		if (m_minValue > newValue)
		{
			m_minValue = newValue;
		}
		if (m_maxValue < newValue)
		{
			m_maxValue = newValue;
		}

		m_accValue += newValue;
		++m_countAcc;
	}

	void PrintStatistics() const
	{
		std::cout << "- " << m_statisticName << std::endl;
		std::cout << "Max: " << m_maxValue << std::endl;
		std::cout << "Min: " << m_minValue << std::endl;
		std::cout << "Average: " << m_accValue / m_countAcc << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0.f;
	size_t m_countAcc = 0;
	std::string m_statisticName;
};



class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStat("Temperature")
		, m_humidityStat("Humidity")
		, m_pressureStat("Pressure")
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStat.Update(data.temperature);
		m_humidityStat.Update(data.humidity);
		m_pressureStat.Update(data.pressure);

		m_temperatureStat.PrintStatistics();
		m_humidityStat.PrintStatistics();
		m_pressureStat.PrintStatistics();
	}

	CWeatherStatistic m_temperatureStat;
	CWeatherStatistic m_humidityStat;
	CWeatherStatistic m_pressureStat;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(const std::string & name = "")
		: m_stationName(name)
	{

	}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

	std::string GetName() const
	{
		return m_stationName;
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.nameStation = GetName();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	

	std::string m_stationName;
};
