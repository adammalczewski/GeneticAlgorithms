#pragma once

#include "Initializator.h"
#include "FlowShopProblem.h"
#include "Population.h"
#include "FlowShopProblemData.h"
#include "FlowShopIndividual.h"

class FlowShopSAInitializator : public Initializator<FlowShopProblem> {
private:
	int _sivalue; //iterations' count
	int _s0value; //temperature at 0 time
	int _svvalue; //velocity of change
	int _snvalue; //neighbourhood size
public:

	const int& getSivalue() const {
		return _sivalue;
	}

	void setSivalue(const int sivalue) {
		_sivalue = sivalue;
	}

	const int& getS0Value() const {
		return _s0value;
	}

	void setS0Value(const int s0Value) {
		_s0value = s0Value;
	}

	const int& getSvvalue() const {
		return _svvalue;
	}

	void setSvvalue(const int svvalue) {
		_svvalue = svvalue;
	}

	const int& getSnvalue() const {
		return _snvalue;
	}

	void setSnvalue(const int snvalue) {
		_snvalue = snvalue;
	}

	explicit FlowShopSAInitializator(ProblemData<FlowShopProblem>& data);

	void initialize(Population<FlowShopProblem>& pop) override;

};