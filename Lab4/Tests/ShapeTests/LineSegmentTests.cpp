#include "stdafx.h"
#include "Shapes/LineSegment.h"

struct LineSegment_
{
	const float expectedLength = 1.414f;
	const float expectedArea = 0.f;

	const sf::Color expectedFillColor;
	const sf::Color expectedColorForSetVectorMethod;

	const sf::Color expectedColor;

	const sf::Vector2f firstPosition = { 0.f, 0.f };
	const sf::Vector2f secondPosition = { 1.f, 1.f };
	const sf::Vector2f expectedPosition = { 2.f, -4.f };

	CLineSegment line;
	LineSegment_()
		: expectedFillColor(16, 16, 16)
		, expectedColorForSetVectorMethod(1, 2, 3)
		, expectedColor(4, 5, 6)
		, line(firstPosition, secondPosition, expectedFillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegment_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&line));
}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	VerifyColor(line.GetFillColor(), expectedFillColor);

	line.SetFillColor(expectedColorForSetVectorMethod);
	VerifyColor(line.GetFillColor(), expectedColorForSetVectorMethod);

	line.SetFillColor(expectedColor);
	VerifyColor(line.GetFillColor(), expectedColor);
}

BOOST_AUTO_TEST_CASE(has_first_point)
{
	VerifyVector2f(line.GetFirstPoint(), firstPosition);

	line.SetPositionFirstPoint(expectedPosition);
	VerifyVector2f(line.GetFirstPoint(), expectedPosition);
}

BOOST_AUTO_TEST_CASE(has_second_point)
{
	VerifyVector2f(line.GetSecondPoint(), secondPosition);

	line.SetPositionSecondPoint(expectedPosition);
	VerifyVector2f(line.GetSecondPoint(), expectedPosition);
}

BOOST_AUTO_TEST_CASE(has_a_length)//"$(TargetPath)" --log_level=test_suite
{
	BOOST_CHECK(IsEqual(line.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(not_has_a_area)
{
	BOOST_CHECK(IsEqual(line.GetArea(), expectedArea));
}

BOOST_AUTO_TEST_SUITE_END()


struct DefaultLineSegment_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;
	const sf::Color expectedFillColor;
	const CLineSegment line;
	DefaultLineSegment_()
		: expectedFillColor(0, 0, 0, 0)
	{}

};
BOOST_FIXTURE_TEST_SUITE(DefaultLineSegment, DefaultLineSegment_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&line));
}

BOOST_AUTO_TEST_CASE(has_color)
{
	VerifyColor(line.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(not_has_a_length)//"$(TargetPath)" --log_level=test_suite
{
	BOOST_CHECK(IsEqual(line.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(not_has_a_area)
{
	BOOST_CHECK(IsEqual(line.GetArea(), expectedArea));
}


BOOST_AUTO_TEST_SUITE_END()

