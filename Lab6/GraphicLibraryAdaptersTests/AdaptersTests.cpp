#include "stdafx.h"
#include "AdaptersTests.h"

struct SCommonData
{
	const std::array<int, 2> leftTopRectangle = { 0, 1 };
	const int rectangleWidth = 100;
	const int rectangleHeight = 75;
	const std::array<int, 2> firstTrianlgePoint = { 0, 0 };
	const std::array<int, 2> secondTrianlgePoint = { 100, 100 };
	const std::array<int, 2> thirdTrianlgePoint = { 75, 100 };

	const uint32_t rectangleColor = 0xFF0000;
	const uint32_t triangleColor = 0xFFFFFF;

};

struct CanvasClassAdapterFixture : public SCommonData
{
	std::stringstream stream;
	CCanvasClassAdapter adapter;

	std::string expectedStreamForRectangle;
	std::string expectedStreamForLine;
	std::string expectedStreamForTriangle;

	shape_drawing_lib::CCanvasPainter painter;
	shape_drawing_lib::CRectangle rectangle;
	shape_drawing_lib::CTriangle triangle;

	CanvasClassAdapterFixture()
		: adapter(stream)
		, painter(adapter)
		, rectangle(
			shape_drawing_lib::Point(leftTopRectangle[0], leftTopRectangle[1]),
			rectangleWidth,
			rectangleHeight
		)
		, triangle(
			shape_drawing_lib::Point(firstTrianlgePoint[0], firstTrianlgePoint[1]),
			shape_drawing_lib::Point(secondTrianlgePoint[0], secondTrianlgePoint[1]),
			shape_drawing_lib::Point(thirdTrianlgePoint[0], thirdTrianlgePoint[1])
		)
	{
		expectedStreamForRectangle = R"(<draw>
  <line fromX="0" fromY="1" toX="100" toY="1"/>
</draw>
<draw>
  <line fromX="100" fromY="1" toX="100" toY="76"/>
</draw>
<draw>
  <line fromX="100" fromY="76" toX="0" toY="76"/>
</draw>
<draw>
  <line fromX="0" fromY="76" toX="0" toY="1"/>
</draw>
)";

		expectedStreamForLine = R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="2"/>
</draw>
)";
		expectedStreamForTriangle = R"(<draw>
  <line fromX="0" fromY="0" toX="100" toY="100"/>
</draw>
<draw>
  <line fromX="100" fromY="100" toX="75" toY="100"/>
</draw>
<draw>
  <line fromX="75" fromY="100" toX="0" toY="0"/>
</draw>
)";
	}
};

struct CanvasObjectAdapterFixture : public SCommonData
{
	std::stringstream stream;
	modern_graphics_lib::CModernGraphicsRenderer renderer;
	CCanvasObjectAdapter adapter;

	std::string expectedStreamForRectangle;
	std::string expectedStreamForLine;
	std::string expectedStreamForTriangle;

	shape_drawing_lib::CCanvasPainter painter;
	shape_drawing_lib::CRectangle rectangle;
	shape_drawing_lib::CTriangle triangle;

	CanvasObjectAdapterFixture()
		: renderer(stream)
		, adapter(renderer)
		, painter(adapter)
		, rectangle(
			shape_drawing_lib::Point(leftTopRectangle[0], leftTopRectangle[1]),
			rectangleWidth,
			rectangleHeight
		)
		, triangle(
			shape_drawing_lib::Point(firstTrianlgePoint[0], firstTrianlgePoint[1]),
			shape_drawing_lib::Point(secondTrianlgePoint[0], secondTrianlgePoint[1]),
			shape_drawing_lib::Point(thirdTrianlgePoint[0], thirdTrianlgePoint[1])
		) {
		expectedStreamForRectangle = R"(<draw>
  <line fromX="0" fromY="1" toX="100" toY="1"/>
</draw>
<draw>
  <line fromX="100" fromY="1" toX="100" toY="76"/>
</draw>
<draw>
  <line fromX="100" fromY="76" toX="0" toY="76"/>
</draw>
<draw>
  <line fromX="0" fromY="76" toX="0" toY="1"/>
</draw>
)";

		expectedStreamForLine = R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="2"/>
</draw>
)";
		expectedStreamForTriangle = R"(<draw>
  <line fromX="0" fromY="0" toX="100" toY="100"/>
</draw>
<draw>
  <line fromX="100" fromY="100" toX="75" toY="100"/>
</draw>
<draw>
  <line fromX="75" fromY="100" toX="0" toY="0"/>
</draw>
)";

	}
};

struct CanvasColoredAdapterFixture : public SCommonData
{
	std::stringstream stream;
	CCanvasColoredAdapter adapter;

	std::string expectedStreamForRectangle;
	std::string expectedStreamForLine;
	std::string expectedStreamForTriangle;

	shape_drawing_lib_pro::CCanvasPainter painter;
	shape_drawing_lib_pro::CRectangle rectangle;
	shape_drawing_lib_pro::CTriangle triangle;

	CanvasColoredAdapterFixture()
		: adapter(stream)
		, painter(adapter)
		, rectangle(
			shape_drawing_lib_pro::Point(leftTopRectangle[0], leftTopRectangle[1]),
			rectangleWidth,
			rectangleHeight,
			rectangleColor
		)
		, triangle(
			shape_drawing_lib_pro::Point(firstTrianlgePoint[0], firstTrianlgePoint[1]),
			shape_drawing_lib_pro::Point(secondTrianlgePoint[0], secondTrianlgePoint[1]),
			shape_drawing_lib_pro::Point(thirdTrianlgePoint[0], thirdTrianlgePoint[1]),
			triangleColor
		) {
		adapter.SetColor(0xFFFFFF);

		expectedStreamForRectangle = R"(<draw>
  <line fromX="0" fromY="1" toX="100" toY="1">
    <color r="1.00" g="0.00" b="0.00" a="1.00" />
  </line>
</draw>
<draw>
  <line fromX="100" fromY="1" toX="100" toY="76">
    <color r="1.00" g="0.00" b="0.00" a="1.00" />
  </line>
</draw>
<draw>
  <line fromX="100" fromY="76" toX="0" toY="76">
    <color r="1.00" g="0.00" b="0.00" a="1.00" />
  </line>
</draw>
<draw>
  <line fromX="0" fromY="76" toX="0" toY="1">
    <color r="1.00" g="0.00" b="0.00" a="1.00" />
  </line>
</draw>
)";
			expectedStreamForLine = R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="2">
    <color r="1.00" g="1.00" b="1.00" a="1.00" />
  </line>
</draw>
)";
		expectedStreamForTriangle = R"(<draw>
  <line fromX="0" fromY="0" toX="100" toY="100">
    <color r="1.00" g="1.00" b="1.00" a="1.00" />
  </line>
</draw>
<draw>
  <line fromX="100" fromY="100" toX="75" toY="100">
    <color r="1.00" g="1.00" b="1.00" a="1.00" />
  </line>
</draw>
<draw>
  <line fromX="75" fromY="100" toX="0" toY="0">
    <color r="1.00" g="1.00" b="1.00" a="1.00" />
  </line>
</draw>
)";

	}
};

typedef boost::mpl::vector<CanvasClassAdapterFixture,
	CanvasObjectAdapterFixture,
	CanvasColoredAdapterFixture
> AdapterFixtures;

BOOST_AUTO_TEST_SUITE(when_used_as_canvas)
	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_draw_rectangle, T, AdapterFixtures, T)
	{
		painter.Draw(rectangle);

		BOOST_CHECK_EQUAL(stream.str(), expectedStreamForRectangle);
	}

	BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_draw_triangle, T, AdapterFixtures, T)
	{
		painter.Draw(triangle);
		BOOST_CHECK_EQUAL(stream.str(), expectedStreamForTriangle);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_CASE_TEMPLATE(can_draw_line, T, AdapterFixtures, T)
{
	adapter.MoveTo(0, 0);
	adapter.LineTo(1, 2);
	BOOST_CHECK_EQUAL(stream.str(), expectedStreamForLine);
}
