#pragma once

#include <map>
#include <string>
#include <boost/filesystem.hpp>

#include "DocumentItems\DocumentItem_fwd.h"

class IDocument;

class CHtmlConverter
{
public:
	static void Save(const boost::filesystem::path & path, const IDocument & document);
private:
	static std::string CreateTitle(const IDocument & document);
	static std::string CreateBody(const boost::filesystem::path & path, const IDocument & document);

	static std::string CreateParagraph(const IParagraphConstPtr & pParagraph);
	static std::string CreateImage(const IImageConstPtr & pImage, const std::string & path);
	static std::string ReplaceEncodeSymbols(std::string const & text);
};

