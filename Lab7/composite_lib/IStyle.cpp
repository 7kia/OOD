#include "stdafx.h"
#include "IStyle.h"

bool operator==(IStylePtr const & first, IStylePtr const & second)
{
	return (first && second)
		&& (first->IsEnabled() == second->IsEnabled())
		&& (first->GetColor() == second->GetColor());
}