#include "stdafx.h"

#include "../ShapeReader.h"
#include "..\Painter\Painter.h"

struct ShapeReader_
{
	CShapeReader reader;
	
	CPictureDraft draft;
	std::vector<SFMLShapePtr> sfmlShapes;
	CSFMLShapeFactory factory;

	const float THIKNESS_LINE = 5;
	const sf::Vector2f ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float RADIUS_POINT = 2.f;

	const int amountShapes = 3;
	const int indexRectangle = 0;
	const int indexCircle = 1;
	const int indexTriangle = 2;

	ShapeReader_()
	{
		reader.ReadShapes("draft.txt");
		draft = reader.GetDraft();

		for (const auto data : draft)
		{
			sfmlShapes.push_back(factory.CreateShape(data));
		}
		
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeReader, ShapeReader_)

BOOST_AUTO_TEST_CASE(size_shape_list_is_correct)
{
	BOOST_CHECK_EQUAL(draft.size(), amountShapes);
}



BOOST_AUTO_TEST_SUITE(read_rectangle)
	struct check_rectangle_ : ShapeReader_
	{
		const sf::Vector2f leftToppoint;
		const SSize size;
		const sf::Color fillColor;
		const sf::Color outlineColor;

		check_rectangle_()
			: fillColor(17, 241, 49)
			, outlineColor(18, 242, 50)
			, leftToppoint(45.f, 23.f)
			, size(46.f, 24.f)
		{

		}
	};
	BOOST_FIXTURE_TEST_SUITE(check_rectangle, check_rectangle_)
		BOOST_AUTO_TEST_CASE(rectangle_draft)
		{
			const CRectangle* pRectangle = dynamic_cast<CRectangle*>(&*draft[indexRectangle]);

			VerifyVector2f(leftToppoint, pRectangle->GetLeftTopPoint());
			
			VerifySize(pRectangle->GetSize(), size);
			VerifyColor(fillColor, pRectangle->GetFillColor());
			VerifyColor(outlineColor, pRectangle->GetOutlineColor());
		}
		BOOST_AUTO_TEST_CASE(rectangle_sfmlShape)
		{
			const sf::RectangleShape* pRectangle = dynamic_cast<sf::RectangleShape*>(&*sfmlShapes[indexRectangle]);

			VerifyVector2f(leftToppoint, pRectangle->getPosition());

			BOOST_CHECK(IsEqual(size.width, pRectangle->getSize().x));
			BOOST_CHECK(IsEqual(size.height, pRectangle->getSize().y));
			VerifyColor(fillColor, pRectangle->getFillColor());
			VerifyColor(outlineColor, pRectangle->getOutlineColor());
		}
	BOOST_AUTO_TEST_SUITE_END()// check_rectangle_
BOOST_AUTO_TEST_SUITE_END()// read_rectangle


BOOST_AUTO_TEST_SUITE(read_circle)
	struct check_circle_ : ShapeReader_
		{
			const sf::Vector2f position;
			const float radius = 2.2f;
			const float height = 24.f;
			const sf::Color fillColor;
			const sf::Color outlineColor;

			check_circle_()
				: fillColor(19, 243, 51)
				, outlineColor(20, 244, 52)
				, position(146.f, 123.f)
			{

			}
		};
	BOOST_FIXTURE_TEST_SUITE(check_circle, check_circle_)
		BOOST_AUTO_TEST_CASE(circle_draft)
		{
			const CCircle* pCircle = dynamic_cast<CCircle*>(&*draft[indexCircle]);

			VerifyVector2f(position, pCircle->GetPosition());
			BOOST_CHECK(IsEqual(radius, pCircle->GetRadius()));
			VerifyColor(fillColor, pCircle->GetFillColor());
			VerifyColor(outlineColor, pCircle->GetOutlineColor());
		}
		BOOST_AUTO_TEST_CASE(circle_sfmlShape)
		{
			const sf::CircleShape* pCircle = dynamic_cast<sf::CircleShape*>(&*sfmlShapes[indexCircle]);

			VerifyVector2f(position, pCircle->getPosition());
			BOOST_CHECK(IsEqual(radius, pCircle->getRadius()));
			VerifyColor(fillColor, pCircle->getFillColor());
			VerifyColor(outlineColor, pCircle->getOutlineColor());
		}
	BOOST_AUTO_TEST_SUITE_END()// check_rectangle_
BOOST_AUTO_TEST_SUITE_END()// read_rectangle

BOOST_AUTO_TEST_SUITE(read_triangle)
	struct check_triangle_ : ShapeReader_
	{
		const sf::Vector2f firstPosition = { 10.f, 0.f };
		const sf::Vector2f secondPosition = { -10.f, 0.f };
		const sf::Vector2f thirdPosition = { 0.f, 10.f };
		const sf::Color fillColor;
		const sf::Color outlineColor;

		check_triangle_()
			: fillColor(21, 245, 53)
			, outlineColor(22, 246, 54)			
		{

		}
	};
	BOOST_FIXTURE_TEST_SUITE(check_triangle, check_triangle_)
		BOOST_AUTO_TEST_CASE(triangle_draft)
		{
			const CTriangle* pTriangle = dynamic_cast<CTriangle*>(&*draft[indexTriangle]);

			VerifyVector2f(firstPosition, pTriangle->GetFirstPoint());
			VerifyVector2f(secondPosition, pTriangle->GetSecondPoint());
			VerifyVector2f(thirdPosition, pTriangle->GetThirdPoint());
			VerifyColor(fillColor, pTriangle->GetFillColor());
			VerifyColor(outlineColor, pTriangle->GetOutlineColor());
		}
		BOOST_AUTO_TEST_CASE(triangle_sfmlShape)
		{
			const sf::ConvexShape* pTriangle = dynamic_cast<sf::ConvexShape*>(&*sfmlShapes[indexTriangle]);

			VerifyVector2f(firstPosition, pTriangle->getPoint(0));
			VerifyVector2f(secondPosition, pTriangle->getPoint(1));
			VerifyVector2f(thirdPosition, pTriangle->getPoint(2));
			VerifyColor(fillColor, pTriangle->getFillColor());
			VerifyColor(outlineColor, pTriangle->getOutlineColor());
		}
	BOOST_AUTO_TEST_SUITE_END()// check_triangle_
BOOST_AUTO_TEST_SUITE_END()// read_triangle


BOOST_AUTO_TEST_SUITE_END()// ShapeReader_
