#pragma once

class StopCondition {
private:

	bool _generationsCountEnabled;
	int _generationsCount;

public:

	StopCondition() {
		_generationsCountEnabled = true;
		_generationsCount = 100;
	}

	const bool& getGenerationsCountEnabled() const {
		return _generationsCountEnabled;
	}

	void setGenerationsCountEnabled(const bool generationsCountEnabled) {
		_generationsCountEnabled = generationsCountEnabled;
	}

	const int& getGenerationsCount() const {
		return _generationsCount;
	}

	void setGenerationsCount(const int generationsCount) {
		_generationsCount = generationsCount;
	}

	//generationNumber is counted from 0
	bool shouldContinue(int generationNumber) const {

		bool result = true;

		if (_generationsCountEnabled && generationNumber >= _generationsCount) result = false;

		return result;
	}

};