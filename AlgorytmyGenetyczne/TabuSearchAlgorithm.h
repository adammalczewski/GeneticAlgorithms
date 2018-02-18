#pragma once
#include "EvolutionAlgorithm.h"
#include "TabuNeighbourhoodSelector.h"
#include "TabuSlowSelection.h"

template <class T>
class TabuSearchAlgorithm : public EvolutionAlgorithm<T> {
protected:
	TabuSlowSelection<T> _tabuSelectionOper;
	CrossOverOperator<T> _crossOverOper;
public:

	TabuSearchAlgorithm(TabuNeighbourhoodSelector<T>& neighbourhoodSelector, EvaluationFunction<T>& evaluationFunction, Initializator<T>& initializator) :
		 EvolutionAlgorithm<T>(neighbourhoodSelector, _crossOverOper, _tabuSelectionOper, evaluationFunction, initializator), _tabuSelectionOper(neighbourhoodSelector._tabuTable) {
		EvolutionAlgorithm<T>::setPopulationSize(1);
	}

	~TabuSearchAlgorithm() {
	}

	virtual std::vector<Statistics> execute(Individual<T>** bestIndividual) override {

		_tabuSelectionOper.clearTabuTable();

		return EvolutionAlgorithm<T>::execute(bestIndividual);
	}

	void setTabuTableSize(int tabuTableSize) {
		_tabuSelectionOper.setTabuTableSize(tabuTableSize);
	}

	int getTabuTableSize() const {
		return _tabuSelectionOper.getTabuTableSize();
	}

};
