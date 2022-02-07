#include "Matrix.h"

Matrix::Matrix(const Config& config) : config(config) {
	data = new int[config.MATRIX_HEIGHT *
		config.MATRIX_WIDTH *
		config.CELL_HEIGHT *
		config.CELL_WIDTH]{0};	
}

Matrix::Matrix(const Config& config, void* data) : config(config) {
	validateInputData(config, data);
	data = (int*)data;
}

const Config& Matrix::getConfig() const {
	return config;
}

const int* Matrix::getData() const {
	return data;
}

int* Matrix::getData() {
	return data;
}

Matrix::~Matrix() {
	delete[] data;
}

void Matrix::validateInputData(const Config& config) const throw(IlligalArgumentException) {
	if (config.CELL_HEIGHT == 0 ||
		config.CELL_WIDTH == 0 ||
		config.MATRIX_HEIGHT == 0 ||
		config.MATRIX_WIDTH == 0) {
		throw IlligalArgumentException("Illigal config structure.");
	}

}

void Matrix::validateInputData(const Config& config, void* data) const throw(IlligalArgumentException) {
	validateInputData(config);
	/*
	try {
		((int*)data)[config.CELL_HEIGHT * config.CELL_WIDTH * config.MATRIX_HEIGHT * config.MATRIX_WIDTH];
	}
	catch (std::exception exception) {
		throw IlligalArgumentException("Illigal size raw data provided.");
	}
	*/
}

Matrix::Matrix(const Matrix& matrix) : config({ matrix.config.CELL_WIDTH,
		matrix.config.CELL_HEIGHT,
		matrix.config.MATRIX_WIDTH,
		matrix.config.MATRIX_HEIGHT }) {
	int elementsAmount = config.MATRIX_HEIGHT *
		config.MATRIX_WIDTH *
		config.CELL_HEIGHT *
		config.CELL_WIDTH;
	data = new int[elementsAmount];
	//std::memmove(data, matrix.data, sizeof(int) * elementsAmount);
}
