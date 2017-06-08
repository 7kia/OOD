#include "stdafx.h"
#include "DocumentItem.h"

using namespace std;

CDocumentItem::CDocumentItem(const IParagraphPtr & paragraph)
	: CConstDocumentItem(paragraph)
{
}

CDocumentItem::CDocumentItem(const IImagePtr & image)
	: CConstDocumentItem(image)
{
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}

shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}
