#include "stdafx.h"
#include "ShapeFactory.h"

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
	const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
}

CShapePtr CShapeFactory::CreateShape(const listArguments & arguments)
{
	if (arguments[0] == COMMANDS_NAME[size_t(IdCommand::Triangle)])
	{
		return CreateTriangle(arguments);
	}
	else if (arguments[0] == COMMANDS_NAME[size_t(IdCommand::Rectangle)])
	{
		return CreateRectangle(arguments);
	}
	else if (arguments[0] == COMMANDS_NAME[size_t(IdCommand::Circle)])
	{
		return CreateCircle(arguments);
	}
	else
	{
		throw invalid_argument(MESSAGE_INCORRECT_COMMAND);
	}
}


void CShapeFactory::CheckAmountArguments(const listArguments & arguments, IdCommand id)
{
	if (arguments.size() != AMOUNT_ARGUMENTS_FOR_COMMAND[size_t(id)])
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
			+ to_string(AMOUNT_ARGUMENTS_FOR_COMMAND[size_t(id)]) + " now " + to_string(arguments.size()));
	}
}


std::shared_ptr<CTriangle> CShapeFactory::CreateTriangle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Triangle);

	std::shared_ptr<CTriangle> addTriangle = make_shared<CTriangle>();
	addTriangle->SetFirstPoint(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addTriangle->SetSecondPoint(sf::Vector2f(stof(arguments[3]), stof(arguments[4])));
	addTriangle->SetThirdPoint(sf::Vector2f(stof(arguments[5]), stof(arguments[6])));
	addTriangle->SetFillColor(ToColor(arguments[7]));
	addTriangle->SetOutlineColor(ToColor(arguments[8]));

	return addTriangle;
}

std::shared_ptr<CRectangle> CShapeFactory::CreateRectangle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Rectangle);

	std::shared_ptr<CRectangle> addRectangle = make_shared<CRectangle>();
	addRectangle->SetLeftTopPoint(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addRectangle->SetSize(SSize(stof(arguments[3]), stof(arguments[4])));
	addRectangle->SetFillColor(ToColor(arguments[5]));
	addRectangle->SetOutlineColor(ToColor(arguments[6]));

	return addRectangle;
}

std::shared_ptr<CCircle> CShapeFactory::CreateCircle(const listArguments & arguments)
{
	CheckAmountArguments(arguments, IdCommand::Circle);

	std::shared_ptr<CCircle> addCircle = make_shared<CCircle>();
	addCircle->SetPosition(sf::Vector2f(stof(arguments[1]), stof(arguments[2])));
	addCircle->SetRadius(stof(arguments[3]));
	addCircle->SetFillColor(ToColor(arguments[4]));
	addCircle->SetOutlineColor(ToColor(arguments[5]));

	return addCircle;
}