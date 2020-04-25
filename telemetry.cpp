#include "Graphic.h"
#include "Tests.h"

#define RELEASE

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <windows.h>

const int MAX_PATH_LENGTH = 1000;	

std::ifstream input;


void map_image(Data& data, std::string image, std::string pathStr) {
	std::string data_string;
	std::getline(input, data_string);

	while (!input.eof() && data_string.find(image) == std::string::npos) {
		std::getline(input, data_string);
	}

	if (data_string.find(image) == std::string::npos) {
		input.clear();
		input.seekg(0, std::ios::beg);
		return;
	}

	input.clear();
	input.seekg(0, std::ios::beg);
	std::cout << "Current working on " << image << " image" << std::endl;
	data.parse_data(data_string);

	Graphic graphic(pathStr + "/" + image);
	
	if (graphic.getImage().cols < graphic.SMALL_WIDTH) {
		graphic.resize_resolution(graphic.SMALL_WIDTH, graphic.SMALL_HEIGHT);
	} else {
		graphic.resize_resolution(graphic.STANDART_WIDTH, graphic.STANDART_HEIGHT);
	}

	graphic.print(data);
	imwrite(pathStr + "/" + image.substr(0, image.find('.')) + "_result.JPG", graphic.getImage());
}

int main() {

#ifdef TEST
	Test test;
	test.allTest();
#endif // TEST
	
#ifdef RELEASE

	std::string file;

	std::string pathStr;

	char path[MAX_PATH_LENGTH];

	std::cout << "Write name of source file and directory with images:" << std::endl;
	std::cin >> file >> pathStr;
	strcpy_s(path, (pathStr + "/*.JPG").c_str());
	std::cout << "PATH " << path << std::endl;

	WIN32_FIND_DATAA FindFileData;
	HANDLE handle;
	handle = FindFirstFileA(path, &FindFileData);

	if (handle == INVALID_HANDLE_VALUE) {
		std::cout << "ERROR: Can`t find directory or it is empty!" << std::endl;
		system("pause");
		return -1;
	}

	std::vector <std::string> images;
	images.push_back(FindFileData.cFileName);
	while (FindNextFileA(handle, &FindFileData)) {
		images.push_back(FindFileData.cFileName);
	}

	input.open(file);
	Data data;

	try {
		if (!input.is_open()) {
			throw "ERROR: Could not open the source file!";
		}

		for (std::string image : images) {
			try {
				map_image(data, image, pathStr);
			} catch (const char* message) {
				std::cerr << std::endl << message << std::endl << std::endl;
			}
		}

		input.close();
	}
	catch (const char* message) {
		std::cerr << std::endl << message << std::endl << std::endl;
		system("pause");
		return -1;
	}
	system("pause");
#endif // RELEASE
}
