#include "stdafx.h"
#include "HtmlConverter.h"
#include "Document/IDocument.h"
#include "Document/DocumentItems/DocumentItem.h"
#include "Document/DocumentItems/IParagraph.h"
#include "Document/DocumentItems/IImage.h"

#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <sstream>
#include <iostream>

using namespace std;
using namespace boost;

namespace fs = boost::filesystem;

namespace
{
	static const string IMAGES_DIRECTORY = "images";
	// TODO : see can transfer to other place, add getImageFolder for document

}

void CHtmlConverter::Save(const fs::path & path, const IDocument & document)
{
	std::ofstream outputFile(path.generic_string());
	if (!outputFile.is_open())
	{
		throw std::runtime_error("failed to open " + path.generic_string() + " to writing");
	}

	outputFile << "<!DOCTYPE html>" << endl
		<< "<html>" << endl;
	outputFile << CreateTitle(document);
	outputFile << CreateBody(path, document)
		<< "</html>";

	if (!outputFile.flush())
	{
		throw std::runtime_error("failed to save data");
	}
	outputFile.close();
}

std::string CHtmlConverter::CreateTitle(const IDocument & document)
{
	const auto title = "\t\t<title>" + ReplaceEncodeSymbols(document.GetTitle())+ "</title>\n";
	return "\t<head>\n"
		+  title  +
		"\t</head>\n";
}

string CHtmlConverter::CreateBody(const fs::path & path, const IDocument & document)
{
	string bodyString = "\t<body>\n";

	auto pathToImages = boost::filesystem::path(path).stem() / IMAGES_DIRECTORY;
	if (!boost::filesystem::exists(fs::path(pathToImages)))
	{
		boost::filesystem::create_directory(pathToImages);
	}
	for (size_t i = 0; i < document.GetItemsCount(); ++i)
	{
		auto item = document.GetItem(i);
		if (item.GetParagraph())
		{
			bodyString += CreateParagraph(item.GetParagraph());
		}
		else if (item.GetImage())
		{
			bodyString += CreateImage(item.GetImage(), pathToImages.generic_string());
		}
		else
		{
			throw std::runtime_error("Unknown item");
		}
	}

	bodyString += "\n\t</body>\n";
	return bodyString;
}

string CHtmlConverter::CreateParagraph(const IParagraphConstPtr & pParagraph)
{
	return "\t\t<p>" + ReplaceEncodeSymbols(pParagraph->GetText()) + "</p>\n";
}

string CHtmlConverter::CreateImage(const IImageConstPtr & pImage, const string & path)
{
	boost::format imageFormat(R"(		<img src="%1%" width="%2%" height="%3%">
)");
	stringstream stream;

	auto pathToTemp = boost::filesystem::path(pImage->GetPath());
	string imageName = pathToTemp.filename().generic_string();

	stream << imageFormat
		% (path + "/" + ReplaceEncodeSymbols(imageName))
		% pImage->GetWidth()
		% pImage->GetHeight();

	return stream.str();
}


std::string CHtmlConverter::ReplaceEncodeSymbols(std::string const& text)
{
	string newString = text;
	replace_all(newString, "&", "&amp;");
	replace_all(newString, "\"", "&quot;");
	replace_all(newString, "\'", "&apos;");
	replace_all(newString, "<", "&lt;");
	replace_all(newString, ">", "&gt;");
	return newString;
}