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
	
	this->screen_width = horizontal;
	
	this->screen_height = vertical;
	
	this->thickness = int(STANDART_THICKNESS * (double(screen_width) / STANDART_WIDTH));
	
	this->font_scale = STANDART_FONT_SCALE * (double(screen_width) / STANDART_WIDTH);
	
	this->date_position = cv::Point2f(screen_width * DATE_POSITION_PERCENT.first / 100, 
										screen_height * DATE_POSITION_PERCENT.second / 100);
	
	this->distance_position = cv::Point2f(screen_width * DISTANCE_POSITION_PERCENT.first / 100,
											screen_height * DISTANCE_POSITION_PERCENT.second / 100);
	
	this->latitude_aim_position = cv::Point2f(screen_width * LATITUDE_AIM_POSITION_PERCENT.first / 100, 
												screen_height * LATITUDE_AIM_POSITION_PERCENT.second / 100);
	
	this->longitude_aim_position = cv::Point2f(screen_width * LONGITUDE_AIM_POSITION_PERCENT.first / 100, 
												screen_height * LONGITUDE_AIM_POSITION_PERCENT.second / 100);
	
	this->latitude_observer_position = cv::Point2f(screen_width * LATITUDE_OBSERVER_POSITION_PERCENT.first / 100,
													screen_height * LATITUDE_OBSERVER_POSITION_PERCENT.second / 100);
	
	this->longitude_observer_position = cv::Point2f(screen_width * LONGITUDE_OBSERVER_POSITION_PERCENT.first / 100, 
														screen_height * LONGITUDE_OBSERVER_POSITION_PERCENT.second / 100);
}

void Graphic::print(Data data) {

	print_text(data.date, this->date_position);
	
	print_text(data.distance, this->distance_position);
	
	print_text(data.latitude_aim, this->latitude_aim_position);
	
	print_text(data.longitude_aim, this->longitude_aim_position);
	
	print_text(data.latitude_observer, this->latitude_observer_position);
	
	print_text(data.longitude_observer, this->longitude_observer_position);

}

cv::Mat Graphic::getImage() {
	return this->image;
}


void Graphic::print_text(std::string text, cv::Point text_position) {

	cv::Size text_size = cv::getTextSize(text, font, font_scale, thickness, 0);
	
	cv::Point bottom_left = cv::Point2f(text_position.x, text_position.y);
	
	cv::Point top_right = cv::Point2f(text_position.x + text_size.width, text_position.y - text_size.height);
	
	cv::rectangle(image, bottom_left, top_right, RECTANGLE_COLOR, RECTANGLE_THICKNESS, LINE_TYPE, RECTANLGE_SHIFT); 
	
	cv::putText(image, text, text_position, font, font_scale, TEXT_COLOR, thickness, LINE_TYPE);
}