#include "MatrixGenerator.h"

MatrixGenerator::MatrixGenerator()
{
	std::random_device rd;
	mersenne = std::mt19937(rd());
}

const void* MatrixGenerator::create(const Config& config) throw(IlligalArgumentException) {
	long long unsigned iterations = config.CELL_HEIGHT *
		config.CELL_WIDTH *
		config.MATRIX_HEIGHT *
		config.MATRIX_WIDTH;
	int* data = new int[iterations];
	for (long long unsigned counter = 0; counter < iterations; counter++) {
		data[counter] = mersenne();
	}
	return data;
}
const void* MatrixGenerator::create(const Config& config, const unsigned max_value) throw(IlligalArgumentException) {
	long long unsigned iterations = config.CELL_HEIGHT *
		config.CELL_WIDTH *
		config.MATRIX_HEIGHT *
		config.MATRIX_WIDTH;
	int* data = new int[iterations];
	for (long long unsigned counter = 0; counter < iterations; counter++) {
		data[counter] = mersenne()%max_value;
	}
	return data;
}
