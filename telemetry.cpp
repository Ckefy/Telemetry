#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class Data {
public:

	void parse_data(const std::string& data) {
		std::vector<std::string> parsed;
		std::istringstream iss(data);
		for (std::string s; iss >> s;) {
			std::replace(s.begin(), s.end(), ',', '.');
			parsed.push_back(s);
		}
		if (parsed.size() < 12) {
			throw "ERROR: There are less information than expected!\nExpected format: \
					\nDate\nName\nAzimuth\nTangage\nAngle\nLatitude of observer\nLongitude of observer \
					\nLatitude of aim\nLongitude of aim\nDistance\nHeight of GPS";
		}
		this->date = parse_date_format(parsed[0]) + " " + parsed[1];
		this->name = parsed[2];
		this->azimuth = parsed[3];
		this->tangage = parsed[4];
		this->angle = parsed[5];
		this->latitude_observer = parse_coordinates(parsed[6]);
		this->longitude_observer = parse_coordinates(parsed[7]);
		this->latitude_aim = parse_coordinates(parsed[8]);
		this->longitude_aim = parse_coordinates(parsed[9]);
		this->distance = parsed[10] + "m";
		this->height_GPS = parsed[11];
	}

	std::string date;
	std::string name;
	std::string azimuth;
	std::string tangage;
	std::string angle;
	std::string latitude_observer;
	std::string longitude_observer;
	std::string latitude_aim;
	std::string longitude_aim;
	std::string distance;
	std::string height_GPS;

private:

	std::string parse_date_format(std::string date) {
		std::vector <std::string> formated_date;
		int index = 0;
		std::string temp = "";
		while (index < date.length()) {
			if (date[index] == '.' || date[index] == '-') {
				formated_date.push_back(temp);
				temp = "";
				index++;
				continue;
			}
			temp += date[index];
			index++;
		}
		formated_date.push_back(temp);
		if (formated_date[0].length() > 2) {
			return formated_date[2] + "." + formated_date[1] + "." + formated_date[0];
		} else {
			return formated_date[0] + "." + formated_date[1] + "." + formated_date[2];
		}
	}

	std::string parse_coordinates(std::string coord) {
		bool minus = coord[0] == '-' ? true : false;
		int degree = stoi(coord.substr(0, coord.find('.')));
		double mod = stod("0." + coord.substr(coord.find('.') + 1));
		std::string minutes = std::to_string(mod * 60);
		double seconds = stod("0." + minutes.substr(minutes.find('.') + 1)) * 60;
		int roundSeconds = int(seconds);
		if (seconds - roundSeconds > 0.5) {
			roundSeconds++;
		}
		minutes = minutes.substr(0, minutes.find('.'));
		if (minutes.length() < 2) {
			minutes = "0" + minutes;
		}
		return (minus ? "-" : "+") + std::to_string(degree) + "." + minutes + "." + std::to_string(roundSeconds);
	}
};

class Graphic {
public:
	
	Graphic(std::string source) {
		this->image = cv::imread(source).clone();
	}

	void resize_resolution(int horizontal, int vertical) {
		cv::Size size(horizontal, vertical);
		cv::resize(image, image, size);
		this->SCREEN_WIDTH = horizontal;
		this->SCREEN_HEIGHT = vertical;
		this->THICKNESS = int(10 * (double(SCREEN_WIDTH) / 6000));
		this->FONT_SCALE = 3.5 * (double (SCREEN_WIDTH) / 6000);
		this->DATE_POSITION = cv::Point2f(SCREEN_WIDTH * 0.03, SCREEN_HEIGHT * 0.94);
		this->DISTANCE_POSITION = cv::Point2f(SCREEN_WIDTH * 0.9, SCREEN_HEIGHT * 0.05);
		this->LATITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.90);
		this->LONGITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.90);
		this->LATITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.95);
		this->LONGITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.95);
	}

	void print(Data data) {
		print_text(data.date, this->DATE_POSITION);
		print_text(data.distance, this->DISTANCE_POSITION);
		print_text(data.latitude_aim, this->LATITUDE_AIM_POSITION);
		print_text(data.longitude_aim, this->LONGITUDE_AIM_POSITION);
		print_text(data.latitude_observer, this->LATITUDE_OBSERVER_POSITION);
		print_text(data.longitude_observer, this->LONGITUDE_OBSERVER_POSITION);

	}

	cv::Mat getImage() {
		return this->image;
	}

private:

	cv::Mat image;

	void print_text(std::string text, cv::Point text_position) {
		cv::Size text_size = cv::getTextSize(text, FONT, FONT_SCALE, THICKNESS, 0);
		cv::Point bottom_left = cv::Point2f(text_position.x, text_position.y);
		cv::Point top_right = cv::Point2f(text_position.x + text_size.width, text_position.y - text_size.height);
		cv::rectangle(image, bottom_left, top_right, cv::Scalar(0, 0, 0), -1, 8, 0); //-1 to fill rectangle
		cv::putText(image, text, text_position, FONT, FONT_SCALE, TEXT_COLOR, THICKNESS, LINE_TYPE);
	}

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int FONT = cv::FONT_HERSHEY_SIMPLEX;
	double FONT_SCALE;
	cv::Scalar TEXT_COLOR = cv::Scalar(255, 255, 255);
	int THICKNESS;
	int LINE_TYPE = 8;
	cv::Point DATE_POSITION;
	cv::Point DISTANCE_POSITION;
	cv::Point LATITUDE_AIM_POSITION;
	cv::Point LONGITUDE_AIM_POSITION;
	cv::Point LATITUDE_OBSERVER_POSITION;
	cv::Point LONGITUDE_OBSERVER_POSITION;

};

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
	} catch (const char* message) {
		std::cerr << std::endl << message << std::endl << std::endl;
		system("pause");
		return -1;
	}

	Graphic graphic(image);
	if (graphic.getImage().cols < 3000) {
		graphic.resize_resolution(3000, 2000);
	} else {
		graphic.resize_resolution(6000, 4000);
	}
	graphic.print(data);	
	imwrite(image.substr(0, image.find('.')) + "_result.JPG", graphic.getImage());
}
