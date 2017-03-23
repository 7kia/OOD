#include "stdafx.h"
#include "Shapes\MyCPoint.h"

struct MyCPoint_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;

	const sf::Vector2f expectedPosition = { 1.f, 2.f };
	const sf::Vector2f expectedPositionAfterAssigment = { -1.f, 20.f };

	const sf::Color expectedColor;

	CMyPoint point;// TODO
	MyCPoint_()
		: expectedColor(4, 5, 6)
		, point(expectedPosition, expectedColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(MyCPoint1, MyCPoint_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&point));
}

BOOST_AUTO_TEST_CASE(has_a_length)//"$(TargetPath)" --log_level=test_suite
{
	BOOST_CHECK(IsEqual(point.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(not_has_a_area)
{
	BOOST_CHECK(IsEqual(point.GetArea(), expectedArea));
}

BOOST_AUTO_TEST_CASE(has_a_position)
{
	VerifyVector2f(point.GetPosition(), expectedPosition);

	point.SetPosition(expectedPositionAfterAssigment);
	VerifyVector2f(point.GetPosition(), expectedPositionAfterAssigment);

	point.SetPosition(expectedPositionAfterAssigment.x, expectedPositionAfterAssigment.y);
	VerifyVector2f(point.GetPosition(), expectedPositionAfterAssigment);
}

BOOST_AUTO_TEST_SUITE_END()


struct DefaultMyCPoint_
{
	const float expectedLength = 0.f;
	const float expectedArea = 0.f;
	const sf::Color expectedColor;
	const CMyPoint point;
	DefaultMyCPoint_()
		: expectedColor(0, 0, 0, 0)
	{}

};
BOOST_FIXTURE_TEST_SUITE(DefaultMyCPoint, DefaultMyCPoint_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&point));
}

BOOST_AUTO_TEST_CASE(not_has_a_length)//"$(TargetPath)" --log_level=test_suite
{
	BOOST_CHECK(IsEqual(point.GetPerimeter(), expectedLength));
}

BOOST_AUTO_TEST_CASE(not_has_a_area)
{
	BOOST_CHECK(IsEqual(point.GetArea(), expectedArea));
}


BOOST_AUTO_TEST_SUITE_END()


