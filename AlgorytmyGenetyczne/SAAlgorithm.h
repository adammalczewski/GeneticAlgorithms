#pragma once
#include "EvolutionAlgorithm.h"
#include "SANeighbourhoodSelector.h"
#include "SASelection.h"

template <class T>
class SAAlgorithm : public EvolutionAlgorithm<T> {
protected:
	SASelection<T> _SASelectionOper;
	CrossOverOperator<T> _crossOverOper;
public:

	SAAlgorithm(SANeighbourhoodSelector<T>& neighbourhoodSelector, EvaluationFunction<T>& evaluationFunction, Initializator<T>& initializator) :
		EvolutionAlgorithm<T>(neighbourhoodSelector, _crossOverOper, _SASelectionOper, evaluationFunction, initializator) {
		EvolutionAlgorithm<T>::setPopulationSize(1);
		
	}

	std::vector<Statistics> execute(Individual<T>** bestIndividual) override {
		_SASelectionOper.reset();
		return EvolutionAlgorithm::execute(bestIndividual);
	}

	void setT0(float _T0) {
		_SASelectionOper.setT0(_T0);
	}

	const float& getTv() const {
		return _SASelectionOper.getTv();
	}

	void setTv(const float tv) {
		_SASelectionOper.setTv(tv);
	}

	~SAAlgorithm() {
	}

};
