#pragma once
#include "Vector3.h"

struct DelPoint : Vector2
{
	int index = 0;

	DelPoint() {}
	DelPoint(const Vector2& point);

	////////////////////////////////////
	// SORTING FUNCTIONS

	// used for sorting
	void SwapValues(DelPoint& other);

	bool TrySortLower(DelPoint& other);
	void TrySortLower(DelPoint& other, bool& runningSuccessCheck);
	/////////////////////////////////////
};