#include "stdafx.h"
#include "Document/Document.h"
#include "Document/DocumentItems/Image.h"
#include "Document/DocumentItems/Paragraph.h"

#include "TestingFunction.h"

using namespace std;

struct DocumentFixture
{
	DocumentFixture()
		: outOfRangeMessage("Index out range")
		, tempPath(document.GetTempPath().generic_string())
	{}

	string GenericPathFromTemp(const string name)
	{
		return tempPath + "/images/" + name;
	}
	CDocument document;
	const string outOfRangeMessage;
	const string tempPath;
};

BOOST_FIXTURE_TEST_SUITE(CDocument_tests, DocumentFixture)
	BOOST_AUTO_TEST_SUITE(constructor_tests)
		BOOST_AUTO_TEST_CASE(has_empty_title)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), "");
		}
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(0));
		}
		BOOST_AUTO_TEST_CASE(do_not_change_history)
		{
			BOOST_CHECK(!document.CanUndo());
			BOOST_CHECK(!document.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(throw_exceptions_if_item_index_is_out_of_range)
	{
		VerifyException<out_of_range>(
			[&]() {
				document.InsertParagraph("text 1", 1);
			},
			outOfRangeMessage
		);
		VerifyException<out_of_range>(
			[&]() {
				document.InsertImage("images/realImage.png", 190, 560, 1);
			},
			outOfRangeMessage
		);
		VerifyException<out_of_range>(
			[&]() {
				document.DeleteItem(0);
			},
			outOfRangeMessage
		);
		VerifyException<out_of_range>(
			[&]() {
				document.GetItem(0);
			},
			outOfRangeMessage
		);
	}

	struct SetTitle_Fixture : public DocumentFixture
	{
		SetTitle_Fixture()
			: title1("new")
			, title2("newest")
		{
			document.SetTitle(title1);
		}

		const std::string title1;
		const std::string title2;
	};
	BOOST_FIXTURE_TEST_SUITE(SetTitle_tests, SetTitle_Fixture)
		BOOST_AUTO_TEST_CASE(can_set_title)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), title1);
		}
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetTitle(), "");
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			document.SetTitle(title2);
			document.Undo();
			document.Undo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetTitle(), title1);
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetTitle(), title2);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	struct InsertParagraph_Fixture : public DocumentFixture
	{
		InsertParagraph_Fixture()
			: textFirstParagraph("text 1")
			, textSecondParagraph("text 2")
			, textThirdParagraph("text 3")
		{
			
		}

		const std::string textFirstParagraph;
		const std::string textSecondParagraph;
		const std::string textThirdParagraph;
	};
	BOOST_FIXTURE_TEST_SUITE(InsertParagraph_tests, InsertParagraph_Fixture)
		BOOST_AUTO_TEST_CASE(can_insert_paragraphs_in_any_positions)
		{
			auto p1 = document.InsertParagraph(textFirstParagraph);
			auto p2 = document.InsertParagraph(textSecondParagraph);
			auto p3 = document.InsertParagraph(textThirdParagraph, size_t(1));
			BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(3));
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetParagraph()->GetText(),
				textFirstParagraph
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(2).GetParagraph()->GetText(), 
				textSecondParagraph
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(1).GetParagraph()->GetText(),
				textThirdParagraph
			);

			BOOST_CHECK_EQUAL(
				p1->GetText(),
				textFirstParagraph
			);
			BOOST_CHECK_EQUAL(
				p2->GetText(),
				textSecondParagraph
			);
			BOOST_CHECK_EQUAL(
				p3->GetText(),
				textThirdParagraph
			);
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
			{
				auto p1 = document.InsertParagraph(textFirstParagraph);
				auto p2 = document.InsertParagraph(textSecondParagraph, 0);
				document.Undo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(1));
				BOOST_CHECK_EQUAL(
					p1->GetText(),
					textFirstParagraph
				);

				document.Undo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(0));

				document.Redo();
				BOOST_CHECK_EQUAL(
					p1->GetText(),
					textFirstParagraph
				);
				BOOST_CHECK_EQUAL(
					document.GetItem(0).GetParagraph()->GetText(),
					textFirstParagraph
				);

				document.Redo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(2));
				BOOST_CHECK_EQUAL(
					p2->GetText(),
					textSecondParagraph
				);
				BOOST_CHECK_EQUAL(
					document.GetItem(0).GetParagraph()->GetText(),
					textSecondParagraph
				);
			}
	BOOST_AUTO_TEST_SUITE_END()

	struct InsertImage_Fixture : public DocumentFixture
	{
		InsertImage_Fixture()
			: name1("image1.txt")
			, name2("image2.txt")
			, path1("images/" + name1)
			, path2("images/" + name2)
		{
			p1 = document.InsertImage(path1, width1, height1);
			p2 = document.InsertImage(path2, width2, height2, size_t(0));
		}

		void CheckFirtstImg()
		{
			BOOST_CHECK_EQUAL(p1->GetWidth(), width1);
			BOOST_CHECK_EQUAL(p1->GetHeight(), height1);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetWidth(),
				width1
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetHeight(),
				height1
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetPath(),
				GenericPathFromTemp(name1)
			);
		}
		void CheckSecondImg()
		{
			BOOST_CHECK_EQUAL(p2->GetWidth(), width2);
			BOOST_CHECK_EQUAL(p2->GetHeight(), height2);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetWidth(),
				width2
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetHeight(),
				height2
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetPath(),
				GenericPathFromTemp(name2)
			);
		}

		std::shared_ptr<IImage> p1;
		std::shared_ptr<IImage> p2;

		const string name1;
		const string name2;
		const std::string path1;
		const std::string path2;
		const unsigned width1 = 100;
		const unsigned width2 = 250;
		const unsigned height1 = 100;
		const unsigned height2 = 250;
	};
	BOOST_FIXTURE_TEST_SUITE(InsertImage_tests, InsertImage_Fixture)
		BOOST_AUTO_TEST_CASE(can_insert_images_in_any_positions)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(2));
			BOOST_CHECK_EQUAL(p1->GetWidth(), width1);
			BOOST_CHECK_EQUAL(p1->GetHeight(), height1);
			BOOST_CHECK_EQUAL(
				document.GetItem(1).GetImage()->GetWidth(),
				width1
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(1).GetImage()->GetHeight(),
				height1
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(1).GetImage()->GetPath(),
				GenericPathFromTemp(name1)
			);

			BOOST_CHECK_EQUAL(p2->GetWidth(), width2);
			BOOST_CHECK_EQUAL(p2->GetHeight(), height2);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetWidth(),
				width2
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetHeight(),
				height2
			);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetPath(),
				GenericPathFromTemp(name2)
			);
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
			{				
				document.Undo();
				CheckFirtstImg();

				document.Undo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(0));

				document.Redo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(1));
				CheckFirtstImg();

				document.Redo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(2));
				CheckSecondImg();
			}
	BOOST_AUTO_TEST_SUITE_END()

	struct DeleteItem_Fixture : public DocumentFixture
	{
		DeleteItem_Fixture()
		{
			img = document.InsertImage("images/image1.txt", 100, 100);
			p = document.InsertParagraph("text");
		}
		std::shared_ptr<IImage> img;
		std::shared_ptr<IParagraph> p;
	};
	BOOST_FIXTURE_TEST_SUITE(DeleteItem_tests, DeleteItem_Fixture)
		BOOST_AUTO_TEST_CASE(can_delete)
		{
			document.DeleteItem(1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(1));
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage(), img);

			document.DeleteItem(0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(0));
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
			{
				document.DeleteItem(0);
				document.DeleteItem(0);
				document.Undo();
				document.Undo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(2));
				document.Redo();
				document.Redo();
				BOOST_CHECK_EQUAL(document.GetItemsCount(), size_t(0));
			}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetItem_tests)
		BOOST_AUTO_TEST_CASE(can_give_access_to_any_element)
		{
			auto p1 = document.InsertParagraph("text 1");
			auto p2 = document.InsertImage("images/image1.txt", 200, 200);
			BOOST_CHECK(p1 == document.GetItem(0).GetParagraph());
			BOOST_CHECK(p2 == document.GetItem(1).GetImage());
		}
		BOOST_AUTO_TEST_CASE(can_give_const_access_to_any_element)
		{
			document.InsertParagraph("text 1");
			document.InsertImage("images/image1.txt", 200, 200);
			CDocument const*  constDoc = &document;

			constDoc->GetItem(0).GetParagraph();
			constDoc->GetItem(1).GetImage();
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(Save_test)
	{
		stringstream expectedresult;
		string imagePath1 = "images/realImage.png";
		string imagePath2 = "images/realImage2.png";
		{
			document.InsertParagraph("text 1");
			auto img1 = document.InsertImage(imagePath1, 100, 150);
			auto img2 = document.InsertImage(imagePath2, 240, 200);
			document.DeleteItem(2);
			document.Save("test.html");
		}
		BOOST_CHECK(boost::filesystem::exists("test/" + imagePath1));
		BOOST_CHECK(!boost::filesystem::exists("test/" + imagePath2));
	}

BOOST_AUTO_TEST_SUITE_END()