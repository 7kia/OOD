#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>
#include <boost/algorithm/string.hpp>

#include "PictureDraft.h"

class CShapeReader
{
public:
	CShapeReader();
	CShapeReader(const std::string &nameInputFile);
	~CShapeReader();

	typedef typename std::vector<std::string> listArguments;

	enum class IdCommand
	{
		Triangle = 0,
		Rectangle ,
		Circle
	};
public:
	void				ReadShapes(const std::string &nameInputFile);
	CPictureDraft		GetDraft() const;
private:
	void				CheckAndOpenFileForReading(std::ifstream &file, const std::string& fileName);
	void				CheckAndOpenFileForWriting(std::ofstream &file, const std::string& fileName);

	void				ReadShapes(std::istream & file);
	void				CheckAmountArguments(const listArguments & arguments, IdCommand id);

	void				AddTriangle(const listArguments & arguments);
	void				AddRectangle(const listArguments & arguments);
	void				AddCircle(const listArguments & arguments);

	listArguments		SplitWords(std::string const & text);
	bool				IsCommand(const std::string & word);
private:
	CPictureDraft		m_draft;
	std::string			m_nameInputFile;
};