#pragma once

#include <map>
#include <string>
#include <boost/filesystem.hpp>

#include "DocumentItems\DocumentItem_fwd.h"

class IDocument;

class CHtmlConverter
{
public:
	void Save(const boost::filesystem::path & path, const IDocument & document) const;
private:
	std::string CreateTitle(const IDocument & document) const;
	std::string CreateBody(const boost::filesystem::path & path, const IDocument & document) const;

	std::string CreateParagraph(const IParagraphConstPtr & pParagraph) const;
	std::string CreateImage(const IImageConstPtr & pImage) const;
	std::string ReplaceEncodeSymbols(std::string const & text) const;
};

