#pragma once


template <class T>
class SelectionOperator {
public:
	SelectionOperator() {};
	virtual ~SelectionOperator() {};

	virtual void select(Population<T>&pop, float* values) = 0;

};

