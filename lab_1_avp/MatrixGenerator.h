#pragma once
#include "Matrix.h"
#include<random>
#include<iostream>
class MatrixGenerator
{
private:
	std::mt19937 mersenne;
public:
	MatrixGenerator();
	const void* create(const Config& config) throw(IlligalArgumentException);
	const void* create(const Config& config, const unsigned) throw(IlligalArgumentException);
	~MatrixGenerator() = default;
};
