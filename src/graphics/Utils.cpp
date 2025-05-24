#pragma once
#include "Utils.h"

int VMath::DivFloor(int x, int y) const
{
	int res = x / y;
	int rem = x % y;
	int corr = (rem != 0 && ((rem < 0) != (y < 0)));
	return res - corr;
}