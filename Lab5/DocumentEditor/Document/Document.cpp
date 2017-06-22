#include "stdafx.h"

#include <fstream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/uuid/uuid.hpp>            
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp> 
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>

#include "Document.h"
#include "DocumentCommands/ChangeStringCommand.h"
#include "DocumentCommands/InsertItemCommand.h"
#include "DocumentCommands/DeleteItemCommand.h"

#include "DocumentItems/Paragraph.h"
#include "DocumentItems/Image.h"
#include "HtmlConverter.h"

#include "GlobalFunctions.h"

using namespace std;
using namespace boost::algorithm;

namespace fs = boost::filesystem;

namespace
{
	static const size_t MAX_IMAGE_WIDTH = 10000;
	static const size_t MAX_IMAGE_HEIGHT = 10000;

	static const string IMAGES_DIRECTORY = "images";
	// TODO : see can transfer to other place, add getImageFolder for document


}

CDocument::CDocument()
	: m_tempPath(fs::unique_path("temp%%%%"))
{
	boost::filesystem::create_directory(m_tempPath);
	boost::filesystem::create_directory(boost::filesystem::path(m_tempPath) / IMAGES_DIRECTORY);
}

CDocument::~CDocument()
{
	boost::filesystem::remove_all(boost::filesystem::path(m_tempPath) / IMAGES_DIRECTORY);
	boost::filesystem::remove_all(m_tempPath);
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(
	const std::string& text,
	boost::optional<size_t> const& position
)
{
	auto pParagraph = make_shared<CParagraph>(CParagraph(text, m_history));
	auto pItem = make_shared<CDocumentItem>(pParagraph);

	size_t pos = position ? *position : m_documentItems.size();
	CheckIndex(pos, m_documentItems.size());
	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_documentItems, pItem, pos));
	return pParagraph;
}


std::shared_ptr<IImage> CDocument::InsertImage(
	const std::string& path,
	int width,
	int height,
	boost::optional<size_t> const& position
)
{

	size_t pos = position ? *position : m_documentItems.size();
	CheckIndex(pos, m_documentItems.size());

	if (!boost::filesystem::exists(path))
	{
		throw std::runtime_error("file doesn't exist");
	}
	if ((width < 1) || (width > MAX_IMAGE_WIDTH))
	{
		throw std::invalid_argument("invalid image width");
	}
	if ((height < 1) || (height > MAX_IMAGE_HEIGHT))
	{
		throw std::invalid_argument("invalid image height");
	}

	auto iterEqual = std::find_if(m_documentItems.begin(), m_documentItems.end(),
		[&](const DocumentItemPtr & pItem)
	{
		if (const auto image = pItem->GetImage())
		{
			auto imagePath = fs::path(image->GetPath());
			auto parentFolder = imagePath.parent_path();
			auto imageName = imagePath.filename();
			if ((parentFolder == fs::path(path).parent_path())
				&& (imageName == fs::path(path).filename())
				)
			{
				return true;
			}
		}
		return false;
	}
	);
	if (iterEqual == m_documentItems.end())
	{
		CopyImage(path);
	}




	auto pImage = make_shared<CImage>(path, width, height, m_history);
	auto pItem = make_shared<CDocumentItem>(pImage);

	m_history.AddAndExecuteCommand(make_unique<CInsertItemCommand>(m_documentItems, pItem, pos));
	return pImage;
}

size_t CDocument::GetItemsCount() const
{
	return m_documentItems.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (m_documentItems.size() == 0)
	{
		throw std::out_of_range("Index out range");
	}
	CheckIndex(index, m_documentItems.size() - 1);
	return *m_documentItems[index].get();
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (m_documentItems.size() == 0)
	{
		throw std::out_of_range("Index out range");
	}
	CheckIndex(index, m_documentItems.size() - 1);
	return *m_documentItems[index].get();
}

void CDocument::DeleteItem(size_t index)
{
	if (m_documentItems.size() == 0)
	{
		throw std::out_of_range("Index out range");
	}
	CheckIndex(index, m_documentItems.size() - 1);

	m_history.AddAndExecuteCommand(make_unique<CDeleteItemCommand>(m_documentItems, index));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const std::string & path) const
{
	CopyImagesForFile(path);

	CHtmlConverter htmlConverter;
	htmlConverter.Save(fs::path(path), *this);
}

boost::filesystem::path CDocument::GetTempPath() const
{
	return m_tempPath;
}

void CDocument::CopyImagesForFile(const std::string path) const
{
	const auto newFolder = fs::path(path).stem();
	boost::filesystem::create_directory(newFolder);
	boost::filesystem::create_directory(newFolder / IMAGES_DIRECTORY);

	const auto imagePathInNewFolder = fs::path(path).parent_path() / fs::path(path).stem() / IMAGES_DIRECTORY;

	for (const auto & item : m_documentItems)
	{
		if (item->GetImage())
		{
			const auto pImage = item->GetImage();
			const auto newPath = imagePathInNewFolder / fs::path(pImage->GetPath()).filename();
			const auto imagePath = fs::path(pImage->GetPath());
			boost::filesystem::copy_file(
				imagePath,
				newPath,
				boost::filesystem::copy_option::overwrite_if_exists);

		}
	}
}

void CDocument::CopyImage(const std::string & path) const
{
	auto pathToLoadImage = boost::filesystem::path(path);

	boost::filesystem::path pathToNewImage;
	auto iter = std::find_if(m_documentItems.begin(), m_documentItems.end(),
		[&](const DocumentItemPtr & pItem)
	{
		if (const auto image = pItem->GetImage())
		{
			auto imagePath = fs::path(image->GetPath());
			auto parentFolder = imagePath.parent_path();
			auto imageName = imagePath.filename();
			if ((parentFolder != fs::path(path).parent_path())
				&& (imageName == fs::path(path).filename())
				)
			{
				return true;
			}
		}
		return false;
	}
	);
	if (iter == m_documentItems.end())
	{
		string newName = pathToLoadImage.filename().generic_string();
		pathToNewImage = m_tempPath / IMAGES_DIRECTORY / newName;
	}
	else
	{
		boost::filesystem::path newName = boost::filesystem::unique_path(
			pathToLoadImage.stem().generic_string()
			+ "%%%%"
			+ pathToLoadImage.extension().generic_string()
		);
		pathToNewImage = m_tempPath / IMAGES_DIRECTORY / newName;
	}
	boost::filesystem::copy_file(path, pathToNewImage, boost::filesystem::copy_option::overwrite_if_exists);
}
