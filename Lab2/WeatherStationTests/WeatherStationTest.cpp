// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"

struct OrderNotifyObserversFixture
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

	CTestWeatherData weatherData;
	CTestDisplay display1;
	CTestDisplay display2;
	CTestDisplay display3;
	CTestDisplay display4;

	OrderNotifyObserversFixture()
	{
		weatherData.RegisterObserver(display1, 1);
		weatherData.RegisterObserver(display2, 3);
		weatherData.RegisterObserver(display3, 2);
		weatherData.RegisterObserver(display4, 1);
	}

};

BOOST_FIXTURE_TEST_SUITE(OrderNotifyObservers, OrderNotifyObserversFixture)// TODO : rename

BOOST_AUTO_TEST_CASE(Chech_order)
{
	weatherData.MeasurementsChanged();

	BOOST_CHECK_EQUAL(display2.m_acceptIndex, 1);
	BOOST_CHECK_EQUAL(display3.m_acceptIndex, 2);
	BOOST_CHECK_EQUAL(display4.m_acceptIndex, 3);
	BOOST_CHECK_EQUAL(display1.m_acceptIndex, 4);
}

BOOST_AUTO_TEST_SUITE_END()


class CTestObserver : public IObserver<SWeatherInfo>
{
public:
	CTestObserver(std::ostream & stream)
		: m_stream(stream)
	{
	}

	void Update(SWeatherInfo const& data)
	{
		m_stream << data.nameStation << "Test" << endl;
	}
private:
	ostream & m_stream;
};

struct OwnDeleteObserverFixture
{
	class COwnDeleteObserver : public IObserver<SWeatherInfo>
	{
	public:
		COwnDeleteObserver(IObservable<SWeatherInfo> & observable, std::ostream & stream)
			: m_observable(observable)
			, m_stream(stream)
		{
		}

		void Update(SWeatherInfo const& data)
		{
			m_observable.RemoveObserver(*this);
			m_stream << "I remove myself" << endl;
		}
	private:
		IObservable<SWeatherInfo> & m_observable;
		ostream & m_stream;
	};

	std::stringstream stream;
	CWeatherData weatherData;
	CTestObserver testObserver1;
	CTestObserver testObserver2;
	COwnDeleteObserver deletableObserver;

	OwnDeleteObserverFixture()
		: deletableObserver(weatherData, stream)
		, testObserver1(stream)
		, testObserver2(stream)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(OwnDeleteObserver, OwnDeleteObserverFixture)

BOOST_AUTO_TEST_CASE(observer_can_remove_itself_safely)
{
	weatherData.RegisterObserver(testObserver1, 1);
	weatherData.RegisterObserver(testObserver2, 2);
	weatherData.RegisterObserver(deletableObserver, 0);
	
	BOOST_CHECK_NO_THROW(weatherData.SetMeasurements(0.0, 0.0, 0.0));
	std::string expectedString = R"(Test
Test
I remove myself
)";
	BOOST_CHECK_EQUAL(stream.str(), expectedString);
	

	stream.clear();
	
	BOOST_CHECK_NO_THROW(weatherData.SetMeasurements(0.0, 0.0, 0.0));
	std::string expectedString2 = R"(Test
Test
I remove myself
Test
Test
)";
	BOOST_CHECK_EQUAL(stream.str(), expectedString2);
	
}

BOOST_AUTO_TEST_SUITE_END()//OwnDeleteObserverFixture



struct DuoVersionFixture
{

	std::stringstream stream;
	CWeatherData innerStation;
	CWeatherData outerStation;

	CTestObserver display;

	DuoVersionFixture()
		: innerStation("Inner")
		, outerStation("Outter")
		, display(stream)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(DuoVersion, DuoVersionFixture)

BOOST_AUTO_TEST_CASE(Check_work_duo_version)
{
	innerStation.RegisterObserver(display, 1);
	outerStation.RegisterObserver(display, 1);

	innerStation.SetMeasurements(0.10, 0.20, 0.30);
	outerStation.SetMeasurements(10.10, 10.20, 10.30);

	std::string expectedString = R"(InnerTest
OutterTest
)";

	BOOST_CHECK_EQUAL(stream.str(), expectedString);
}

BOOST_AUTO_TEST_SUITE_END()//OwnDeleteObserverFixture