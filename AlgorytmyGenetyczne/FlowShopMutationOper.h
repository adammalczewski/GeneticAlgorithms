#pragma once

#include "MutationOperator.h"
#include "FlowShopProblem.h"
#include "Population.h"
#include "FlowShopIndividual.h"

class FlowShopMutationOper : public MutationOperator<FlowShopProblem>{
public:
	FlowShopMutationOper();
	~FlowShopMutationOper();

	void mutate(Population<FlowShopProblem>& pop);

};

