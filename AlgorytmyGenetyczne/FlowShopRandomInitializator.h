#pragma once

#include "Initializator.h"
#include "FlowShopProblem.h"
#include "Population.h"
#include "FlowShopProblemData.h"
#include "FlowShopIndividual.h"

class FlowShopRandomInitializator : public Initializator<FlowShopProblem> {
public:

	FlowShopRandomInitializator(ProblemData<FlowShopProblem>& data);

	void initialize(Population<FlowShopProblem>& pop);

};