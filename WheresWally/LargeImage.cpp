#include "BC_LargeImage.h"

void LargeImage::CreateBorder(int xOffset, int yOffset, int width, int height, int thickness, double color) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x < thickness || y < thickness || y + thickness >= height || x + thickness >= width) {
				setValue(x + xOffset, y + yOffset, color);
			}
		}
	}
}