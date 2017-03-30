#include "stdafx.h"
#include "ShapeReader.h"

using namespace std;

namespace
{
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";
}

CShapeReader::CShapeReader(const std::string &nameInputFile)
{
	ReadShapes(nameInputFile);
}

void CShapeReader::ReadShapes(const std::string & nameInputFile)
{
	m_nameInputFile = nameInputFile;

	std::ifstream inputFile;
	CheckAndOpenFileForReading(inputFile, m_nameInputFile);

	ReadShapes(inputFile);
}

CPictureDraft CShapeReader::GetDraft() const
{
	return m_draft;
}


void CShapeReader::CheckAndOpenFileForReading(ifstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ifstream::badbit);
	if (!file.is_open())
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

void CShapeReader::CheckAndOpenFileForWriting(ofstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ofstream::badbit);
	if (!file.is_open())
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}
}

vector<string> CShapeReader::SplitWords(const string & text)
{
	std::string trimmed = boost::trim_copy(text);

	vector<string> words;
	boost::split(words, trimmed, boost::is_space(), boost::token_compress_on);
	return words;
}

void CShapeReader::ReadShapes(std::istream & file)
{
	string stringFromFile;
	listArguments argumnents;

	while (getline(file, stringFromFile))
	{
		m_draft.push_back(m_shapeFactory.CreateShape(SplitWords(stringFromFile)));
	}

}
