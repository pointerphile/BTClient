#pragma once
class RNG
{
public:	
	RNG();
	virtual ~RNG();
	int GetRandomNumber(int iRangeMax, int iRangeMin);
};

