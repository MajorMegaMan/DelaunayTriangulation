#include "pch.h"
#include "DelPoint.h"

DelPoint::DelPoint(const Vector2& point)
{
	x = point.x;
	y = point.y;
}

void DelPoint::SwapValues(DelPoint& other)
{
	DelPoint temp = other;
	other = *this;
	*this = temp;
}

bool DelPoint::TrySortLower(DelPoint& other)
{
	if (SortDirection(other) > 0)
	{
		SwapValues(other);
		return true;
	}
	return false;
}

void DelPoint::TrySortLower(DelPoint& other, bool& runningSuccessCheck)
{
	if (SortDirection(other) > 0)
	{
		SwapValues(other);
		runningSuccessCheck = true;
	}
}
