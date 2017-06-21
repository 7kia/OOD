#pragma once
#include <math.h>
#include <iomanip>

namespace
{
	void CompareTxtFiles(std::istream& stream1, std::istream& stream2)
	{
		std::istream_iterator<char> begin1(stream1), end1;
		std::istream_iterator<char> begin2(stream2), end2;

		BOOST_CHECK_EQUAL_COLLECTIONS(begin1, end1, begin2, end2);
	}

	template <typename Ex, typename Fn>
	void VerifyException(Fn && fn, const std::string & expectedDescription)
	{
		BOOST_REQUIRE_THROW(
			fn(), 
			Ex, 
			[&](const Ex& e) {
				BOOST_CHECK_EQUAL(e.what(), expectedDescription);
				return e.what() == expectedDescription;
			}
		);
	}

}