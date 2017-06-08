#include "stdafx.h"
#include "ConstDocumentItem.h"

using namespace std;

CConstDocumentItem::CConstDocumentItem(const IParagraphPtr & paragraph)
	: m_paragraph(paragraph)
	, m_image(nullptr)
{
}

CConstDocumentItem::CConstDocumentItem(const IImagePtr & image)
	: m_image(image)
	, m_paragraph(nullptr)
{	
}

IParagraphConstPtr CConstDocumentItem::GetParagraph()const
{
	return m_paragraph;
}

IImageConstPtr CConstDocumentItem::GetImage()const
{
	return m_image;
}

