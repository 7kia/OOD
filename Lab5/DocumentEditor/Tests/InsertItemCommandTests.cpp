#include "stdafx.h"
#include "Document/DocumentCommands/InsertItemCommand.h"
#include "Command/History.h"
#include "Document/DocumentItems/Paragraph.h"
#include "Document/DocumentItems/DocumentItem.h"

using namespace std;

struct InsertItemFixture
{
	InsertItemFixture()
	{
		
		auto pParagraph = make_shared<CParagraph>(CParagraph("text", history));
		item = make_shared<CDocumentItem>(pParagraph);
		command = make_unique<CInsertItemCommand>(items, item, 0);
	}

	CHistory history;
	vector<DocumentItemPtr> items;
	std::shared_ptr<CInsertItemCommand> command;
	std::shared_ptr<CDocumentItem> item;
};

BOOST_FIXTURE_TEST_SUITE(CInsertItemCommand_tests, InsertItemFixture)
BOOST_AUTO_TEST_CASE(can_execute_and_unexecute)
{
	command->Execute();
	BOOST_CHECK_EQUAL(items.size(), size_t(1));
	BOOST_CHECK_EQUAL(items[0], item);

	command->Unexecute();
	BOOST_CHECK_EQUAL(items.size(), size_t(0));
}
BOOST_AUTO_TEST_SUITE_END()