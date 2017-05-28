#include "stdafx.h"
#include "ILineStyle.h"

bool operator==(ILineStylePtr const & first, ILineStylePtr const & second)
{
	return (first && second)
		&& (first->IsEnabled() == second->IsEnabled())
		&& (first->GetColor() == second->GetColor())
		&& (first->GetLineThikness() == second->GetLineThikness());
}