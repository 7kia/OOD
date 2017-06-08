#pragma once

#include <memory>
#include <string>

#include "IImage.h"
#include "Command/History.h"

class CImage 
	: public IImage
	, public std::enable_shared_from_this<IImage>
{
public:
	CImage(
		std::string const& path,
		unsigned width,
		unsigned height,
		CHistory & history
	);
	~CImage();
public:
	std::string GetPath() const override;

	unsigned GetWidth() const override;
	unsigned GetHeight() const override;

	void SetWidth(unsigned width) override;
	void SetHeight(unsigned height) override;

	void Resize(unsigned width, unsigned height) override;
private:
	std::string m_path;
	unsigned m_width;
	unsigned m_height;
	CHistory & m_history;
};