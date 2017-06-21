#pragma once

#include "ICommand.h"
#include "IHistory.h"
#include <deque>
#include <cassert>

class CHistory : public IHistory
{
public:
	bool CanUndo() const override final;	
	void Undo() override final;
	bool CanRedo() const  override final;
	void Redo() override final;
	void AddAndExecuteCommand(ICommandPtr && command) override final;

	size_t GetSize() const override;
private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

