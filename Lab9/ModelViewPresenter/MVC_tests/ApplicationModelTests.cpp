// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "ApplicationModelTests.h"

bool IsEqual(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

struct HarmonicFixture
{
	const float amplitude = 1.f;
	const FunctionType function = FunctionType::Sin;
	const float frequency = 1.f;
	const float phase = 0.f;

	CHarmonic harmonic;

	HarmonicFixture()
		: harmonic(amplitude, function, frequency, phase)
	{

	}
};


BOOST_FIXTURE_TEST_SUITE(HarmonicTest, HarmonicFixture)
BOOST_AUTO_TEST_CASE(have_type)
{
	BOOST_CHECK(harmonic.GetType() == function);
	harmonic.SetType(FunctionType::Cos);
	BOOST_CHECK(harmonic.GetType() == FunctionType::Cos);
}
BOOST_AUTO_TEST_CASE(have_amplitude)
{
	BOOST_CHECK_EQUAL(harmonic.GetAmplitude(), amplitude);
	const float newAmplitude = 3.f;
	harmonic.SetAmplitude(newAmplitude);
	BOOST_CHECK(harmonic.GetAmplitude() == newAmplitude);
}
BOOST_AUTO_TEST_CASE(have_frequency)
{
	BOOST_CHECK_EQUAL(harmonic.GetFrequency(), frequency);
	const float newFrequency = 3.1f;
	harmonic.SetFrequency(newFrequency);
	BOOST_CHECK(harmonic.GetFrequency() == newFrequency);

}
BOOST_AUTO_TEST_CASE(have_phase)
{
	BOOST_CHECK_EQUAL(harmonic.GetPhase(), phase);
	const float newPhase = 3.3f;
	harmonic.SetPhase(newPhase);
	BOOST_CHECK(harmonic.GetPhase() == newPhase);

}
BOOST_AUTO_TEST_CASE(can_calculate_value_to_point)
{
	std::vector<float> values;
	
	for (float x = -float(M_PI); x <= float(M_PI); x += float(M_PI_4))
	{
		values.push_back(harmonic.CalculateAt(x));
	}

	std::vector<float> expectedValues =
	{
		0.f,
		-0.707f,
		-1.f,
		-0.707f,
		0.2f,
		0.707f,
		1.f,
		0.707f,
	};

	for (size_t index = 0; index < expectedValues.size(); ++index)
	{
		IsEqual(values[index], expectedValues[index]);
	}

}
BOOST_AUTO_TEST_SUITE_END()// HarmonicFixture

struct HarmonicCollectionFixture
{
	std::vector<IHarmonicPtr> harmonics;
	CHarmonicCollection emptyHarmonicCollection;
	CHarmonicCollection harmonicCollection;

	HarmonicCollectionFixture()
	{
		harmonics.push_back(
			std::make_shared<CHarmonic>(
				2.f,
				FunctionType::Cos,
				1.f,
				1.5f
			)
		);
		harmonics.push_back(
			std::make_shared<CHarmonic>(
				9.f,
				FunctionType::Sin,
				0.5f,
				1.25f
				)
		);
		harmonics.push_back(
			std::make_shared<CHarmonic>(
				0.2f,
				FunctionType::Sin,
				0.25f,
				0.47f
				)
		);

		for (const auto & harmonic : harmonics)
		{
			harmonicCollection.AddHarmonic(harmonic);
		}
	}
};


BOOST_FIXTURE_TEST_SUITE(HarmonicCollection, HarmonicCollectionFixture)
BOOST_AUTO_TEST_CASE(add_harmonic)
{
	BOOST_CHECK_EQUAL(emptyHarmonicCollection.GetCount(), 0);
	emptyHarmonicCollection.AddHarmonic(harmonics[0]);
	BOOST_CHECK_EQUAL(emptyHarmonicCollection.GetCount(), 1);
	BOOST_CHECK_EQUAL(emptyHarmonicCollection.GetHarmonic(0), harmonics[0]);
}
BOOST_AUTO_TEST_CASE(delete_harmonic)
{
	const size_t deleteIndex = 1;
	BOOST_CHECK_EQUAL(harmonicCollection.GetCount(), 3);
	harmonicCollection.DeleteHarmonic(deleteIndex);

	BOOST_CHECK_EQUAL(harmonicCollection.GetCount(), 2);

	harmonics.erase(harmonics.begin() + deleteIndex);

	for (size_t index = 0; index < harmonicCollection.GetCount(); ++index)
	{
		BOOST_CHECK_EQUAL(harmonicCollection.GetHarmonic(index), harmonics[index]);
	}
}
BOOST_AUTO_TEST_CASE(throw_exception_if_index_out_of_range)
{
	BOOST_CHECK_THROW(emptyHarmonicCollection.GetHarmonic(0), std::out_of_range);
	BOOST_CHECK_THROW(emptyHarmonicCollection.GetHarmonic(1), std::out_of_range);
	BOOST_CHECK_THROW(emptyHarmonicCollection.DeleteHarmonic(0), std::out_of_range);

	BOOST_CHECK_THROW(harmonicCollection.GetHarmonic(3), std::out_of_range);
	BOOST_CHECK_THROW(harmonicCollection.GetHarmonic(4), std::out_of_range);
	BOOST_CHECK_THROW(harmonicCollection.DeleteHarmonic(3), std::out_of_range);
}
BOOST_AUTO_TEST_CASE(get_harmonic_count)
{
	BOOST_CHECK_EQUAL(emptyHarmonicCollection.GetCount(), 0);
}
BOOST_AUTO_TEST_SUITE_END()// HarmonicCollectionFixture