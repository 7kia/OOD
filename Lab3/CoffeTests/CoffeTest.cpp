// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


struct FirstTaskFixture
{
	std::stringstream stream;

	FirstTaskFixture()
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(FirstTask, FirstTaskFixture)

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
		auto tea = make_unique<CTea>(CTea::SortType::Green);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Green Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(CTea::SortType::Black);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Black Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(CTea::SortType::Carcade);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Carcade Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}
	{
		auto tea = make_unique<CTea>(CTea::SortType::White);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "White Tea");
		BOOST_CHECK_EQUAL(tea->GetCost(), 30);
	}

}

BOOST_AUTO_TEST_CASE(Check_milkshake)
{
	{
		auto tea = make_unique<CMilkshake>(CMilkshake::PortionType::Small);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Small milkshake");
		BOOST_CHECK_EQUAL(tea->GetCost(), 50);
	}
	{
		auto tea = make_unique<CMilkshake>(CMilkshake::PortionType::Medium);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Medium milkshake");
		BOOST_CHECK_EQUAL(tea->GetCost(), 60);
	}
	{
		auto tea = make_unique<CMilkshake>(CMilkshake::PortionType::Big);

		BOOST_CHECK_EQUAL(tea->GetDescription(), "Big milkshake");
		BOOST_CHECK_EQUAL(tea->GetCost(), 80);
	}

}

BOOST_AUTO_TEST_SUITE_END()// FirstTask



struct SecondTaskFixture
{
	std::stringstream stream;

	SecondTaskFixture()
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(SecondTask, SecondTaskFixture)

BOOST_AUTO_TEST_CASE(Check_cream)
{
	{
		auto latte = make_unique<CCream>(
			make_unique<CLatte>(CLatte::Type::OnePortion)
		);
			
		BOOST_CHECK_EQUAL(latte->GetDescription(), "Latte, cream");
		BOOST_CHECK_EQUAL(latte->GetCost(), 25 + 90);
	}
	{
		auto capuccino = make_unique<CCream>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
		);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, cream");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 25 + 80);
	}
}


BOOST_AUTO_TEST_CASE(Check_chocolate_pieces)
{
	{
		auto latte = make_unique<CChocolatePieces>(
			make_unique<CLatte>(CLatte::Type::OnePortion)
			, 1
			);

		BOOST_CHECK_EQUAL(latte->GetDescription(), "Latte, 1 chocolate pieces");
		BOOST_CHECK_EQUAL(latte->GetCost(), 10 * 1 + 90);
	}
	{
		auto capuccino = make_unique<CChocolatePieces>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
			, 3
			);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, 3 chocolate pieces");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 10 * 3 + 80);
	}
}

BOOST_AUTO_TEST_CASE(Check_max_chocolate_pieces)
{
	{
		auto capuccino = make_unique<CChocolatePieces>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
			, 5
			);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, 5 chocolate pieces");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 10 * 5 + 80);
	}
	{
		auto capuccino = make_unique<CChocolatePieces>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
			, 13
			);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, 5 chocolate pieces");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 10 * 5 + 80);
	}
}


BOOST_AUTO_TEST_CASE(Check_Liquor)
{
	{
		auto capuccino = make_unique<CLiquor>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
			, CLiquor::Type::Chocolate
			);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, Chocolate liquor");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 40 + 80);
	}
	{
		auto capuccino = make_unique<CLiquor>(
			make_unique<CCapuccino>(CCapuccino::Type::OnePortion)
			, CLiquor::Type::Nut
			);

		BOOST_CHECK_EQUAL(capuccino->GetDescription(), "Capuccino, Nut liquor");
		BOOST_CHECK_EQUAL(capuccino->GetCost(), 40 + 80);
	}
}
BOOST_AUTO_TEST_SUITE_END()// SecondTask