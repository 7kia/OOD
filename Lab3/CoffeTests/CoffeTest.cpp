// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Beverages.h"
#include "Condiments.h"

using namespace std;

struct FirstTaskFixture
{
	std::stringstream stream;

	FirstTaskFixture()
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(FirstTask, FirstTaskFixture)// TODO : rename

BOOST_AUTO_TEST_CASE(Check_latte)
{
	{
		auto latte = make_unique<CLatte>(CLatte::Type::OnePortion);

		BOOST_CHECK_EQUAL(latte->GetDescription(), "Latte");
		BOOST_CHECK_EQUAL(latte->GetCost(), 90);
	}
	{
		auto latte = make_unique<CLatte>(CLatte::Type::DoublePortion);

		BOOST_CHECK_EQUAL(latte->GetDescription(), "Double Latte");
		BOOST_CHECK_EQUAL(latte->GetCost(), 130);
	}
}

BOOST_AUTO_TEST_CASE(Check_capuccino)
{
	{
		auto capuccino = make_unique<CCapuccino>(CCapuccino::Type::OnePortion);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 80);
	}
	{
		auto capuccino = make_unique<CCapuccino>(CCapuccino::Type::DoublePortion);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Double Capuccino");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 120);
	}
}

BOOST_AUTO_TEST_CASE(Check_tea)
{
	{
		auto tea = make_unique<CTea>(TeaType::Green);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Green Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(TeaType::Black);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Black Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(TeaType::Carcade);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Carcade Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(TeaType::White);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "White Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}

}

BOOST_AUTO_TEST_SUITE_END()

//
//BOOST_FIXTURE_TEST_SUITE(OwnDeleteObserver, OwnDeleteObserverFixture)
//
//BOOST_AUTO_TEST_CASE(observer_can_remove_itself_safely)
//{
//	weatherData.RegisterObserver(testObserver1, 1);
//	weatherData.RegisterObserver(testObserver2, 2);
//	weatherData.RegisterObserver(deletableObserver, 0);
//	
//	BOOST_CHECK_NO_THROW(weatherData.SetMeasurements(0.0, 0.0, 0.0));
//	std::string expectedString = R"(Test
//Test
//I remove myself
//)";
//	BOOST_CHECK_EQUAL(stream.str(), expectedString);
//	
//
//	stream.clear();
//	
//	BOOST_CHECK_NO_THROW(weatherData.SetMeasurements(0.0, 0.0, 0.0));
//	std::string expectedString2 = R"(Test
//Test
//I remove myself
//Test
//Test
//)";
//	BOOST_CHECK_EQUAL(stream.str(), expectedString2);
//	
//}
//
//BOOST_AUTO_TEST_SUITE_END()//OwnDeleteObserverFixture
//
//
//
//struct DuoVersionFixture
//{
//
//	std::stringstream stream;
//	CWeatherData innerStation;
//	CWeatherData outerStation;
//
//	CTestObserver display;
//
//	DuoVersionFixture()
//		: innerStation("Inner")
//		, outerStation("Outter")
//		, display(stream)
//	{
//	}
//
//};
//
//BOOST_FIXTURE_TEST_SUITE(DuoVersion, DuoVersionFixture)
//
//BOOST_AUTO_TEST_CASE(Check_work_duo_version)
//{
//	innerStation.RegisterObserver(display, 1);
//	outerStation.RegisterObserver(display, 1);
//
//	innerStation.SetMeasurements(0.10, 0.20, 0.30);
//	outerStation.SetMeasurements(10.10, 10.20, 10.30);
//
//	std::string expectedString = R"(InnerTest
//OutterTest
//)";
//
//	BOOST_CHECK_EQUAL(stream.str(), expectedString);
//}
//
//BOOST_AUTO_TEST_SUITE_END()//OwnDeleteObserverFixture