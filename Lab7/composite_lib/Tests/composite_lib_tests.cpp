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
	{
	}

};

	BOOST_FIXTURE_TEST_SUITE(GroupWitnShapes, GroupWitnShapesFixture)

	BOOST_AUTO_TEST_SUITE(SetLineStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetLineStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(SetFillStyle)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetFillStyle)
		BOOST_AUTO_TEST_CASE(return_nullptr_if_styles_not_equal)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(return_pointer_to_common_style)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetLineThickness)
		BOOST_AUTO_TEST_CASE(style_assingned_for_all_shapes)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetLineThickness)
		BOOST_AUTO_TEST_CASE(return_boost_optional_none_if_thicknesses_not_equal)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(return_common_thickness)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(GetFrame)
	{
		BOOST_CHECK(false);
	}

	BOOST_AUTO_TEST_SUITE(SetFrame)
		BOOST_AUTO_TEST_CASE(return_frame_where_exist_all_shapes)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(shapes_for_set_new_frame_change_own_frame)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapesCount)
		BOOST_AUTO_TEST_CASE(return_shapes_count)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetShapeAtIndex)
		BOOST_AUTO_TEST_CASE(return_shape)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(RemoveShapeAtIndex)
		BOOST_AUTO_TEST_CASE(can_remove_to_start)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_remove_to_middle)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_remove_to_end)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_not_remove_out_of_range)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(InsertShape)
		BOOST_AUTO_TEST_CASE(can_insert_to_start)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_insert_to_middle)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_insert_to_end)
		{
			BOOST_CHECK(false);
		}
		BOOST_AUTO_TEST_CASE(can_not_insert_out_of_range)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(GetShapesIndex)
		BOOST_AUTO_TEST_CASE(return_shape_index)
		{
			BOOST_CHECK(false);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()// GroupWitnShapes
