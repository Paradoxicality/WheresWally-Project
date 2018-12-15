#include "BC_RefImage.h"
#include <algorithm>

RefImage::RefImage() {
	/*
	this->width = 0;
	this->height = 0;
	this->offsetX = 0;
	this->offsetY = 0;
	this->length = 0;
	this->matrix = new double*[1];
	*/
}

//RefImage::RefImage(int width, int height, int offsetX, int offsetY) {
//	this->width = width;
//	this->height = height;
//	this->length = width * height;
//	this->offsetX = offsetX;
//	this->offsetY = offsetY;
//
//	this->matrix = new double*[this->height];
//	for (int i = 0; i < this->height; i++)
//		matrix[i] = new double[width];
//}

double RefImage::Compare(LargeImage* largeTemp, int offsetX, int offsetY) {
	double accuracy = 0.0;
	
	for (int y = 0; y < this->getHeight(); y++) {
		for (int x = 0; x < this->getWidth(); x++) {
			double largeValue = largeTemp->getValue(x + offsetX, y + offsetY);
			double refValue = this->getValue(x, y);
	
			if (refValue != 255) {
				accuracy += pow((largeValue - refValue), 2.0);
			}
		}
	}
	
	return accuracy;
}