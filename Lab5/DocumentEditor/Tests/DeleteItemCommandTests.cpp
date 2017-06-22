#include "stdafx.h"
#include "Document/DocumentCommands/DeleteItemCommand.h"
#include "Command/History.h"
#include "Document/DocumentItems/Paragraph.h"
#include "Document/DocumentItems/DocumentItem.h"

#include <memory.h>

using namespace std;

struct DeleteItemFixture
{
	DeleteItemFixture()
	{
		for (size_t i = 0; i < countItems; ++i)
		{
			auto pParagraph = make_shared<CParagraph>(CParagraph("text " + to_string(i), history));
			item = make_shared<CDocumentItem>(pParagraph);

			items.push_back(item);
		}

		deleteFromEnd = make_shared<CDeleteItemCommand>(items, countItems - 1);
		deleteFromMiddle = make_shared<CDeleteItemCommand>(items, countItems / 2);
		deleteFromStart = make_shared<CDeleteItemCommand>(items, 0);
	}

	const size_t countItems = 5;
	CHistory history;
	vector<DocumentItemPtr> items;
	shared_ptr<CDeleteItemCommand> deleteFromStart;
	shared_ptr<CDeleteItemCommand> deleteFromMiddle;
	shared_ptr<CDeleteItemCommand> deleteFromEnd;
	shared_ptr<CDocumentItem> item;
};

BOOST_FIXTURE_TEST_SUITE(CDeleteItemCommand_tests, DeleteItemFixture)
BOOST_AUTO_TEST_CASE(can_delete_from_start)
{
	deleteFromStart->Execute();
	BOOST_CHECK_EQUAL(items.size(), countItems - 1);
	BOOST_CHECK_EQUAL(items[0]->GetParagraph()->GetText(), "text 1");

	deleteFromStart->Unexecute();
	BOOST_CHECK_EQUAL(items.size(), countItems);
	BOOST_CHECK_EQUAL(items[0]->GetParagraph()->GetText(), "text 0");

}
BOOST_AUTO_TEST_CASE(can_delete_from_middle)
{
	deleteFromMiddle->Execute();
	BOOST_CHECK_EQUAL(items.size(), countItems - 1);
	BOOST_CHECK_EQUAL(items[2]->GetParagraph()->GetText(), "text 3");

	deleteFromMiddle->Unexecute();
	BOOST_CHECK_EQUAL(items.size(), countItems);
	BOOST_CHECK_EQUAL(items[2]->GetParagraph()->GetText(), "text 2");

}
BOOST_AUTO_TEST_CASE(can_delete_from_end)
{
	deleteFromEnd->Execute();
	BOOST_CHECK_EQUAL(items.size(), countItems - 1);
	BOOST_CHECK_EQUAL(items.back()->GetParagraph()->GetText(), "text 3");

	deleteFromEnd->Unexecute();
	BOOST_CHECK_EQUAL(items.size(), countItems);
	BOOST_CHECK_EQUAL(items.back()->GetParagraph()->GetText(), "text 4");

}
BOOST_AUTO_TEST_SUITE_END()