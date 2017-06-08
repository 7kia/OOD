#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "GlobalFunctions.h"

using namespace std;

CDeleteItemCommand::CDeleteItemCommand(vector<DocumentItemPtr> & items, size_t index)
	: m_items(items)
	, m_index(index)
{
}

void CDeleteItemCommand::DoExecute()
{
	CheckIndex(m_index, m_items.size() + 1);

	m_item = m_items[m_index];
	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItemCommand::DoUnexecute()
{
	CheckIndex(m_index, m_items.size());

	m_items.insert(m_items.begin() + m_index, m_item);
}
