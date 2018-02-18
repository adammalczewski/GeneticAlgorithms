#pragma once
#include <Windows.h>

class Timer{
	LARGE_INTEGER _freq;
	LARGE_INTEGER _startTime;
public:
	Timer();
	void start();
	float getTime() const; // in milliseconds
};