#include "stdafx.h"
#include "Shapes\Triangle.h"


struct Triangle_
{
	const float expectedLength = 4.828f;
	const float expectedArea = 1.f;

	const sf::Vector2f firstPosition = { 1.f, 0.f };
	const sf::Vector2f secondPosition = { -1.f, 0.f };
	const sf::Vector2f thirdPosition = { 0.f, 1.f };
	const sf::Vector2f excpectedPosition = { 2.f, 9.f };

	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const sf::Color expectedColorForSetVectorMethod;
	const sf::Color expectedColor;

	CTriangle triangle;

	Triangle_()
		: expectedOutlineColor(10, 10, 10)
		, expectedFillColor(160, 160, 160)
		, expectedColorForSetVectorMethod(1, 2, 3)
		, expectedColor(4,5,6)
		, triangle(firstPosition, secondPosition, thirdPosition,
			expectedFillColor, expectedOutlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&triangle));
}

BOOST_AUTO_TEST_CASE(has_color_outline_color)
{
	VerifyColor(triangle.GetOutlineColor(), expectedOutlineColor);

	triangle.SetOutlineColor(expectedColorForSetVectorMethod);
	VerifyColor(triangle.GetOutlineColor(), expectedColorForSetVectorMethod);

	triangle.SetOutlineColor(expectedColor);
	VerifyColor(triangle.GetOutlineColor(), expectedColor);

}

BOOST_AUTO_TEST_CASE(has_color_fill_color)
{
	VerifyColor(triangle.GetFillColor(), expectedFillColor);

	triangle.SetFillColor(expectedColorForSetVectorMethod);
	VerifyColor(triangle.GetFillColor(), expectedColorForSetVectorMethod);

	triangle.SetFillColor(expectedColor);
	VerifyColor(triangle.GetFillColor(), expectedColor);

}

BOOST_AUTO_TEST_CASE(has_a_first_point)
{
	VerifyVector2f(triangle.GetFirstPoint(), firstPosition);

	triangle.SetPositionFirstPoint(excpectedPosition);
	VerifyVector2f(triangle.GetFirstPoint(), excpectedPosition);
}

BOOST_AUTO_TEST_CASE(has_a_second_point)
{
	VerifyVector2f(triangle.GetSecondPoint(), secondPosition);

	triangle.SetPositionSecondPoint(excpectedPosition);
	VerifyVector2f(triangle.GetSecondPoint(), excpectedPosition);
}

BOOST_AUTO_TEST_CASE(has_a_third_point)
{
	VerifyVector2f(triangle.GetThirdPoint(), thirdPosition);

	triangle.SetPositionThirdPoint(excpectedPosition);
	VerifyVector2f(triangle.GetThirdPoint(), excpectedPosition);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK(IsEqual(triangle.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK(IsEqual(triangle.GetArea(), expectedArea));
}

BOOST_AUTO_TEST_SUITE_END()


struct DefaultTriangle_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;

	const sf::Vector2f defaultPosition = { 0.f, 0.f };

	const sf::Color expectedOutlineColor;
	const sf::Color expectedFillColor;
	const CTriangle triangle;
	DefaultTriangle_()
		: expectedOutlineColor(0, 0, 0, 0)
		, expectedFillColor(0, 0, 0, 0)
	{}
};

BOOST_FIXTURE_TEST_SUITE(DefaultTriangle, DefaultTriangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&triangle));
}

BOOST_AUTO_TEST_CASE(has_color)
{
	VerifyColor(triangle.GetOutlineColor(), expectedOutlineColor);
	VerifyColor(triangle.GetFillColor(), expectedFillColor);
}


BOOST_AUTO_TEST_CASE(has_a_first_point)
{
	VerifyVector2f(triangle.GetFirstPoint(), defaultPosition);
}

BOOST_AUTO_TEST_CASE(has_a_second_point)
{
	VerifyVector2f(triangle.GetSecondPoint(), defaultPosition);
}

BOOST_AUTO_TEST_CASE(has_a_third_point)
{
	VerifyVector2f(triangle.GetThirdPoint(), defaultPosition);
}

BOOST_AUTO_TEST_CASE(has_a_length)
{
	BOOST_CHECK_EQUAL(triangle.GetPerimeter(), expectedLength);
}

BOOST_AUTO_TEST_CASE(has_a_area)
{
	BOOST_CHECK_EQUAL(triangle.GetArea(), expectedArea);
}

BOOST_AUTO_TEST_SUITE_END()