#pragma once
#include <math.h>
#include <iomanip>

namespace
{
	template <typename Ex, typename Fn>
	void VerifyException(Fn && fn, const std::string & expectedDescription)
	{
		BOOST_CHECK_EXCEPTION(
			fn(), 
			Ex, 
			[&](const Ex& e) {
				BOOST_CHECK_EQUAL(e.what(), expectedDescription);
				return e.what() == expectedDescription;
			}
		);
	}

}