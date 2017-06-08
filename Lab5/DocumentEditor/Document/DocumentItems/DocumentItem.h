#pragma once
#include "ConstDocumentItem.h"
#include "DocumentItem_fwd.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const IParagraphPtr & paragraph);
	CDocumentItem(const IImagePtr & image);
public:
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	IParagraphPtr GetParagraph();
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	IImagePtr GetImage();
};
