#pragma once

#include "ICommand.h"

class IHistory
{
public:
	virtual ~IHistory() = default;

	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void AddAndExecuteCommand(ICommandPtr && command) = 0;

	virtual size_t GetSize() const = 0;
};

