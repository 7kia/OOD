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
	//BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()


struct GumballMachineFixture
{
	const unsigned expectedBalls = 5;
	const unsigned expectedBallsAfterRefill = 16;
	naive::CGumballMachine machine;
	//with_state::CGumballMachine stateGumballMachine;
	//with_dynamic_state::CGumballMachine dynamicStateGumballMachine;

	GumballMachineFixture()
		: machine(expectedBalls, 5)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(New_machine, GumballMachineFixture)

BOOST_AUTO_TEST_CASE(has_coins)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}

BOOST_AUTO_TEST_CASE(has_balls)
{
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
}

BOOST_AUTO_TEST_SUITE_END()

struct SoldOutStateFixture : public GumballMachineFixture
{
	const unsigned expectedBallsAfterRefill = 16;
	SoldOutStateFixture()
	{
		for (unsigned index = 0; index < expectedBalls; ++index)
		{
			machine.InsertQuarter();
			machine.TurnCrank();
		}
	};
};

BOOST_FIXTURE_TEST_SUITE(SoldOut_state, SoldOutStateFixture)
BOOST_AUTO_TEST_CASE(can_not_insert_quarter)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), 0);
	BOOST_CHECK(!machine.InsertQuarter());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_CASE(can_eject_all_quarter)
{
	BOOST_CHECK(!machine.EjectQuarters());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_CASE(can_not_turn_crank)
{
	BOOST_CHECK(!machine.TurnCrank());
	BOOST_CHECK_EQUAL(machine.GetBallCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_CASE(can_refill_and_quarter_count_not_changes)
{
	BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_SUITE_END()


struct NoQuarterStateFixture : public GumballMachineFixture
{

};

BOOST_FIXTURE_TEST_SUITE(NoQuarter_state, NoQuarterStateFixture)
BOOST_AUTO_TEST_CASE(can_insert_quarter)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	BOOST_CHECK(machine.InsertQuarter());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 1);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
}
BOOST_AUTO_TEST_CASE(for_eject_quarter_do_nothing)
{
	BOOST_CHECK(!machine.EjectQuarters());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
}
BOOST_AUTO_TEST_CASE(for_turn_crank_not_release_ball)
{
	BOOST_CHECK(!machine.TurnCrank());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
}
BOOST_AUTO_TEST_CASE(can_refill_and_quarter_count_not_changes)
{
	BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_SUITE_END()

struct HasQuarterStateFixture : public GumballMachineFixture
{
	const unsigned expectedQuarters = 2;
	HasQuarterStateFixture()
	{
		for (unsigned index = 0; index < expectedQuarters; ++index)
		{
			machine.InsertQuarter();
		}
	};
};

BOOST_FIXTURE_TEST_SUITE(HasQuarter_state, HasQuarterStateFixture)
BOOST_AUTO_TEST_CASE(can_insert_quarter)
{
	for (unsigned index = expectedQuarters; index < expectedBalls; ++index)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), std::min(index + 1, unsigned(expectedBalls)));
	}
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedBalls);
}
BOOST_AUTO_TEST_CASE(can_eject_quarters)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters);
	BOOST_CHECK(machine.EjectQuarters());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_CASE(for_turn_crank_release_ball)
{
	BOOST_CHECK(machine.TurnCrank());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters - 1);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls - 1);
}
BOOST_AUTO_TEST_CASE(can_refill_and_quarter_count_not_changes)
{
	BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters);
}
BOOST_AUTO_TEST_SUITE_END()
