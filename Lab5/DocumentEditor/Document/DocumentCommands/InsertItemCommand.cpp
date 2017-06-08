#include "stdafx.h"
#include "InsertItemCommand.h"
#include "GlobalFunctions.h"

using namespace std;

CInsertItemCommand::CInsertItemCommand(
	vector<DocumentItemPtr> & items,// TODO : see need interface for document items
	DocumentItemPtr item,
	size_t position
)
	: m_items(items)
	, m_item(item)
	, m_position(position)
{
}

void CInsertItemCommand::DoExecute()
{
	if (m_position < m_items.size())
	{
		CheckIndex(m_position, m_items.size());

		m_items.insert(m_items.begin() + m_position, m_item);
	}
	else
	{
		m_items.push_back(m_item);
	}
}

void CInsertItemCommand::DoUnexecute()
{
	if (m_position < m_items.size())
	{
		CheckIndex(m_position, m_items.size() + 1);

		m_items.erase(m_items.begin() + m_position);
	}
	else
	{
		m_items.pop_back();
	}
}
