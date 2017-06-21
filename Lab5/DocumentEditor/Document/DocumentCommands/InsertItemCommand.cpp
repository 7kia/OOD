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

	/*if (m_item->GetImage())
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());

		m_textureStorage.SetDelete(m_textureStorage.GetTexturePath(pPictureModel->GetTexture()), false);
	}*/
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

	/*if (m_item->GetType())
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());
		const auto shapeHavePicture = m_shapeCollection.GetShape(pPictureModel->GetTexture());
		if (!shapeHavePicture)
		{
			m_textureStorage.SetDelete(m_textureStorage.GetTexturePath(pPictureModel->GetTexture()), true);
		}
	}*/
}
//
//void CInsertItemCommand::Destroy()
//{
//	if (m_item->GetType())
//	{
//		auto listShapesAfterDestroy = m_shapeCollection.GetShapes();
//		listShapesAfterDestroy.pop_back();// TODO: check correctness
//
//		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());
//
//		m_textureStorage.SetDelete(
//			m_textureStorage.GetTexturePath(pPictureModel->GetTexture()),
//			!HavePictureWithTexture(pPictureModel->GetTexture(), listShapesAfterDestroy)
//		);
//	}
//}
