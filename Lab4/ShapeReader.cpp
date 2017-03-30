#include "stdafx.h"
#include "ShapeReader.h"

using namespace std;

namespace
{
	const std::vector<std::string> COMMANDS_NAME =
	{
		"Triangle" ,
		"Rectangle" ,
		"Circle"
	};
	const std::vector<int> AMOUNT_ARGUMENTS_FOR_COMMAND =
	{
		9 ,
		7 ,
		6
	};
	const std::string MESSAGE_INCORRECT_COMMAND = "Incorrect command.";

	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";
	const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
}

CShapeReader::CShapeReader()
{
}

CShapeReader::CShapeReader(const std::string &nameInputFile)
{
	ReadShapes(nameInputFile);
}

CShapeReader::~CShapeReader()
{
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

vector<string> CShapeReader::SplitWords(string const& text)
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
		argumnents = SplitWords(stringFromFile);
		if (argumnents[0] == COMMANDS_NAME[size_t(IdCommand::Triangle)])
		{
			AddTriangle(argumnents);
		}
		else if (argumnents[0] == COMMANDS_NAME[size_t(IdCommand::Rectangle)])
		{
			AddRectangle(argumnents);
		}
		else if (argumnents[0] == COMMANDS_NAME[size_t(IdCommand::Circle)])
		{
			AddCircle(argumnents);
		}
		else
		{
			throw invalid_argument(MESSAGE_INCORRECT_COMMAND);
		}
	}


}

void CShapeReader::CheckAmountArguments(const listArguments & arguments, IdCommand id)
{
	if (arguments.size() != AMOUNT_ARGUMENTS_FOR_COMMAND[size_t(id)])
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
			+ to_string(AMOUNT_ARGUMENTS_FOR_COMMAND[size_t(id)]) + " now " + to_string(arguments.size()));
	}
}

void CShapeReader::AddTriangle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Triangle);

	std::unique_ptr<CTriangle> addTriangle(new CTriangle);
	addTriangle->SetFirstPoint(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addTriangle->SetSecondPoint(sf::Vector2f(stof(arguments[3]), stof(arguments[4])));
	addTriangle->SetThirdPoint(sf::Vector2f(stof(arguments[5]), stof(arguments[6])));
	addTriangle->SetFillColor(ToColor(arguments[7]));
	addTriangle->SetOutlineColor(ToColor(arguments[8]));

	m_draft.push_back(move(addTriangle));
}

void CShapeReader::AddRectangle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Rectangle);

	std::unique_ptr<CRectangle> addRectangle(new CRectangle);
	addRectangle->SetLeftTopPoint(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addRectangle->SetSize(SSize(stof(arguments[3]), stof(arguments[4])));
	addRectangle->SetFillColor(ToColor(arguments[5]));
	addRectangle->SetOutlineColor(ToColor(arguments[6]));

	m_draft.push_back(move(addRectangle));
}

void CShapeReader::AddCircle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Circle);

	std::unique_ptr<CCircle> addCircle(new CCircle);
	addCircle->SetPosition(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addCircle->SetRadius(stof(arguments[3]));
	addCircle->SetFillColor(ToColor(arguments[4]));
	addCircle->SetOutlineColor(ToColor(arguments[5]));

	m_draft.push_back(move(addCircle));
}

bool CShapeReader::IsCommand(const std::string & word)
{
	return find(COMMANDS_NAME.begin(), COMMANDS_NAME.end(), word) != COMMANDS_NAME.end();
}
