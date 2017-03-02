// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"

struct WeatherStationFixture
{

	struct STestInfo : public SWeatherInfo
	{		
		size_t acceptIndex = 0;
	};

	class CTestDisplay : public IObserver<STestInfo>
	{
	private:
		/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
		*/
		void Update(STestInfo const& data) override
		{
			std::cout << "Current Temp " << data.temperature << std::endl;
			std::cout << "Current Hum " << data.humidity << std::endl;
			std::cout << "Current Pressure " << data.pressure << std::endl;
			std::cout << "----------------" << std::endl;

			m_acceptIndex = data.acceptIndex;
		}
	public:// For test
		size_t m_acceptIndex = 0;
	};

	class CTestObservable : public CObservable<STestInfo>
	{
	public:
		void NotifyObservers() override
		{
			STestInfo data = GetChangedData();
			for (auto iter = m_priority.rbegin(); iter != m_priority.rend(); ++iter)
			{
				std::cout << "Priority = " << iter->first << std::endl;

				++data.acceptIndex;
				iter->second->Update(data);
			}
		}
	};

	class CTestWeatherData : public CTestObservable
	{
	public:
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

			++m_acceptIndex;
			MeasurementsChanged();
		}
	private:
		double m_temperature = 0.0;
		double m_humidity = 0.0;
		double m_pressure = 760.0;
		// For test
		size_t m_acceptIndex = 0;
	protected:
		STestInfo GetChangedData()const override
		{
			STestInfo info;
			info.temperature = GetTemperature();
			info.humidity = GetHumidity();
			info.pressure = GetPressure();
			info.acceptIndex = m_acceptIndex;
			return info;
		}
	};

	CTestWeatherData wd;
	CTestDisplay d1;
	CTestDisplay d2;
	CTestDisplay d3;
	CTestDisplay d4;

	WeatherStationFixture()
	{
		wd.RegisterObserver(d1, 1);
		wd.RegisterObserver(d2, 3);
		wd.RegisterObserver(d3, 2);
		wd.RegisterObserver(d4, 1);
	}

};

BOOST_FIXTURE_TEST_SUITE(Weather_station, WeatherStationFixture)// TODO : rename

BOOST_AUTO_TEST_CASE(Template_1)
{
	wd.MeasurementsChanged();

	BOOST_CHECK(d2.m_acceptIndex == 1);
	BOOST_CHECK(d3.m_acceptIndex == 2);
	BOOST_CHECK(d4.m_acceptIndex == 3);
	BOOST_CHECK(d1.m_acceptIndex == 4);
}

BOOST_AUTO_TEST_SUITE_END()