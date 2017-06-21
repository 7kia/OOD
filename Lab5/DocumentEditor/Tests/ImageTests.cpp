#include "stdafx.h"

#include <boost/filesystem.hpp>

#include "Document/DocumentItems/Image.h"
#include "Command/History.h"

#include "TestingFunction.h"

using namespace std;
using namespace boost;

struct imageFixture
{
	imageFixture()
		: fileName("testImage.txt")
		, width(100)
		, height(100)
		, history()
		, imagePath("images\\" + fileName)
		, image(imagePath, width, height, history)
	{}

	string fileName;
	unsigned width;
	unsigned height;
	CHistory history;
	string imagePath;
	CImage image;
};

BOOST_FIXTURE_TEST_SUITE(CImage_, imageFixture)
	BOOST_AUTO_TEST_CASE(throw_exception_if_source_image_is_not_accessible)
	{
		VerifyException<invalid_argument>(
			[&]() {
				CImage("C:\\Nothing_hm.png", 100, 100, history);
			},
			"Invalid file path or not accessible file"
		);
	}	
	BOOST_AUTO_TEST_CASE(can_get_width_and_height)
	{
		BOOST_CHECK_EQUAL(image.GetWidth(), width);
		BOOST_CHECK_EQUAL(image.GetHeight(), height);
	}
	BOOST_AUTO_TEST_CASE(can_resize_image)
	{
		const unsigned newWidth = 100;
		const unsigned newHeight = 200;
		image.Resize(newWidth, newHeight);
		BOOST_CHECK_EQUAL(image.GetWidth(), newWidth);
		BOOST_CHECK_EQUAL(image.GetHeight(), newHeight);
	}
	BOOST_AUTO_TEST_CASE(can_get_path)
	{
		BOOST_CHECK_EQUAL(image.GetPath(), imagePath);
	}
BOOST_AUTO_TEST_SUITE_END()