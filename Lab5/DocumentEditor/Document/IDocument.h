#pragma once
// TODO : see includes
#include <memory>
#include <string>
#include <boost\optional.hpp>
#include <boost\none.hpp>
#include "DocumentItems\IParagraph.h"
#include "DocumentItems\IImage.h"
#include "DocumentItems\ConstDocumentItem.h"
#include "DocumentItems\DocumentItem.h"

class IDocument
{
public:
	virtual ~IDocument() = default;

	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text,
		boost::optional<size_t> const& position  = boost::none
	) = 0;

	//// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	//// �������� path ������ ���� � ������������ �����������
	//// ��� ������� ����������� ������ ������������ � ���������� images 
	//// ��� ������������� ��������������� ������
	virtual std::shared_ptr<IImage> InsertImage(
		const std::string& path,
		int width,
		int height,
		boost::optional<size_t> const& position = boost::none
	) = 0;

	//// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount()const = 0;

	//// ������ � ��������� �����������
	virtual CConstDocumentItem GetItem(size_t index)const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	//// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string & title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	//// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	//// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const std::string& path)const = 0;
};
