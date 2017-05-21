#include "stdafx.h"
#include "gumball_machine_tests.h"


struct NewGumballMachineFixture
{
	naive::CGumballMachine machine;

	GumballMachineFixture()
		: machine(2)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(New_machine, GumballMachineFixture)

BOOST_AUTO_TEST_CASE(Can_get_info)
{
	BOOST_CHECK_EQUAL(machine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: 2 gumballs
Machine is waiting for quarter
)");
}

BOOST_AUTO_TEST_CASE(Can_insert_quarter)
{
	machine.Insert
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

BOOST_AUTO_TEST_CASE(can_refill)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()
