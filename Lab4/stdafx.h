// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <SFML\Graphics.hpp>

#include <stdio.h>
#include <tchar.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>

#include <boost/algorithm/string/replace.hpp>

#define BOOST_TEST_INCLUDED
#pragma warning (disable: 4702)
#include <boost/test/unit_test.hpp>

// TODO : delete functions fix in tests stdafx.h
static bool IsEqual(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

static void VerifyVector2f(const sf::Vector2f & vector, const sf::Vector2f & expectedVector)
{
	BOOST_CHECK(IsEqual(vector.x, expectedVector.x));
	BOOST_CHECK(IsEqual(vector.y, expectedVector.y));
}

static  void VerifyColor(const sf::Color & color, const sf::Color & myColor)
{
	BOOST_CHECK_EQUAL(color.r, myColor.r);
	BOOST_CHECK_EQUAL(color.g, myColor.g);
	BOOST_CHECK_EQUAL(color.b, myColor.b);
	BOOST_CHECK_EQUAL(color.a, myColor.a);

}

// TODO: reference additional headers your program requires here
