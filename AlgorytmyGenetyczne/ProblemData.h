#pragma once

#include <string>

template <class T>
class ProblemData{
public:
	ProblemData() {};
	virtual ~ProblemData() {};

	virtual void loadFromFile(std::string fileName) = 0;

};

