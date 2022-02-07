#pragma once
#include<chrono>
using namespace std::chrono;
class Timer
{
private:
	high_resolution_clock::time_point startPoint;

	long long difference() {
		return duration_cast<microseconds>(high_resolution_clock::now() - startPoint).count();
	}
public:
	void start() {
		startPoint = high_resolution_clock::now();
	}

	double check() {
		return  (double)((double)difference()/1000000);
	}

	long double hr_check() {
		return  (long double)((long double)difference() / 1000000);
	}

	long long _check() {
		return  difference();
	}
};

