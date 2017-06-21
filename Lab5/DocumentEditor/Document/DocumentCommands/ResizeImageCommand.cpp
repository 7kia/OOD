#include "stdafx.h"
#include "ResizeImageCommand.h"

using namespace std;

CResizeImageCommand::CResizeImageCommand(
	unsigned & width,
	unsigned & height,
	unsigned newWidth,
	unsigned newHeight
)
	: m_width(width)
	, m_height(height)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	swap(m_width, m_newWidth);
	swap(m_height, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	swap(m_width, m_newWidth);
	swap(m_height, m_newHeight);
}


