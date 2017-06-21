#include "stdafx.h"
#include "Image.h"
#include "../DocumentCommands/ResizeImageCommand.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

using namespace  boost;

CImage::CImage(
	std::string const& path,
	unsigned width,
	unsigned height,
	CHistory & history
)
	: m_path(path)
	, m_height(height)
	, m_width(width)
	, m_history(history)
{
	if (!exists(boost::filesystem::path(path)))
	{
		throw std::invalid_argument("Invalid file path or not accessible file");
	}

}


CImage::~CImage()
{
	/*try
	{
		if (filesystem::exists(m_path))
		{
			filesystem::remove(m_path);
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}*/
	
}

std::string CImage::GetPath() const
{
	return m_path;
}

unsigned CImage::GetWidth() const
{
	return m_width;
}

unsigned CImage::GetHeight() const
{
	return m_height;
}


void CImage::SetWidth(unsigned width)
{
	m_width = width;
}


void CImage::SetHeight(unsigned height)
{
	m_height = height;
}

void CImage::Resize(unsigned width, unsigned height)
{
	m_history.AddAndExecuteCommand(std::make_unique<CResizeImageCommand>(m_width, m_height, width, height));
}
