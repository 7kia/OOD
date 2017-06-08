#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "DocumentItem_fwd.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const IParagraphPtr & paragraph);
	CConstDocumentItem(const IImagePtr & image);
	virtual ~CConstDocumentItem() = default;

public:
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	IImageConstPtr GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	IParagraphConstPtr GetParagraph()const;
protected:
	IParagraphPtr m_paragraph;
	IImagePtr m_image;
};
