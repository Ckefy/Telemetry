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
	this->THICKNESS = int(STANDART_THICKNESS * (double(SCREEN_WIDTH) / STANDART_WIDTH));
	this->FONT_SCALE = STANDART_FONT_SCALE * (double(SCREEN_WIDTH) / STANDART_WIDTH);
	this->DATE_POSITION = cv::Point2f(SCREEN_WIDTH * DATE_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * DATE_POSITION_PERCENT.second / 100);
	this->DISTANCE_POSITION = cv::Point2f(SCREEN_WIDTH * DISTANCE_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * DISTANCE_POSITION_PERCENT.second / 100);
	this->LATITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * LATITUDE_AIM_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * LATITUDE_AIM_POSITION_PERCENT.second / 100);
	this->LONGITUDE_AIM_POSITION = cv::Point2f(SCREEN_WIDTH * LONGITUDE_AIM_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * LONGITUDE_AIM_POSITION_PERCENT.second / 100);
	this->LATITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * LATITUDE_OBSERVER_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * LATITUDE_OBSERVER_POSITION_PERCENT.second / 100);
	this->LONGITUDE_OBSERVER_POSITION = cv::Point2f(SCREEN_WIDTH * LONGITUDE_OBSERVER_POSITION_PERCENT.first / 100, SCREEN_HEIGHT * LONGITUDE_OBSERVER_POSITION_PERCENT.second / 100);
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
	cv::rectangle(image, bottom_left, top_right, RECTANGLE_COLOR, RECTANGLE_THICKNESS, LINE_TYPE, RECTANLGE_SHIFT); 
	cv::putText(image, text, text_position, FONT, FONT_SCALE, TEXT_COLOR, THICKNESS, LINE_TYPE);
}
