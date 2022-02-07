#pragma once
#include<malloc.h>
#include<stdlib.h>
#include"config.h"
#include "IlligalArgumentException.h"
#include <cstring>
#include<algorithm>
class Matrix
{
private:
	int* data;
	const Config& config;

public:
	Matrix(const Config&);
	Matrix(const Config&, void* );
	Matrix(const Matrix& matrix);
	const Config& getConfig() const;
	const int* getData() const;
	int* getData();
	~Matrix();
private:
	void validateInputData(const Config& config) const throw(IlligalArgumentException);
	void validateInputData(const Config& config, void* data) const throw(IlligalArgumentException);
};

