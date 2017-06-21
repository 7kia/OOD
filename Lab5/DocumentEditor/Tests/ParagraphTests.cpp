#include "stdafx.h"
#include "Document/DocumentItems/Paragraph.h"
#include "Command/History.h"

using namespace std;

struct paragraphFixture
{
	paragraphFixture()
		: oldText("text")
		, paragraph("text", history)
		, newText("new text")
	{}

	const std::string oldText;
	const std::string newText;

	CHistory history;
	CParagraph paragraph;
};

BOOST_FIXTURE_TEST_SUITE(CParagraph_, paragraphFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(have_preset_text)
		{
			BOOST_CHECK_EQUAL(paragraph.GetText(), oldText);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_set_text)
	{
		paragraph.SetText(newText);
		BOOST_CHECK_EQUAL(paragraph.GetText(), newText);
	}
	
	BOOST_AUTO_TEST_CASE(can_get_text)
	{
		paragraph.SetText(newText);
		BOOST_CHECK_EQUAL(paragraph.GetText(), newText);
	}

BOOST_AUTO_TEST_SUITE_END()
