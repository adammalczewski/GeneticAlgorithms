#include "timer.h"

Timer::Timer(){
	QueryPerformanceFrequency(&_freq);
}

void Timer::start(){
	QueryPerformanceCounter(&_startTime);
}

float Timer::getTime() const{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return float(t.QuadPart- _startTime.QuadPart)/ _freq.QuadPart*1000.0f;
}