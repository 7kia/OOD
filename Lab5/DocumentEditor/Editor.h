#pragma once
#include "Document/DocumentItems/Menu.h"
#include "Document/IDocument.h"
#include "Document/HtmlConverter.h"

class CEditor
{
public:
	CEditor();
public:
	void Start();
private:
	// ��������� �� ����� ������ CEditor, ����������� istream& � ������������ void
	typedef void (CEditor::*MenuHandler)(std::istream & in);

	void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler);

	void SetTitle(std::istream & in);
	void AddParagraph(std::istream & in);
	void AddImage(std::istream & in);
	void DeleteItem(std::istream & in);
	void ReplaceText(std::istream & in);
	void ResizeImage(std::istream & in);
	void Save(std::istream & in);
	void List(std::istream &);

	void Undo(std::istream &);
	void Redo(std::istream &);

	unsigned ReadUnsigned(std::istream & in) const;
	std::string ReadLine(std::istream & in) const;
	boost::optional<size_t> ReadPosition(std::istream & in) const;
private:
	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};
