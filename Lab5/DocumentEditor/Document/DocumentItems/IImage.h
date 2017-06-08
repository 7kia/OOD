#pragma once
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class IImage
{
public:
	virtual ~IImage() = default;

	virtual std::string GetPath() const = 0;

	// ������ ����������� � ��������
	virtual unsigned GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual unsigned GetHeight()const = 0;

	virtual void SetWidth(unsigned width) = 0;
	virtual void SetHeight(unsigned height) = 0;
	// �������� ������ �����������
	virtual void Resize(unsigned width, unsigned height) = 0;
};
