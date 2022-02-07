#pragma once
#include "Matrix.h"
#include <immintrin.h>
class MatrixMultiplyer
{
public:
	static const Matrix multiply(const Matrix& matr1, const Matrix& matr2);
	static const Matrix multiplyWithoutVectorisation(const Matrix& matr1, const Matrix& matr2);
	static const Matrix multiplyAVX2(const Matrix& matr1, const Matrix& matr2);
	//static Matrix& assemblyMultiply(const Matrix& matr1, const Matrix& matr2) {	}
private:
	static void validateConfiguration(const Config& config1, const Config& config2) throw(IlligalArgumentException);
	static __m256i createEndMask(int);
	MatrixMultiplyer() = default;
	~MatrixMultiplyer() = default;
};

