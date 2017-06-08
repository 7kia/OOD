#include "stdafx.h"
#include "ResizeImageCommand.h"


CResizeImageCommand::CResizeImageCommand(
	std::shared_ptr<IImage> const & pImage,
	int newWidth,
	int newHeight
)// TODO : see need interface for IImage get height and width
	: m_pImage(pImage)
	, m_oldHeight(pImage->GetHeight())
	, m_oldWidth(pImage->GetWidth())
	, m_newHeight(newHeight)
	, m_newWidth(newWidth)
{

}


void CResizeImageCommand::DoExecute()
{
	m_pImage->SetWidth(m_newWidth);
	m_pImage->SetHeight(m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_pImage->SetWidth(m_oldWidth);
	m_pImage->SetHeight(m_oldHeight);
}
