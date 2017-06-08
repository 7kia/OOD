#pragma once
#include "Command/AbstractCommand.h"
#include "../DocumentItems/IImage.h"
#include <memory>

class CResizeImageCommand :	public CAbstractCommand
{
public:
	CResizeImageCommand(
		std::shared_ptr<IImage> const & pImage,
		int newWidth,
		int newHeight
	);

protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::shared_ptr<IImage> m_pImage;
	int m_newWidth;
	int m_newHeight;
	int m_oldWidth;
	int m_oldHeight;
};

