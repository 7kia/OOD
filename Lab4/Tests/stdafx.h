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


#include "..\Shapes\Shapes.h"
// TODO : delete functions fix in tests stdafx.h

// TODO: reference additional headers your program requires here
bool IsEqual(float a, float b);
void VerifyVector2f(const sf::Vector2f & vector, const sf::Vector2f & expectedVector);
void VerifyColor(const sf::Color & color, const sf::Color & myColor);
void VerifySize(const SSize & size, const SSize & expectedSize);