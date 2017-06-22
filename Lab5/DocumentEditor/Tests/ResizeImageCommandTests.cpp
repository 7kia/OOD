#include "stdafx.h"
#include "Document/DocumentCommands/ResizeImageCommand.h"

using namespace std;

struct ResizeImageFixture
{
	ResizeImageFixture()
		: width(10)
		, height(21)
		, newWidth(90)
		, newHeight(35)
		, oldWidth(width)
		, oldHeight(height)
		, command(width, height, newWidth, newHeight)
	{
	}
	unsigned width;
	unsigned height;
	unsigned newWidth;
	unsigned newHeight;
	unsigned oldWidth;
	unsigned oldHeight;

	CResizeImageCommand command;
};

BOOST_FIXTURE_TEST_SUITE(CResizeImageCommand_tests, ResizeImageFixture)
BOOST_AUTO_TEST_CASE(can_execute_and_unexecute)
{
	command.Execute();
	BOOST_CHECK_EQUAL(width, newWidth);
	BOOST_CHECK_EQUAL(height, newHeight);

	command.Unexecute();
	BOOST_CHECK_EQUAL(width, oldWidth);
	BOOST_CHECK_EQUAL(height, oldHeight);
}
BOOST_AUTO_TEST_SUITE_END()