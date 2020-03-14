#include "Graphic.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

const int STANDART_WIDTH = 6000;
const int STANDART_HEIGHT = 4000;
const int SMALL_WIDTH = 3000;
const int SMALL_HEIGHT = 2000;

int main() {
	Data data;
	std::string file;
	std::string image;
	std::cout << "Write name of source file and image:" << std::endl;
	std::cin >> file >> image;
	std::ifstream input(file);

	try {
		if (!input.is_open()) {
			throw "ERROR: Could not open the file!";
		}
		if (!(image.substr(image.find('.') + 1) == "JPG")) {
			throw "ERROR: Wrong image format! Expected ***.JPG";
		}
		std::string data_string;
		std::getline(input, data_string);
		while (!input.eof() && data_string.find(image) == std::string::npos) {
			std::getline(input, data_string);
		}
		if (data_string.find(image) == std::string::npos) {
			throw "ERROR: No image with such name in source file!";
		}
		data.parse_data(data_string);
		input.close();

		Graphic graphic(image);
		if (graphic.getImage().cols < SMALL_WIDTH) {
			graphic.resize_resolution(SMALL_WIDTH, SMALL_HEIGHT);
		}
		else {
			graphic.resize_resolution(STANDART_WIDTH, STANDART_HEIGHT);
		}
		graphic.print(data);
		imwrite(image.substr(0, image.find('.')) + "_result.JPG", graphic.getImage());
	}
	catch (const char* message) {
		std::cerr << std::endl << message << std::endl << std::endl;
		system("pause");
		return -1;
	}
}
