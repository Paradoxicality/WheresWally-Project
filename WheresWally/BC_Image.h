#ifndef image
#define image

class Image {
public:
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	double** getMatrix();
	double getValue(int x, int y);
	void setValue(int x, int y, double value);

	Image& operator+=(const Image& temp);
	Image& operator-=(const Image& temp);
	Image& operator*=(const Image& temp);
	Image* operator=(const Image& temp);
	friend Image operator+(Image first, const Image& second);
	friend Image operator-(Image first, const Image& second);
	friend Image operator*(Image first, const Image& second);

	Image();
	Image(int width, int height);
	Image(int width, int height, double** matrix);


protected:
	double** matrix;
	int length;

private:
	int width, height;

};

#endif