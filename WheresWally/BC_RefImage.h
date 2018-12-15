#ifndef refImage
#define refImage

#include "BC_Image.h"
#include "BC_LargeImage.h"

class RefImage : public Image 
{
public:
	int offsetX, offsetY;
	double Compare(LargeImage* largeTemp, int offsetX, int offsetY);

	RefImage();
	//RefImage(int width, int height, int offsetX, int offsetY);

	using Image::Image;

	using Image::operator+=;
	using Image::operator-=;
	using Image::operator*=;
	using Image::operator =;
};

#endif // !refImage

