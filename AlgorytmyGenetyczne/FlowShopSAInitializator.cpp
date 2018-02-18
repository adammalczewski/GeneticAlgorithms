#include "FlowShopSAInitializator.h"
#include "FlowShopEvaluationFunction.h"
#include "FlowShopRandomInitializator.h"
#include "SANeighbourhoodSelector.h"
#include "SAAlgorithm.h"
#include "FlowShopSANeighbourhoodOperSwapFewTimes.h"

FlowShopSAInitializator::FlowShopSAInitializator(ProblemData<FlowShopProblem>& data) : Initializator(data), _sivalue(0), _s0value(0), _svvalue(0), _snvalue(0) {

}

void FlowShopSAInitializator::initialize(Population<FlowShopProblem>& pop) {

	FlowShopRandomInitializator initializator(_data);
	FlowShopEvaluationFunction evaluationFunc(_data);
	FlowShopSANeighbourhoodOperSwapFewTimes neighbourhoodSelector;

	SAAlgorithm<FlowShopProblem> algorithm(neighbourhoodSelector, evaluationFunc, initializator);

	algorithm.setT0(_s0value);
	algorithm.setTv(_svvalue);
	neighbourhoodSelector.setNeighbourhoodSize(_snvalue);
	algorithm.stopCondition().setGenerationsCount(_sivalue);

	for (int i = 0; i < pop.getSize(); ++i) {
		algorithm.execute(&pop.getIndividuals()[i]);
	}

}
