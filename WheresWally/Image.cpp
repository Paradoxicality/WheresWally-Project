#include "BC_Image.h"
#include <iostream>
/*

	int width, height, length;
	void getValue(int x, int y);
	void getValue(int x, int y);

	Image operator+=(const Image image);
	Image operator-=(const Image image);
	Image operator*=(const Image image);
	Image operator=(const Image image);
	friend Image operator+(Image first, const Image second);
	friend Image operator-(Image first, const Image second);
	friend Image operator*(Image first, const Image second);

	Image(int width, int height, double* matrix);
	~Image();

*/

double** Image::getMatrix() {
	return matrix;
}

double Image::getValue(int x, int y) {
	return matrix[y][x];
}

void Image::setValue(int x, int y, double value) {
	matrix[y][x] = value;
}

Image::Image() {
}

Image::Image(int width, int height, double** matrix) {
	this->width = width;
	this->height = height;
	this->length = width * height;
	this->matrix = matrix;
}

Image::Image(int width, int height) {
	this->width = width;
	this->height = height;
	this->length = width * height;
	this->matrix = new double*[this->height];
	for (int i = 0; i < this->height; i++)
		matrix[i] = new double[width];
}

Image operator+(Image first, const Image& second) {
	first += second; 
	return first;
}

Image operator-(Image first, const Image& second) {
	first -= second;
	return first;
}

Image operator*(Image first, const Image& second) {
	first *= second;
	return first;
}

Image & Image::operator+=(const Image& temp)
{
	Image holder = Image(this->width + temp.width, temp.height);

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			holder.setValue(i, j, this->matrix[i][j*this->width]);
		}
		for (int j = 0; j < temp.width; j++) {
			holder.setValue(this->width + j, i, temp.matrix[i][j*this->width]);
		}
	}

	return holder;
}

Image & Image::operator-=(const Image & temp)
{
	Image holder = Image(temp.width, temp.height);

	for (int i = 0; i < temp.height; i++) {
		for (int j = 0; j < temp.width; j++) {
			holder.setValue(j, i, this->matrix[i][j] - temp.matrix[i][j]);
		}
	}

	return holder;
}

Image & Image::operator*=(const Image & temp)
{
	double matrixValue = 0;

	Image holder = Image(temp.width, this->height);

	for (int i = 0; i < temp.width; i++) {
		for (int j = 0; j < temp.height; j++) {
			matrixValue = 0;

			for (int k = 0; k < this->width; k++) {
				matrixValue += this->matrix[j][k] + temp.matrix[k][i];
			}

			holder.setValue(i, j, matrixValue);
		}
	}

	return holder;
}

Image* Image::operator=(const Image & temp) {
	this->width = temp.width;
	this->height = temp.height;
	this->length = temp.length;
	this->matrix = temp.matrix;

	return this;
}
