#include "stdafx.h"
#include "FormDataExtractor.h"
#include <boost\lexical_cast.hpp>

namespace FormDataExtractor
{
	float GetEditValue(CEdit const& edit)
	{
		/*try
		{*/

		CString str;
		edit.GetWindowTextW(str);
		/*}
		catch (boost::bad_lexical_cast* e)
		{
			return 0;
		}*/
		
		return boost::lexical_cast<float>(str.GetBuffer());
	}
}
