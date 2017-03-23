#include "stdafx.h"

#include "../ShapeReader.h"
#include "Painter\Painter.h"

struct ShapeReader_
{
	CShapeReader reader;
	
	CPictureDraft draft;
	std::vector<SFMLShapePtr> sfmlShapes;
	CSFMLShapeFactory factory;

	const float THIKNESS_LINE = 5;
	const sf::Vector2f ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float RADIUS_POINT = 2.f;

	const int amountShapes = 5;
	const int indexPoint = 0;
	const int indexRectangle = 1;
	const int indexCircle = 2;
	const int indexTriangle = 3;
	const int indexLine = 4;

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

BOOST_AUTO_TEST_CASE(indexes_shape_is_correct)
{
	BOOST_CHECK_EQUAL(draft[indexPoint]->GetType(), "Point");
	BOOST_CHECK_EQUAL(draft[indexLine]->GetType(), "Line");
	BOOST_CHECK_EQUAL(draft[indexRectangle]->GetType(), "Rectangle");
	BOOST_CHECK_EQUAL(draft[indexCircle]->GetType(), "Circle");
	BOOST_CHECK_EQUAL(draft[indexTriangle]->GetType(), "Triangle");
}

BOOST_AUTO_TEST_SUITE(read_point)
	struct check_point_ : ShapeReader_
	{

	};
	BOOST_FIXTURE_TEST_SUITE(check_point, check_point_)
		BOOST_AUTO_TEST_CASE(draft_point)
		{
			const CMyPoint* pPoint = dynamic_cast<CMyPoint*>(&*draft[indexPoint]);

			const sf::Color fillColor(16, 240, 48);

			const sf::Vector2f position(100.f, 150.f);

			VerifyVector2f(position, pPoint->GetPosition());
			VerifyColor(fillColor, pPoint->GetFillColor());
		}
	BOOST_AUTO_TEST_SUITE_END()// check_point_
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(read_rectangle)
{
	const CRectangle* pRectangle = dynamic_cast<CRectangle*>(&*draft[indexRectangle]);

	const sf::Vector2f leftToppoint(45.f, 23.f);
	const float width = 46.f;
	const float height = 24.f;
	const sf::Color fillColor(17, 241, 49);
	const sf::Color outlineColor(18, 242, 50);

	VerifyVector2f(leftToppoint, pRectangle->GetLeftTopPoint());
	BOOST_CHECK_EQUAL(width, pRectangle->GetWidth());
	BOOST_CHECK_EQUAL(height, pRectangle->GetHeight());
	VerifyColor(fillColor, pRectangle->GetFillColor());
	VerifyColor(outlineColor, pRectangle->GetOutlineColor());
}


BOOST_AUTO_TEST_CASE(read_circle)
{
	const CCircle* pCircle = dynamic_cast<CCircle*>(&*draft[indexCircle]);

	const sf::Vector2f position(146.f, 123.f);
	const float radius = 2.2f;
	const float height = 24.f;
	const sf::Color fillColor(19, 243, 51);
	const sf::Color outlineColor(20, 244, 52);

	VerifyVector2f(position, pCircle->GetPosition());
	BOOST_CHECK_EQUAL(radius, pCircle->GetRadius());
	VerifyColor(fillColor, pCircle->GetFillColor());
	VerifyColor(outlineColor, pCircle->GetOutlineColor());
}

BOOST_AUTO_TEST_CASE(read_triangle)
{
	const CTriangle* pTriangle = dynamic_cast<CTriangle*>(&*draft[indexTriangle]);

	const sf::Vector2f firstPosition = { 10.f, 0.f };
	const sf::Vector2f secondPosition = { -10.f, 0.f };
	const sf::Vector2f thirdPosition = { 0.f, 10.f };
	const sf::Color fillColor(21, 245, 53);
	const sf::Color outlineColor(22, 246, 54);

	VerifyVector2f(firstPosition, pTriangle->GetFirstPoint());
	VerifyVector2f(secondPosition, pTriangle->GetSecondPoint());
	VerifyVector2f(thirdPosition, pTriangle->GetThirdPoint());
	VerifyColor(fillColor, pTriangle->GetFillColor());
	VerifyColor(outlineColor, pTriangle->GetOutlineColor());
}

BOOST_AUTO_TEST_CASE(read_line)
{
	const CLineSegment* pLine = dynamic_cast<CLineSegment*>(&*draft[indexLine]);

	const sf::Vector2f firstPosition = { 11.f, 0.f };
	const sf::Vector2f secondPosition = { -11.f, 11.f };
	const sf::Color fillColor(23, 247, 55);

	VerifyVector2f(firstPosition, pLine->GetFirstPoint());
	VerifyVector2f(secondPosition, pLine->GetSecondPoint());
	VerifyColor(fillColor, pLine->GetFillColor());
}

BOOST_AUTO_TEST_SUITE_END()// ShapeReader_
