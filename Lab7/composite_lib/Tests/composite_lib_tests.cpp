// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "composite_lib_tests.h"

using namespace std;

namespace
{
	static string NOT_SHAPES = "No shapes to group";
	static string INDEX_OUT_OF_RANGE = "Index out range";

	bool Equal(float first, float second)
	{
		return abs(first - second) < 0.001f;
	}

	bool CompareFrames(const RectF & first, const RectF & second)
	{
		return Equal(first.left , second.left) 
			&& Equal(first.top , second.top)
			&& Equal(first.width , second.width)
			&& Equal(first.height , second.height);
	}

}

struct EmptyGroupFixture
{
	EmptyGroupFixture()
	{
	}

	CGroup emptyGroup;
};

BOOST_FIXTURE_TEST_SUITE(EmptyGroup, EmptyGroupFixture)

	BOOST_AUTO_TEST_SUITE(SetLineStyle)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					auto style = make_shared<CLineStyle>(false, 0xFFFFFFFF, 3.f);
					emptyGroup.SetLineStyle(style);
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetLineStyle)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					emptyGroup.GetLineStyle();
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()
		
	BOOST_AUTO_TEST_SUITE(SetFillStyle)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					auto style = make_shared<CFillStyle>(true, 0x001DFFFF);
					emptyGroup.SetFillStyle(style);
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetFillStyle)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					emptyGroup.GetFillStyle();
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetLineThickness)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					emptyGroup.SetLineThickness(1.f);
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetLineThickness)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					emptyGroup.GetLineThickness();
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetFrame)
		BOOST_AUTO_TEST_CASE(return_empty_frame)
		{
			BOOST_CHECK(CompareFrames(emptyGroup.GetFrame(), RectF(0,0,0,0)));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetFrame)
		BOOST_AUTO_TEST_CASE(throw_exception_runtime_error)
		{
			VerifyException<runtime_error>(
				[&]() {
					emptyGroup.SetFrame(RectF(1,1,2,2));
				},
				NOT_SHAPES
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapesCount)
		BOOST_AUTO_TEST_CASE(return_zero)
		{
			BOOST_CHECK_EQUAL(emptyGroup.GetShapesCount(), size_t(0));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapeAtIndex)
		BOOST_AUTO_TEST_CASE(throw_exception_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					emptyGroup.GetShapeAtIndex(0);
				},
				INDEX_OUT_OF_RANGE
			);
		}
	BOOST_AUTO_TEST_SUITE_END()
	

	BOOST_AUTO_TEST_SUITE(RemoveShapeAtIndex)
		BOOST_AUTO_TEST_CASE(throw_exception_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					emptyGroup.RemoveShapeAtIndex(0);
				},
				INDEX_OUT_OF_RANGE
			);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(InsertShape)
		BOOST_AUTO_TEST_CASE(can_insert_to_start)
		{
			auto shape = make_shared<CRectangle>();
			emptyGroup.InsertShape(shape, 0);

			BOOST_CHECK_EQUAL(emptyGroup.GetShapeAtIndex(0), shape);
		}
		BOOST_AUTO_TEST_CASE(can_not_insert_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					emptyGroup.InsertShape(make_shared<CRectangle>(), 1);
				},
				INDEX_OUT_OF_RANGE
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()// EmptyGroup


struct GroupWitnShapesFixture
{
	GroupWitnShapesFixture()
		: newFillStyle(make_shared<CFillStyle>(false, 0xFF0000FF))
		, newLineStyle(make_shared<CLineStyle>(true, 0x110000FF, 2.f))
		, rectangleFrame(0.f, 0.f, 1.f, 1.f)
		, triangleFrame(3.f, 0.f, 1.f, 1.f)
		, ellipseFrame(1.5f, 3.f, 1.f, 1.f)
		, group(make_shared<CGroup>())
	{
		for (size_t i = 0; i < 3; ++i)
		{
			oldFillStyle.push_back(make_shared<CFillStyle>(true, 0x000000FF));
			oldLineStyle.push_back(make_shared<CLineStyle>(false, 0x010000FF, 1.f));
		}

		rectangle = make_shared<CRectangle>(rectangleFrame, oldFillStyle[0], oldLineStyle[0]);
		triangle = make_shared<CTriangle>(triangleFrame, oldFillStyle[1], oldLineStyle[1]);
		ellipse = make_shared<CEllipse>(ellipseFrame, oldFillStyle[2], oldLineStyle[2]);

		group->InsertShape(rectangle, 0);
		group->InsertShape(triangle, 0);
		group->InsertShape(ellipse, 0);
	}
	const float newThikness = 5.f;

	const RectF rectangleFrame;
	const RectF triangleFrame;
	const RectF ellipseFrame;

	vector<shared_ptr<CFillStyle>> oldFillStyle;
	shared_ptr<CFillStyle> newFillStyle;
	vector<shared_ptr<CLineStyle>> oldLineStyle;
	shared_ptr<CLineStyle> newLineStyle;

	shared_ptr<CRectangle> rectangle;
	shared_ptr<CTriangle> triangle;
	shared_ptr<CEllipse> ellipse;
	shared_ptr<CGroup> group;
};

	BOOST_FIXTURE_TEST_SUITE(GroupWitnShapes, GroupWitnShapesFixture)

	BOOST_AUTO_TEST_SUITE(SetLineStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			group->SetLineStyle(newLineStyle);
			BOOST_CHECK_EQUAL(rectangle->GetLineStyle(), newLineStyle);
			BOOST_CHECK_EQUAL(triangle->GetLineStyle(), newLineStyle);
			BOOST_CHECK_EQUAL(ellipse->GetLineStyle(), newLineStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetLineStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			rectangle->SetLineStyle(newLineStyle);
			BOOST_CHECK(group->GetLineStyle() == nullptr);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style_if_styles_is_equal)
		{
			group->SetLineStyle(newLineStyle);
			BOOST_CHECK_EQUAL(group->GetLineStyle(), newLineStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetFillStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			group->SetFillStyle(newFillStyle);
			BOOST_CHECK_EQUAL(rectangle->GetFillStyle(), newFillStyle);
			BOOST_CHECK_EQUAL(triangle->GetFillStyle(), newFillStyle);
			BOOST_CHECK_EQUAL(ellipse->GetFillStyle(), newFillStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetFillStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			rectangle->SetFillStyle(newFillStyle);
			BOOST_CHECK(group->GetFillStyle() == nullptr);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style_if_styles_is_equal)
		{
			group->SetFillStyle(newFillStyle);
			BOOST_CHECK_EQUAL(group->GetFillStyle(), newFillStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetLineThickness)
		BOOST_AUTO_TEST_CASE(thikness_assingned_for_all_shapes)
		{
			group->SetLineThickness(newThikness);
			BOOST_CHECK(rectangle->GetLineThickness() == boost::optional<float>(newThikness));
			BOOST_CHECK(triangle->GetLineThickness() == boost::optional<float>(newThikness));
			BOOST_CHECK(ellipse->GetLineThickness() == boost::optional<float>(newThikness));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetLineThickness)
		BOOST_AUTO_TEST_CASE(return_boost_optional_none_if_thicknesses_not_equal)
		{
			rectangle->SetLineThickness(newThikness);
			BOOST_CHECK(group->GetLineThickness() == boost::none);
		}
		BOOST_AUTO_TEST_CASE(return_common_thickness)
		{
			group->SetLineThickness(newThikness);
			BOOST_CHECK(group->GetLineThickness() == boost::optional<float>(newThikness));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(GetFrame)
	{		
		BOOST_CHECK(CompareFrames(group->GetFrame(), RectF(0.f, 0.f, 4.f, 4.f)));
	}

	BOOST_AUTO_TEST_SUITE(SetFrame)
		BOOST_AUTO_TEST_CASE(shapes_for_set_new_frame_change_own_frame)
		{
			const RectF newFrame = RectF(0.f, 0.f, 8.f, 6.f);
			group->SetFrame(newFrame);
			BOOST_CHECK(CompareFrames(group->GetFrame(), newFrame));
			BOOST_CHECK(CompareFrames(rectangle->GetFrame(), RectF(0.f, 0.f, 2.f, 1.5f)));
			BOOST_CHECK(CompareFrames(triangle->GetFrame(), RectF(6.f, 0.f, 2.f, 1.5f)));
			BOOST_CHECK(CompareFrames(ellipse->GetFrame(), RectF(3.0f, 4.5f, 2.f, 1.5f)));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapesCount)
		BOOST_AUTO_TEST_CASE(return_shapes_count)
		{
			BOOST_CHECK_EQUAL(group->GetShapesCount(), 3);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapeAtIndex)
		BOOST_AUTO_TEST_CASE(return_shape)
		{
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(2), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), ellipse);
		}
		BOOST_AUTO_TEST_CASE(can_not_return_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					group->GetShapeAtIndex(3);
				},
				INDEX_OUT_OF_RANGE
			);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(RemoveShapeAtIndex)
		BOOST_AUTO_TEST_CASE(can_remove_to_start)
		{
			group->RemoveShapeAtIndex(0);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), triangle);
		}
		BOOST_AUTO_TEST_CASE(can_remove_to_middle)
		{
			group->RemoveShapeAtIndex(1);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), ellipse);
		}
		BOOST_AUTO_TEST_CASE(can_remove_to_end)
		{
			group->RemoveShapeAtIndex(2);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), ellipse);
		}
		BOOST_AUTO_TEST_CASE(can_not_remove_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					group->RemoveShapeAtIndex(3);
				},
				INDEX_OUT_OF_RANGE
			);

		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(InsertShape)
		BOOST_AUTO_TEST_CASE(can_insert_to_start)
		{
			group->InsertShape(rectangle, 0);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(3), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(2), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), ellipse);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), rectangle);
		}
		BOOST_AUTO_TEST_CASE(can_insert_to_middle)
		{
			group->InsertShape(rectangle, 1);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(3), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(2), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), ellipse);

		}
		BOOST_AUTO_TEST_CASE(can_insert_to_end)
		{
			group->InsertShape(triangle, 3);

			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(3), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(2), rectangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(1), triangle);
			BOOST_CHECK_EQUAL(group->GetShapeAtIndex(0), ellipse);

		}
		BOOST_AUTO_TEST_CASE(can_not_insert_out_of_range)
		{
			VerifyException<out_of_range>(
				[&]() {
					group->InsertShape(rectangle, 4);
				},
				INDEX_OUT_OF_RANGE
			);

		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(GetShapesIndex)
		BOOST_AUTO_TEST_CASE(return_shape_index)
		{
			BOOST_CHECK_EQUAL(group->GetShapesIndex(rectangle), 2);
			BOOST_CHECK_EQUAL(group->GetShapesIndex(triangle), 1);
			BOOST_CHECK_EQUAL(group->GetShapesIndex(ellipse), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()// GroupWitnShapes




struct GroupWitnShapeAndGroupFixture : public GroupWitnShapesFixture
{
	GroupWitnShapeAndGroupFixture()
		: secondRectangleFrame(4.f, 4.f, 1.f, 1.f)
		, secondGroup(make_shared<CGroup>())
		, oldFillStyle2(make_shared<CFillStyle>(true, 0x000000FF))
		, oldLineStyle2(make_shared<CLineStyle>(false, 0x010000FF, 1.f))
	{

		secondRectangle = make_shared<CRectangle>(secondRectangleFrame, oldFillStyle2, oldLineStyle2);

		secondGroup->InsertShape(secondRectangle, 0);
		secondGroup->InsertShape(group, 1);
	}

	const RectF secondRectangleFrame;

	shared_ptr<CFillStyle> oldFillStyle2;
	shared_ptr<CLineStyle> oldLineStyle2;

	shared_ptr<CRectangle> secondRectangle;
	shared_ptr<CGroup> secondGroup;
};

BOOST_FIXTURE_TEST_SUITE(GroupWitnShapesAndGroup, GroupWitnShapeAndGroupFixture)

	BOOST_AUTO_TEST_SUITE(SetLineStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			secondGroup->SetLineStyle(newLineStyle);
			BOOST_CHECK_EQUAL(rectangle->GetLineStyle(), newLineStyle);
			BOOST_CHECK_EQUAL(triangle->GetLineStyle(), newLineStyle);
			BOOST_CHECK_EQUAL(ellipse->GetLineStyle(), newLineStyle);
			BOOST_CHECK_EQUAL(group->GetLineStyle(), newLineStyle);

			BOOST_CHECK_EQUAL(secondRectangle->GetLineStyle(), newLineStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetLineStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			secondRectangle->SetLineStyle(newLineStyle);
			BOOST_CHECK(secondGroup->GetLineStyle() == nullptr);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style_if_styles_is_equal)
		{
			secondGroup->SetLineStyle(newLineStyle);
			BOOST_CHECK_EQUAL(secondGroup->GetLineStyle(), newLineStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetFillStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			secondGroup->SetFillStyle(newFillStyle);
			BOOST_CHECK_EQUAL(rectangle->GetFillStyle(), newFillStyle);
			BOOST_CHECK_EQUAL(triangle->GetFillStyle(), newFillStyle);
			BOOST_CHECK_EQUAL(ellipse->GetFillStyle(), newFillStyle);
			BOOST_CHECK_EQUAL(group->GetFillStyle(), newFillStyle);

			BOOST_CHECK_EQUAL(secondRectangle->GetFillStyle(), newFillStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetFillStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			secondRectangle->SetFillStyle(newLineStyle);
			BOOST_CHECK(secondGroup->GetFillStyle() == nullptr);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style_if_styles_is_equal)
		{
			secondGroup->SetFillStyle(newLineStyle);
			BOOST_CHECK_EQUAL(secondGroup->GetFillStyle(), newLineStyle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetLineThickness)
		BOOST_AUTO_TEST_CASE(thikness_assingned_for_all_shapes)
		{
			secondGroup->SetLineThickness(newThikness);
			BOOST_CHECK(rectangle->GetLineThickness() == boost::optional<float>(newThikness));
			BOOST_CHECK(triangle->GetLineThickness() == boost::optional<float>(newThikness));
			BOOST_CHECK(ellipse->GetLineThickness() == boost::optional<float>(newThikness));
			BOOST_CHECK(group->GetLineThickness() == boost::optional<float>(newThikness));

			BOOST_CHECK(secondRectangle->GetLineThickness() == boost::optional<float>(newThikness));
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(GetLineThickness)
		BOOST_AUTO_TEST_CASE(return_boost_optional_none_if_thicknesses_not_equal)
		{
			secondRectangle->SetLineThickness(newThikness);
			BOOST_CHECK(secondGroup->GetLineThickness() == boost::none);
		}
		BOOST_AUTO_TEST_CASE(return_common_thickness)
		{
			secondGroup->SetLineThickness(newThikness);
			BOOST_CHECK(secondGroup->GetLineThickness() == boost::optional<float>(newThikness));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(GetFrame)
	{
		BOOST_CHECK(CompareFrames(secondGroup->GetFrame(), RectF(0.f, 0.f, 5.f, 5.f)));
	}

	BOOST_AUTO_TEST_SUITE(SetFrame)
		BOOST_AUTO_TEST_CASE(shapes_for_set_new_frame_change_own_frame)
		{
			const RectF newFrame = RectF(0.f, 0.f, 10.f, 7.5f);
			secondGroup->SetFrame(newFrame);
			BOOST_CHECK(CompareFrames(secondGroup->GetFrame(), newFrame));
			BOOST_CHECK(CompareFrames(secondRectangle->GetFrame(), RectF(8.f, 6.f, 2.f, 1.5f)));

			BOOST_CHECK(CompareFrames(group->GetFrame(), RectF(0.f, 0.f, 8.f, 6.f)));
			BOOST_CHECK(CompareFrames(rectangle->GetFrame(), RectF(0.f, 0.f, 2.f, 1.5f)));
			BOOST_CHECK(CompareFrames(triangle->GetFrame(), RectF(6.f, 0.f, 2.f, 1.5f)));
			BOOST_CHECK(CompareFrames(ellipse->GetFrame(), RectF(3.0f, 4.5f, 2.f, 1.5f)));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapesCount)
		BOOST_AUTO_TEST_CASE(return_shapes_count)
		{
			BOOST_CHECK_EQUAL(secondGroup->GetShapesCount(), 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapeAtIndex)
		BOOST_AUTO_TEST_CASE(return_shape)
		{
			BOOST_CHECK_EQUAL(secondGroup->GetShapeAtIndex(1), group);
			BOOST_CHECK_EQUAL(secondGroup->GetShapeAtIndex(0), secondRectangle);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapesIndex)
		BOOST_AUTO_TEST_CASE(return_shape_index)
		{
			BOOST_CHECK_EQUAL(secondGroup->GetShapesIndex(group), 1);
			BOOST_CHECK_EQUAL(secondGroup->GetShapesIndex(secondRectangle), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()// GroupWitnShapesAndGroup