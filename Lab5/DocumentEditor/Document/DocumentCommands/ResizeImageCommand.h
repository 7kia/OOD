#pragma once
#include "Command/AbstractCommand.h"
#include "../DocumentItems/IImage.h"
#include <memory>

class CResizeImageCommand :	public CAbstractCommand
{
public:
	CResizeImageCommand(
		unsigned & width,
		unsigned & height,
		unsigned newWidth,
		unsigned newHeight
	);

protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	unsigned & m_width;
	unsigned & m_height;
	unsigned m_newWidth;
	unsigned m_newHeight;
};

