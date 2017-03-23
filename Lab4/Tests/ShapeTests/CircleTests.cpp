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
	VerifyColor(circle.GetOutlineColor(), expectedOutlineColor);

	circle.SetOutlineColor(expectedColorForSetVectorMethod);
	VerifyColor(circle.GetOutlineColor(), expectedColorForSetVectorMethod);

	circle.SetOutlineColor(expectedColor);
	VerifyColor(circle.GetOutlineColor(), expectedColor);

}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	VerifyColor(circle.GetFillColor(), expectedFillColor);

	circle.SetFillColor(expectedColorForSetVectorMethod);
	VerifyColor(circle.GetFillColor(), expectedColorForSetVectorMethod);

	circle.SetFillColor(expectedColor);
	VerifyColor(circle.GetFillColor(), expectedColor);
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
	BOOST_CHECK(IsEqual(circle.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK(IsEqual(circle.GetArea(), expectedArea));
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
		: expectedOutlineColor(0, 0, 0, 0)
		, expectedFillColor(0, 0, 0, 0)
	{}
};

BOOST_FIXTURE_TEST_SUITE(DefaultCircle, DefaultCircle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&circle));
}

BOOST_AUTO_TEST_CASE(has_color)
{
	VerifyColor(circle.GetOutlineColor(), expectedOutlineColor);
	VerifyColor(circle.GetFillColor(), expectedFillColor);
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

BOOST_AUTO_TEST_SUITE_END()