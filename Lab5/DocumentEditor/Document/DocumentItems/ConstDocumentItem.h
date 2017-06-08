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
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	IImageConstPtr GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	IParagraphConstPtr GetParagraph()const;
protected:
	IParagraphPtr m_paragraph;
	IImagePtr m_image;
};
