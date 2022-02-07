
#include "MatrixMultiplyer.h"
#include <immintrin.h>
#include<math.h>

const Matrix MatrixMultiplyer::multiply(const Matrix& matr1, const Matrix& matr2) {
	const Config& config1 = matr1.getConfig();
	const Config& config2 = matr2.getConfig();
	validateConfiguration(config1, config2);
	const int* data1 = matr1.getData();
	const int* data2 = matr2.getData();
	const Config resultConfig{ config2.CELL_WIDTH,
		config1.CELL_HEIGHT,
		config2.MATRIX_WIDTH,
		config1.MATRIX_HEIGHT
	};

	Matrix resultMatr(resultConfig);
	int* resultData = resultMatr.getData();

	int dataInsertCounter = 0;
	int iterations_1 = config2.MATRIX_WIDTH * config2.CELL_WIDTH;
	int iterations_0 = config1.MATRIX_HEIGHT * config1.CELL_HEIGHT;
	int iterations_2 = config1.CELL_WIDTH * config1.MATRIX_WIDTH;
	for (int counter_0 = 0; counter_0 < iterations_0; counter_0++) {
		for (int counter_1 = 0; counter_1 < iterations_1; counter_1++, dataInsertCounter++) {
			for (int counter_2 = 0; counter_2 < iterations_2; counter_2++) {
				resultData[dataInsertCounter] +=
					data1[counter_0 * resultConfig.MATRIX_WIDTH + counter_2] *
					data2[counter_2 * resultConfig.MATRIX_WIDTH + counter_1];
			}
		}
	}
	return resultMatr;
}

const Matrix MatrixMultiplyer::multiplyWithoutVectorisation(const Matrix& matr1, const Matrix& matr2)
{
	const Config& config1 = matr1.getConfig();
	const Config& config2 = matr2.getConfig();
	validateConfiguration(config1, config2);
	const int* data1 = matr1.getData();
	const int* data2 = matr2.getData();
	const Config resultConfig{ config2.CELL_WIDTH,
		config1.CELL_HEIGHT,
		config2.MATRIX_WIDTH,
		config1.MATRIX_HEIGHT
	};

	Matrix resultMatr(resultConfig);
	int* resultData = resultMatr.getData();

	int dataInsertCounter = 0;
	int iterations_1 = config2.MATRIX_WIDTH * config2.CELL_WIDTH;
	int iterations_0 = config1.MATRIX_HEIGHT * config1.CELL_HEIGHT;
	int iterations_2 = config1.CELL_WIDTH * config1.MATRIX_WIDTH;
#pragma loop(no_vector)
	for (int counter_0 = 0; counter_0 < iterations_0; counter_0++) {
#pragma loop(no_vector)
		for (int counter_1 = 0; counter_1 < iterations_1; counter_1++, dataInsertCounter++) {
#pragma loop(no_vector)
			for (int counter_2 = 0; counter_2 < iterations_2; counter_2++) {
				resultData[dataInsertCounter] +=
					data1[counter_0 * resultConfig.MATRIX_WIDTH + counter_2] *
					data2[counter_2 * resultConfig.MATRIX_WIDTH + counter_1];
			}
		}
	}
	return resultMatr;
}

int* MatrixMultiplyer::multiplyAVX2(const Matrix& matr1, const Matrix& matr2)
{
	const Config& config1 = matr1.getConfig();
	const Config& config2 = matr2.getConfig();
	validateConfiguration(config1, config2);
	const int* data1 = matr1.getData();
	const int* data2 = matr2.getData();
	const Config resultConfig{ config2.CELL_WIDTH,
		config1.CELL_HEIGHT,
		config2.MATRIX_WIDTH,
		config1.MATRIX_HEIGHT
	};
	const int consistent_size = config1.CELL_WIDTH * config1.MATRIX_WIDTH;
	const int virt_hor_size = resultConfig.CELL_WIDTH * resultConfig.MATRIX_WIDTH;
	const int virt_ver_size = resultConfig.CELL_HEIGHT * resultConfig.MATRIX_HEIGHT;
	const int pack_amount = (consistent_size + 63) / 64;
	const int pack_size = 8;
	const int sum_iter_amount = ceil(log(pack_amount) / log(pack_size));
	int* buffer = new int[pack_amount];
	int* sums_amounts = new int[sum_iter_amount];

	__m256i* hLine = new __m256i[pack_amount];
	__m256i* vLine = new __m256i[pack_amount];
	__m256i* resLine = new __m256i[pack_amount];
	__m256i mask = _mm256_setr_epi32(-1, -1, -1, -1, -1, -1, -1, -1);
	__m256i endMask = createEndMask(8 - (pack_amount * 64 - virt_hor_size));

	int* resultData = new int[virt_hor_size*virt_ver_size];

	for (int counter_0 = 0; counter_0 < virt_hor_size; counter_0++) {
		for (int counter = 0; counter < pack_amount-1; counter++) {
			const int step = virt_hor_size * counter * 8 + counter_0;
			vLine[counter] = _mm256_setr_epi32(
				data2[step + virt_hor_size * 0],
				data2[step + virt_hor_size * 1],
				data2[step + virt_hor_size * 2],
				data2[step + virt_hor_size * 3],
				data2[step + virt_hor_size * 4],
				data2[step + virt_hor_size * 5],
				data2[step + virt_hor_size * 6],
				data2[step + virt_hor_size * 7]
			);
		}

		const int step = virt_hor_size * (pack_amount - 1) * 8 + counter_0;
		hLine[pack_amount - 1] = _mm256_setr_epi32(
			data2[step + virt_hor_size * 0],
			data2[step + virt_hor_size * 1],
			data2[step + virt_hor_size * 2],
			data2[step + virt_hor_size * 3],
			data2[step + virt_hor_size * 4],
			data2[step + virt_hor_size * 5],
			data2[step + virt_hor_size * 6],
			data2[step + virt_hor_size * 7]
		);

		for (int counter_1 = 0; counter_1 < virt_ver_size; counter_1++) {
			for (int counter = 0; counter < pack_amount - 1; counter++) {
				hLine[counter] = _mm256_maskload_epi32((data1 + counter * 256), mask);
			}
			hLine[pack_amount - 1] = _mm256_maskload_epi32((data1 + (pack_amount - 1) * 256), endMask);

			for (int counter = 0; counter < pack_amount; counter++) {
				resLine[counter] = _mm256_mul_epi32(hLine[counter], vLine[counter]);
			}
			
			for (int counter = 0; counter < sum_iter_amount; counter++) {


			}
		}
	}
	return resultData;
}

void MatrixMultiplyer::validateConfiguration(const Config& config1, const Config& config2) throw(IlligalArgumentException) {
	if (config1.CELL_WIDTH != config2.CELL_HEIGHT ||
		config1.MATRIX_WIDTH != config2.MATRIX_HEIGHT) {
		throw IlligalArgumentException("Matrixes aren't consistent.");
	}
}

__m256i MatrixMultiplyer::createEndMask(int size)
{
	int maskArr[8]{ 0 };
	for (int counter = 0; counter < size && counter < 8; counter++) {
		maskArr[counter] = -1;
	}
	
	return _mm256_setr_epi32(
		maskArr[0],
		maskArr[1], 
		maskArr[2], 
		maskArr[3], 
		maskArr[4], 
		maskArr[5], 
		maskArr[6], 
		maskArr[7]
	);
}
