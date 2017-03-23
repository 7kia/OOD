#include "stdafx.h"
#include "Shapes\Circle.h"


struct Circle_
{
	const float expectedLength = 18.849f;
	const float expectedArea = 28.274f;

	const float expectedRadius = 3.f;
	const float expectedRadiusAfterAssigment = 5.f;

	const sf::Vector2f expectedPosition = { 1.f, 0.f };
	const sf::Vector2f expectedPositionAfterAssigment = { -1.f, 0.f };

	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const sf::Color expectedColorForSetVectorMethod;
	
	const sf::Color expectedColor;

	CCircle circle;

	Circle_()
		: expectedOutlineColor(10, 10, 10)
		, expectedFillColor(160, 160, 160)
		, expectedColorForSetVectorMethod(1, 2, 3)
		, expectedColor(4, 5, 6)
		, circle(expectedPosition, expectedRadius,
			expectedFillColor, expectedOutlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&circle));
}

BOOST_AUTO_TEST_CASE(has_color_outline_color)
{
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedOutlineColor);

	circle.SetOutlineColor(expectedColorForSetVectorMethod);
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedColorForSetVectorMethod);

	circle.SetOutlineColor(expectedColor);
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedColor);

}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedFillColor);

	circle.SetFillColor(expectedColorForSetVectorMethod);
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedColorForSetVectorMethod);

	circle.SetFillColor(expectedColor);
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedColor);
}

BOOST_AUTO_TEST_CASE(has_a_Radius)
{
	BOOST_CHECK_EQUAL(circle.GetRadius(), expectedRadius);

	circle.SetRadius(expectedRadiusAfterAssigment);
	BOOST_CHECK_EQUAL(circle.GetRadius(), expectedRadiusAfterAssigment);
}

BOOST_AUTO_TEST_CASE(has_a_position)
{
	VerifyVector2f(circle.GetPosition(), expectedPosition);

	circle.SetPositionCenter(expectedPositionAfterAssigment);
	VerifyVector2f(circle.GetPosition(), expectedPositionAfterAssigment);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK_EQUAL(circle.GetPerimeter(), expectedLength);
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK_EQUAL(circle.GetArea(), expectedArea);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(Circle:
	Fill color = #a0a0a0
	Perimeter = 18.8
	Area = 28.3
	Outline color = #0a0a0a00
	Position center = (1, 0)
	Radius = 3
)";
	BOOST_CHECK_EQUAL(circle.GetStringPresentation(), expectedString);
}
BOOST_AUTO_TEST_SUITE_END()


struct DefaultCircle_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;
	const float expectedRadius = 0.f;
	const sf::Vector2f expectedPosition = { 0.f, 0.f };
	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const CCircle circle;
	DefaultCircle_()
		: expectedOutlineColor(0, 0, 0)
		, expectedFillColor(0, 0, 0, 1)
	{}
};

BOOST_FIXTURE_TEST_SUITE(DefaultCircle, DefaultCircle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&circle));
}

BOOST_AUTO_TEST_CASE(has_color)
{
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedOutlineColor);
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(has_a_Radius)
{
	BOOST_CHECK_EQUAL(circle.GetRadius(), expectedRadius);
}

BOOST_AUTO_TEST_CASE(has_a_position)
{
	VerifyVector2f(circle.GetPosition(), expectedPosition);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK_EQUAL(circle.GetPerimeter(), expectedLength);
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK_EQUAL(circle.GetArea(), expectedArea);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(Circle:
	Fill color = #000000
	Perimeter = 0
	Area = 0
	Outline color = #000000
	Position center = (0, 0)
	Radius = 0
)";
	BOOST_CHECK_EQUAL(circle.GetStringPresentation(), expectedString);
}
BOOST_AUTO_TEST_SUITE_END()