#include "stdafx.h"
#include "Command/History.h"
#include "Command/AbstractCommand.h"

using namespace std;

typedef std::vector<bool> ChangeArray;

class CommandMock : public CAbstractCommand
{
public:
	CommandMock(ChangeArray& commands, int id) 
		: m_commands(commands)
		, m_id(id)
	{
	}
protected:
	void DoExecute() override
	{
		m_commands.at(m_id) = !m_commands.at(m_id);
	}
	void DoUnexecute() override
	{
		m_commands.at(m_id) = !m_commands.at(m_id);
	}
private:
	int m_id;
	ChangeArray& m_commands;
};

struct HistoryFixture
{
	HistoryFixture()
	{
		for (size_t i = 0; i < 2; ++i)
		{
			commands.push_back(false);
		}
	}

	CHistory history;
	ChangeArray commands;
}; 

BOOST_FIXTURE_TEST_SUITE(CHistory_tests, HistoryFixture)
	BOOST_AUTO_TEST_SUITE(constructor_tests)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(!history.CanUndo());
			BOOST_CHECK(!history.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_add_and_execute_commands)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 1));
		BOOST_CHECK_EQUAL(commands.size(), size_t(2));

		BOOST_CHECK_EQUAL(commands[0], true);
		BOOST_CHECK_EQUAL(commands[1], true);
	}
	BOOST_AUTO_TEST_CASE(can_undo_and_redo_commands)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 1));
		history.Undo();
		BOOST_CHECK(!commands[1]);
		history.Undo();
		BOOST_CHECK(!commands[0]);
		BOOST_CHECK(!history.CanUndo());
		history.Redo();
		BOOST_CHECK(commands[0]);
		history.Redo();
		BOOST_CHECK(commands[1]);
		BOOST_CHECK(!history.CanRedo());
	}
	BOOST_AUTO_TEST_CASE(should_erase_commands_if_history_is_changed)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 1));
		history.Undo();

		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 1));
		BOOST_CHECK_EQUAL(history.GetSize(), size_t(2));
		BOOST_CHECK(commands[1]);
		BOOST_CHECK(commands[0]);
	}
	BOOST_AUTO_TEST_CASE(should_erase_commands_if_capacity_is_filled)
	{
		const unsigned maxAmountCommands = 10;

		for (size_t i = 2; i < maxAmountCommands; ++i)
		{
			commands.push_back(false);
		}
		for (int i = 0; i < maxAmountCommands; ++i)
		{
			history.AddAndExecuteCommand(make_unique<CommandMock>(commands, i));
		}
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));

		BOOST_CHECK_EQUAL(commands.size(), maxAmountCommands);
		for (size_t i = 0; i < maxAmountCommands; ++i)
		{
			BOOST_CHECK_EQUAL(commands[i], true);
		}
	}
BOOST_AUTO_TEST_SUITE_END()
	