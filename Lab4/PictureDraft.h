#pragma once

#include <vector>
#include <boost/iterator/indirect_iterator.hpp>

#include "Shapes\Shapes.h"

class CPictureDraft
{

public:
	typedef std::vector<std::shared_ptr<CShape>> Storage;


	CPictureDraft();

	bool IsEmpty()const;

	//typedef boost::indirect_iterator<Storage::const_iterator, const CShape&> ConstIterator;
	typedef Storage::const_iterator ConstIterator;
	ConstIterator begin()const;

	ConstIterator end()const;

	void AddShape(std::shared_ptr<CShape> && shape);

	// TODO : see need it
	//CPictureDraft(CPictureDraft &&) = default;
	//CPictureDraft& operator=(CPictureDraft &&) = default;

	//CPictureDraft(const CPictureDraft &) = delete;
	//CPictureDraft& operator=(const CPictureDraft &) = delete;
private:
	Storage m_shapes;
};
