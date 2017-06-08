#pragma once

#include "Command/AbstractCommand.h"
#include "../DocumentItems/DocumentItem.h"
#include "../DocumentItems/DocumentItem_fwd.h"
#include <vector>

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<DocumentItemPtr> & items, size_t index);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::vector<DocumentItemPtr> & m_items;
	DocumentItemPtr m_item;
	size_t m_index;
};

