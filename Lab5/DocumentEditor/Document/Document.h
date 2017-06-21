#pragma once
#include "IDocument.h"
#include "Command/History.h"
#include "DocumentItems/ConstDocumentItem.h"

#include <boost/filesystem.hpp>


class CDocument : public IDocument
{
public:
	CDocument();
	~CDocument();
public:

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;
	std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text,
		boost::optional<size_t> const& position = boost::none
	) override;

	std::shared_ptr<IImage> InsertImage(
		const std::string& path,
		int width,
		int height,
		boost::optional<size_t> const& position = boost::none
	) override;

	size_t GetItemsCount() const override;

	CConstDocumentItem GetItem(size_t index) const override;
	CDocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(const std::string& path) const override;


	boost::filesystem::path GetTempPath() const;
private:
	void CopyImagesForFile(const std::string path) const;
private:
	std::string m_title;
	CHistory m_history;
	std::vector<DocumentItemPtr> m_documentItems;
	boost::filesystem::path m_tempPath;
};