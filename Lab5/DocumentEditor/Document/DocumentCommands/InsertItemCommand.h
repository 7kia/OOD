#pragma once
#include "Command/AbstractCommand.h"
#include "../DocumentItems/IParagraph.h"
#include "../DocumentItems/DocumentItem_fwd.h"

#include <vector>
#include <boost/optional.hpp>

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(
		std::vector<DocumentItemPtr> & items,
		DocumentItemPtr item,
		size_t position
	);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<DocumentItemPtr> & m_items;
	DocumentItemPtr m_item;
	size_t m_position;
};

