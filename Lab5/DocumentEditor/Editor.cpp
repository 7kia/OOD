#include "stdafx.h"
#include "Editor.h"
#include "Document/Document.h"
#include "Document/DocumentItems/DocumentItem.h"
#include "Document/DocumentItems/ConstDocumentItem.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor()
	: m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Change title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("insertParagraph", "Add paragraph at position. Args: <position>|end <text>", &CEditor::AddParagraph);
	AddMenuItem("insertImage", "Add image at positions. Args: <position>|end <width> <height> <path>", &CEditor::AddImage);
	AddMenuItem("deleteItem", "Delete item at position. Args: <position>", &CEditor::DeleteItem);
	AddMenuItem("replaceText", "Replace text at position. Args: <position>", &CEditor::ReplaceText);
	AddMenuItem("resizeImage", "Resize image at position. Args: <position> <width> <height>", &CEditor::ResizeImage);
	AddMenuItem("save", "Save html document to path. Args: <path>", &CEditor::Save);
	AddMenuItem("list", "Show document", &CEditor::List);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream & in)
{
	m_document->SetTitle(ReadLine(in));
}

void CEditor::AddParagraph(istream & in)
{
	try
	{
		size_t position = size_t(ReadUnsigned(in));
		string text = ReadLine(in);
		m_document->InsertParagraph(text, position);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::AddImage(istream & in)
{
	try
	{
		size_t position = size_t(ReadUnsigned(in));
		unsigned width = ReadUnsigned(in);
		unsigned height = ReadUnsigned(in);
		string path = ReadLine(in);
		m_document->InsertImage(path, width, height, position);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::DeleteItem(istream & in)
{
	try
	{
		m_document->DeleteItem(ReadUnsigned(in));
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::ReplaceText(istream & in)
{
	try
	{
		unsigned index = ReadUnsigned(in);
		string text = ReadLine(in);

		auto item = m_document->GetItem(index);
		if (!item.GetParagraph())
		{
			throw invalid_argument("Can't replace text in non-text item");
		}

		item.GetParagraph()->SetText(text);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::ResizeImage(istream & in)
{
	try
	{
		size_t index = ReadUnsigned(in);
		unsigned width = ReadUnsigned(in);
		unsigned height = ReadUnsigned(in);

		auto item = m_document->GetItem(index);
		if (!item.GetImage())
		{
			throw invalid_argument("Can't resize non-image");
		}
		item.GetImage()->Resize(width, height);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::Save(istream & in)
{
	try
	{
		string path = ReadLine(in);

		m_document->Save(path);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}
}

void CEditor::List(istream &)
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	for (unsigned i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);
		if (item.GetParagraph())
		{
			cout << i << ". Paragraph: " << item.GetParagraph()->GetText() << endl;
		}
		else
		{
			auto image = item.GetImage();
			cout << i << ". Image: " << image->GetWidth() << "x" << image->GetHeight() << " " << image->GetPath() << endl;
		}
	}
	cout << "-------------" << endl;
}

void CEditor::Undo(istream &)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		cout << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream &)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		cout << "Can't redo" << endl;
	}
}

unsigned CEditor::ReadUnsigned(istream & in)
{
	int index;
	if (!(in >> index) || (index < 0))
	{
		throw invalid_argument("Unsigned number expected");
	}
	return index;
}

string CEditor::ReadLine(istream & in)
{
	string text;
	getline(in >> ws, text);
	return text;
}

