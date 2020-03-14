#include "Graphic.h"
#include <iostream>

Graphic::Graphic(std::string source) {
	this->image = cv::imread(source).clone();
	if (image.empty()) {
		throw "ERROR: No image with such name in direction!";
	}
}

void Graphic::resize_resolution(int horizontal, int vertical) {
	cv::Size size(horizontal, vertical);
	cv::resize(image, image, size);
	this->SCREEN_WIDTH = horizontal;
	this->SCREEN_HEIGHT = vertical;
	this->THICKNESS = int(10 * (double(SCREEN_WIDTH) / 6000));
	this->FONT_SCALE = 3.5 * (double(SCREEN_WIDTH) / 6000);
	this->DATE_POSITION = cv::Point2f(SCREEN_WIDTH * 0.03, SCREEN_HEIGHT * 0.94);
	this->DISTANCE_POSITION = cv::Point2f(SCREEN_WIDTH * 0.9, SCREEN_HEIGHT * 0.05);
	this->LATITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.90);
	this->LONGITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.90);
	this->LATITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * 0.72, SCREEN_HEIGHT * 0.95);
	this->LONGITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * 0.85, SCREEN_HEIGHT * 0.95);
}

void Graphic::print(Data data) {
	print_text(data.date, this->DATE_POSITION);
	print_text(data.distance, this->DISTANCE_POSITION);
	print_text(data.latitude_aim, this->LATITUDE_AIM_POSITION);
	print_text(data.longitude_aim, this->LONGITUDE_AIM_POSITION);
	print_text(data.latitude_observer, this->LATITUDE_OBSERVER_POSITION);
	print_text(data.longitude_observer, this->LONGITUDE_OBSERVER_POSITION);

}

cv::Mat Graphic::getImage() {
	return this->image;
}


void Graphic::print_text(std::string text, cv::Point text_position) {
	cv::Size text_size = cv::getTextSize(text, FONT, FONT_SCALE, THICKNESS, 0);
	cv::Point bottom_left = cv::Point2f(text_position.x, text_position.y);
	cv::Point top_right = cv::Point2f(text_position.x + text_size.width, text_position.y - text_size.height);
	cv::rectangle(image, bottom_left, top_right, cv::Scalar(0, 0, 0), -1, 8, 0); //-1 to fill rectangle
	cv::putText(image, text, text_position, FONT, FONT_SCALE, TEXT_COLOR, THICKNESS, LINE_TYPE);
}