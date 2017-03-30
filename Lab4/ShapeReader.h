#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>
#include <boost/algorithm/string.hpp>

#include "PictureDraft.h"
#include "Shapes\ShapeFactory.h"

class CShapeReader
{
public:
	CShapeReader() = default;
	CShapeReader(const std::string & nameInputFile);
public:
	void				ReadShapes(const std::string &nameInputFile);
	CPictureDraft		GetDraft() const;
private:
	void				CheckAndOpenFileForReading(std::ifstream &file, const std::string & fileName);
	void				CheckAndOpenFileForWriting(std::ofstream &file, const std::string & fileName);

	void				ReadShapes(std::istream & file);

	listArguments		SplitWords(const std::string & text);
private:
	CPictureDraft		m_draft;
	CShapeFactory		m_shapeFactory;
	std::string			m_nameInputFile;
};