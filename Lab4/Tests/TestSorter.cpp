#include "stdafx.h"
#include "TestSorter.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

bool TestSorter(const std::string & inputFile, const std::string & nameSortByPerimeter,
				const std::string & nameSortByArea)
{
	CShapeReader reader(inputFile);

	reader.SortContent(nameSortByPerimeter, nameSortByArea);
	
	return true;
}

void CompareFiles(const std::string & first, const std::string & second)
{
	std::ifstream resultFile(first);
	std::ifstream rightResultFile(second);

	std::istream_iterator<char> iterResultFile(resultFile), endIter;
	std::istream_iterator<char> iterRightRsultFile(rightResultFile);

	BOOST_CHECK_EQUAL_COLLECTIONS(iterResultFile, endIter, iterRightRsultFile, endIter);
};

BOOST_AUTO_TEST_CASE(throw_exception_for_nonexistent_file)
{
	const std::string nameInputFile = "shapes00.txt";
	const std::string nameSortByPerimeter = "sortByPerimeter1.txt";
	const std::string nameSortByArea = "sortByArea1.txt";

	BOOST_CHECK_THROW(TestSorter(nameInputFile, nameSortByPerimeter, nameSortByArea), std::ifstream::failure);
}

BOOST_AUTO_TEST_CASE(if_input_file_is_empty_then_create_empty_output_files)
{
	const std::string nameInputFile = "shapesEmpty.txt";
	const std::string nameSortByPerimeter = "sortByPerimeterEmpty.txt";
	const std::string nameSortByArea = "sortByAreaEmpty.txt";

	BOOST_CHECK(TestSorter(nameInputFile, nameSortByPerimeter, nameSortByArea));
	CompareFiles(nameSortByPerimeter, PATH_RIGHT_DATA + nameSortByPerimeter);
	CompareFiles(nameSortByArea, PATH_RIGHT_DATA + nameSortByArea);
}

BOOST_AUTO_TEST_CASE(sort_by_decrease_decrease_perimeter_and_increase_area)
{
	const std::string nameInputFile = "shapes1.txt";
	const std::string nameSortByPerimeter = "sortByPerimeter1.txt";
	const std::string nameSortByArea = "sortByArea1.txt";

	BOOST_CHECK(TestSorter(nameInputFile, nameSortByPerimeter, nameSortByArea));
	CompareFiles(nameSortByPerimeter, PATH_RIGHT_DATA + nameSortByPerimeter);
	CompareFiles(nameSortByArea, PATH_RIGHT_DATA + nameSortByArea);
}

BOOST_AUTO_TEST_SUITE_END()
