#include "stdafx.h"
#include "Shapes\Rectangle.h"


struct Rectangle_
{
	const float expectedLength = 10.f;
	const float expectedArea = 6.f;

	const sf::Vector2f expectedPosition = { 1.f, 2.f };

	const float expectedWidth = 2.f;
	const float expectedHeight = 3.f;

	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const sf::Color expectedColorForSetVectorMethod;

	CRectangle rectangle;

	const sf::Color expectedColor;


	Rectangle_()
		: expectedOutlineColor(160, 160, 160)
		, expectedFillColor(10, 10, 10)
		, expectedColorForSetVectorMethod(1, 2, 3)
		, expectedColor(4, 5, 6)
		, rectangle(expectedPosition, expectedWidth, expectedHeight,
					expectedFillColor, expectedOutlineColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&rectangle));
}

BOOST_AUTO_TEST_CASE(has_color_outline_color)
{
	VerifyColor(rectangle.GetOutlineColor(), expectedOutlineColor);

	rectangle.SetOutlineColor(expectedColorForSetVectorMethod);
	VerifyColor(rectangle.GetOutlineColor(), expectedColorForSetVectorMethod);

	rectangle.SetOutlineColor(expectedColor);
	VerifyColor(rectangle.GetOutlineColor(), expectedColor);

}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	VerifyColor(rectangle.GetFillColor(), expectedFillColor);

	rectangle.SetFillColor(expectedColorForSetVectorMethod);
	VerifyColor(rectangle.GetFillColor(), expectedColorForSetVectorMethod);

	rectangle.SetFillColor(expectedColor);
	VerifyColor(rectangle.GetFillColor(), expectedColor);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK(IsEqual(rectangle.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK(IsEqual(rectangle.GetArea(), expectedArea));
}

BOOST_AUTO_TEST_CASE(has_a_position_which_is_left_top_point)
{
	VerifyVector2f(rectangle.GetLeftTopPoint(), expectedPosition);
}

BOOST_AUTO_TEST_SUITE_END()


struct DefaultRectangle_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;
	const sf::Vector2f expectedPosition = { 0.f, 0.f };
	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const CRectangle rectangle;
	DefaultRectangle_()
		: expectedOutlineColor(0, 0, 0, 0)
		, expectedFillColor(0, 0, 0, 0)
	{}
};

BOOST_FIXTURE_TEST_SUITE(DefaultRectangle, DefaultRectangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&rectangle));
}

BOOST_AUTO_TEST_CASE(has_color_outline_color)
{
	VerifyColor(rectangle.GetOutlineColor(), expectedOutlineColor);
}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	VerifyColor(rectangle.GetFillColor(), expectedFillColor);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK(IsEqual(rectangle.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK(IsEqual(rectangle.GetArea(), expectedArea));
}

BOOST_AUTO_TEST_CASE(has_a_position_which_is_left_top_point)
{
	VerifyVector2f(rectangle.GetLeftTopPoint(), expectedPosition);
}

BOOST_AUTO_TEST_SUITE_END()