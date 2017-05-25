#include "stdafx.h"
#include "FormDataExtractor.h"
#include <boost\lexical_cast.hpp>

namespace FormDataExtractor
{
	float GetEditValue(CEdit const& edit)
	{
		CString str;
		edit.GetWindowTextW(str);		
		return boost::lexical_cast<float>(str.GetBuffer());
	}
}
