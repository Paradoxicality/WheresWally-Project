#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>

//To Do:
/*	Main:
	Search - Search the large image matrix by using the reference image matrix ontop
		   - Take Large Image, Reference Image, number of matches
		   - Create a vector of matches
		   - loop through the large image - width of reference
		   - Compare images
		   - Add the item to the match list
		   - Sort the match list
		   - Push out the last match
		   - Loop through match list and add a black border to the edge
	Compare - Compare submatrix to reference matrix
			- Loop through get the value from large matrix, get the value from reference matrix
			- If matrix value is less than 255 calculate the variance using square sum difference
			- Return the variance
	Sort - Sort the matrix
		 - Merge sor the match list
	Convert - array to matrix
			- matrix to array
	Read Image
	Write Image
*/

/*	Image:
	width, height, length (width*height)
	Get Matrix by index, and x and y position
	Set Matrix by index, and x and y position

	constructors - take width, height, double* []

	operator overloads

	deconstructor - delete matrix

	protected - double matrix


*/

/*	Match:
	contains offsets of the match
	contains value of accuracy
*/

/*	Reference Image:
	inherit Image:
	offeset from main matrix x, y
	user operator overloads

	inherits: constructors, deconstructors and operator overloads

*/

/*	Large Image:

	Create Sub Matrix - takes offsets, width and height

	inherits: constructors, deconstructors and operator overloads

*/


#include "BC_Image.h"
#include "BC_LargeImage.h"
#include "BC_RefImage.h"
#include "BC_RWFunc.h"
#include "BC_MatchPos.h"

#define LARGE_IMG_WIDTH 1024
#define LARGE_IMG_HEIGHT 768
#define REF_IMG_WIDTH 36
#define REF_IMG_HEIGHT 49
#define INPUT_LARGE_PATH "input/Cluttered_scene.txt"
#define INPUT_REF_PATH "input/Wally_grey.txt"
#define OUTPUT_IMG_PATH "output/Wally_found.pgm"

double** ConvertToMatrix(double* file, int width, int height) {
	double** tempMatrix = new double*[height];

	int length = width * height;
	for (int i = 0; i < height; i++) {
		tempMatrix[i] = new double[width];
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tempMatrix[y][x] = file[((width * y) + x)];
		}
	}

	return tempMatrix;
}

double* ConvertToFile(double** matrix) {
	double* tempFile = new double[LARGE_IMG_WIDTH * LARGE_IMG_HEIGHT];
	for (int y = 0; y < LARGE_IMG_HEIGHT; y++) {
		for (int x = 0; x < LARGE_IMG_WIDTH; x++) {
			tempFile[(LARGE_IMG_WIDTH * y) + x] = matrix[y][x];
		}
	}

	return tempFile;
}

void Sort(std::vector<MatchPos>& matchList) {
	int i, j;
	MatchPos item;

	for (i = 1; i < matchList.size(); i++) {
		item = matchList.at(i);
		j = i - 1;

		while (j >= 0 && matchList.at(j).accuracy > item.accuracy) {
			matchList.at(j + 1) = matchList.at(j);
			j = j - 1;
		}

		matchList.at(j + 1) = item;
	}
}

//double Compare(LargeImage* largeTemp, RefImage* refTemp, int offsetX, int offsetY) {
//	double accuracy = 0.0;
//
//	for (int y = 0; y < refTemp->getHeight(); y++) {
//		for (int x = 0; x < refTemp->getWidth(); x++) {
//			double largeValue = largeTemp->getValue(x + offsetX, y + offsetY);
//			double refValue = refTemp->getValue(x, y);
//
//			if (refValue != 255) {
//				accuracy += pow((largeValue - refValue), 2.0);
//			}
//		}
//	}
//
//	return accuracy;
//}

std::vector<MatchPos> Search(LargeImage* largeTemp, RefImage* refTemp, int matches) {
	std::vector<MatchPos> matchList;
	MatchPos newMatch;

	double ssd = 0.0;

	for (int y = 0; y < largeTemp->getHeight() - refTemp->getHeight(); y+=3) {
		for (int x = 0; x < largeTemp->getWidth() - refTemp->getWidth(); x+=3) {
			ssd = refTemp->Compare(largeTemp, x, y);

			newMatch = MatchPos(x, y, ssd);

			matchList.push_back(newMatch);

			if (matchList.size() > matches) {
				Sort(matchList);

				matchList.erase(matchList.begin() + matches);
			}
		}
	}

	return matchList;
}



int main()
{
	int matches = 0;
	int thickness = 3;
	RWFunc iofiles;

	double* largeImageData = iofiles.readText(INPUT_LARGE_PATH, LARGE_IMG_HEIGHT, LARGE_IMG_WIDTH);
	double* refImageData = iofiles.readText(INPUT_REF_PATH, REF_IMG_HEIGHT, REF_IMG_WIDTH);

	std::cout << "Enter the number of matches you would like to find: " << std::endl;
	while (!(std::cin >> matches) || matches <= 0) {
		std::cout << "Please enter a valid number of matches: " << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	LargeImage* largeTemp = new LargeImage(LARGE_IMG_WIDTH, LARGE_IMG_HEIGHT, ConvertToMatrix(largeImageData, LARGE_IMG_WIDTH, LARGE_IMG_HEIGHT));
	RefImage* refTemp = new RefImage(REF_IMG_WIDTH, REF_IMG_HEIGHT, ConvertToMatrix(refImageData, REF_IMG_WIDTH, REF_IMG_HEIGHT));

	std::chrono::system_clock::time_point start;
	start = std::chrono::system_clock::now();
	std::vector<MatchPos> listOMatches = Search(largeTemp, refTemp, matches);
	auto end = std::chrono::system_clock::now();

	for (auto match : listOMatches) {
		largeTemp->CreateBorder(match.x, match.y, REF_IMG_WIDTH, REF_IMG_HEIGHT, thickness, 0.0);
		std::cout << match.x << "," << match.y << std::endl;
	}
	std::chrono::duration<float, std::milli> span = end - start;
	span.count();
	std::cout << "It took: " << span.count() / 1000 << " seconds to find " << matches << "matches" << std::endl;
	iofiles.writePgm(OUTPUT_IMG_PATH, ConvertToFile(largeTemp->getMatrix()), LARGE_IMG_HEIGHT, LARGE_IMG_WIDTH, 255);
	//iofiles.writePgm(OUTPUT_IMG_PATH, ConvertToFile(refTemp->getMatrix()), REF_IMG_HEIGHT, REF_IMG_WIDTH, 255);

	delete largeTemp;
	delete refTemp;

}
