#pragma once

#include "Population.h"
#include "FlowShopProblem.h"
#include "CrossOverOperator.h"

class FlowShopCrossOverOper : public CrossOverOperator<FlowShopProblem> 
{
	bool *_isUsed1,*_isUsed2;
	int* _temp;
	int _jobsCount;
public:
	FlowShopCrossOverOper(int jobsCount);
	~FlowShopCrossOverOper();

	void crossOver(Population<FlowShopProblem>& pop);
};

