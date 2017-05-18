// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gumball_machine_tests.h"

struct ExampleFixture
{
	ExampleFixture()
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(Example, ExampleFixture)

BOOST_AUTO_TEST_CASE(Chech_order)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()


struct GumballMachineFixture
{
	naive::CGumballMachine naiveGumballMachine;
	with_state::CGumballMachine stateGumballMachine;
	with_dynamic_state::CGumballMachine dynamicStateGumballMachine;

	GumballMachineFixture()
		: naiveGumballMachine(2)
		, stateGumballMachine(2)
		, dynamicStateGumballMachine(2)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(New_machine, GumballMachineFixture)

BOOST_AUTO_TEST_CASE(Can_get_info)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(Can_insert_quarter)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(not_quarter)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(not_release_ball)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()
