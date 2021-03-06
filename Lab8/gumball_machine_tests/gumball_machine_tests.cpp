// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gumball_machine_tests.h"

#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>

template<typename MachineType>
struct MachineFixture
{
	const unsigned expectedBalls = 5;
	const unsigned expectedBallsAfterRefill = 16;

	MachineType machine;

	MachineFixture()
		: machine(expectedBalls, 5)
	{
	}
};

typedef boost::mpl::vector<MachineFixture<naive::CGumballMachine>,
	MachineFixture<with_state::CGumballMachine>,
	MachineFixture<with_dynamic_state::CGumballMachine>
> NewMachineFixtures;

BOOST_AUTO_TEST_SUITE(SoldOutState)
BOOST_FIXTURE_TEST_CASE_TEMPLATE(have_quarter, T, NewMachineFixtures, T)
{
	BOOST_CHECK_EQUAL(T::machine.GetCoinsCount(), 0);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(has_balls, T, NewMachineFixtures, T)
{
	BOOST_CHECK_EQUAL(T::machine.GetBallCount(), expectedBalls);
}
BOOST_AUTO_TEST_SUITE_END()

template<typename MachineType>
struct SoldOutStateFixture : public MachineFixture<MachineType>
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
typedef boost::mpl::vector<SoldOutStateFixture<naive::CGumballMachine>,
	SoldOutStateFixture<with_state::CGumballMachine>,
	SoldOutStateFixture<with_dynamic_state::CGumballMachine>
> SoldOutStateFixtures;

BOOST_AUTO_TEST_SUITE(SoldOutState)
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_not_insert_quarter, T, SoldOutStateFixtures, T)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), 0);
	BOOST_CHECK(!machine.InsertQuarter());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_eject_all_quarter, T, SoldOutStateFixtures, T)
{
	BOOST_CHECK(!machine.EjectQuarters());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_not_turn_crank, T, SoldOutStateFixtures, T)
{
	BOOST_CHECK(!machine.TurnCrank());
	BOOST_CHECK_EQUAL(machine.GetBallCount(), 0);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_refill_and_quarter_count_not_changes, T, SoldOutStateFixtures, T)
{
	BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_AUTO_TEST_SUITE_END()

template<typename MachineType>
struct NoQuarterStateFixture : public MachineFixture<MachineType>
{

};
typedef boost::mpl::vector<NoQuarterStateFixture<naive::CGumballMachine>,
	NoQuarterStateFixture<with_state::CGumballMachine>,
	NoQuarterStateFixture<with_dynamic_state::CGumballMachine>
> NoQuarterStateFixtures;

BOOST_AUTO_TEST_SUITE(NoQuarterState)
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_insert_quarter, T, NoQuarterStateFixtures, T)
	{
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
		BOOST_CHECK(machine.InsertQuarter());
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 1);
		BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
	}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(for_eject_quarter_do_nothing, T, NoQuarterStateFixtures, T)
	{
		BOOST_CHECK(!machine.EjectQuarters());
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
		BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
	}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(for_turn_crank_not_release_ball, T, NoQuarterStateFixtures, T)
	{
		BOOST_CHECK(!machine.TurnCrank());
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
		BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls);
	}
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_refill_and_quarter_count_not_changes, T, NoQuarterStateFixtures, T)
	{
		BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
		BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
	}
BOOST_AUTO_TEST_SUITE_END()


template<typename MachineType>
struct HasQuarterStateFixture : public MachineFixture<MachineType>
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
typedef boost::mpl::vector<HasQuarterStateFixture<naive::CGumballMachine>,
	HasQuarterStateFixture<with_state::CGumballMachine>,
	HasQuarterStateFixture<with_dynamic_state::CGumballMachine>
> HasQuarterStateFixtures;

BOOST_AUTO_TEST_SUITE(HasQuarter_state)
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_insert_quarter, T, HasQuarterStateFixtures, T)
{
	for (unsigned index = expectedQuarters; index < expectedBalls; ++index)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.GetCoinsCount(), std::min(index + 1, unsigned(expectedBalls)));
	}
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedBalls);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_eject_quarters, T, HasQuarterStateFixtures, T)
{
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters);
	BOOST_CHECK(machine.EjectQuarters());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), 0);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(for_turn_crank_release_ball, T, HasQuarterStateFixtures, T)
{
	BOOST_CHECK(machine.TurnCrank());
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters - 1);
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBalls - 1);
}
BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_refill_and_quarter_count_not_changes, T, HasQuarterStateFixtures, T)
{
	BOOST_CHECK(machine.Refill(expectedBallsAfterRefill));
	BOOST_CHECK_EQUAL(machine.GetBallCount(), expectedBallsAfterRefill);
	BOOST_CHECK_EQUAL(machine.GetCoinsCount(), expectedQuarters);
}
BOOST_AUTO_TEST_SUITE_END()
