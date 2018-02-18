#include "EvaluationFunction.h"

template <class T>
EvaluationFunction<T>::EvaluationFunction(ProblemData<T>& data): _data(data) {
}

template <class T>
EvaluationFunction<T>::~EvaluationFunction() {
}
