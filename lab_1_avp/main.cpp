#include<iostream>
#include<chrono>
#include"config.h"
#include"Matrix.h"
#include"MatrixGenerator.h"
#include"MatrixMultiplyer.h"
#include"Timer.h"
const Config config1{ 100,250,100,250 };
//const Config config2{ 2,100,2,100 };
const Config config2{ 8,100,8,100 };
const unsigned max_element_value = 10;

void doVectorCasual(Matrix&, Matrix&);
void doCasual(Matrix&, Matrix&);
void doUltimateIntelFastSupperHot(Matrix&, Matrix&);

int main() {
	Matrix matr1(config1);
	Matrix matr2(config2);
	Matrix matr3(config1);
	Matrix matr4(config2);
	try {
		doCasual(matr1, matr2);
		

		doVectorCasual(matr1, matr2);
	}
	catch (IlligalArgumentException exception) {
		std::cout << "ERROR: matrix are inconsistent.";
	}
}

void doVectorCasual(Matrix& matr1, Matrix& matr2) {
	std::cout << "vector casual:" << std::endl;
	Timer timer;
	timer.start();
	MatrixMultiplyer::multiply(matr1, matr2);
	std::cout << "period: " << timer.check() << std::endl;
}
void doCasual(Matrix& matr1, Matrix& matr2) {
	std::cout << "casual without vectorization:" << std::endl;
	Timer timer;
	timer.start();
	MatrixMultiplyer::multiplyWithoutVectorisation(matr1, matr2);
	std::cout << "period: " << timer.check() << std::endl;
}
void doUltimateIntelFastSupperHot(Matrix& matr1, Matrix& matr2){}