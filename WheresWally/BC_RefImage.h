#ifndef refImage
#define refImage

#include "BC_Image.h"

class RefImage : public Image 
{
public:
	int offsetX, offsetY;

	RefImage();
	//RefImage(int width, int height, int offsetX, int offsetY);

	using Image::Image;

	using Image::operator+=;
	using Image::operator-=;
	using Image::operator*=;
	using Image::operator =;
};

#endif // !refImage

