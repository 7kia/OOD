// stdafx.cpp : source file that includes just the standard includes
// bodies_tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// �������� ���������� boost test, ��� ������� main ����� ������������� ���� (��� ���������������� ���������������� ����������), 
// � �� ������������� boost-�� �� ���
#define BOOST_TEST_NO_MAIN 
// ���������� ���������� boost test
#include <boost/test/included/unit_test.hpp>

bool IsEqual(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

void VerifyVector2f(const sf::Vector2f & vector, const sf::Vector2f & expectedVector)
{
	BOOST_CHECK(IsEqual(vector.x, expectedVector.x));
	BOOST_CHECK(IsEqual(vector.y, expectedVector.y));
}

void VerifyColor(const sf::Color & color, const sf::Color & myColor)
{
	BOOST_CHECK_EQUAL(color.r, myColor.r);
	BOOST_CHECK_EQUAL(color.g, myColor.g);
	BOOST_CHECK_EQUAL(color.b, myColor.b);
	BOOST_CHECK_EQUAL(color.a, myColor.a);

}

void VerifySize(const SSize & size, const SSize & expectedSize)
{
	BOOST_CHECK(IsEqual(size.width, expectedSize.width));
	BOOST_CHECK(IsEqual(size.height, expectedSize.height));
}