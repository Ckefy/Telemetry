#pragma once
#include "Data.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class Graphic {
public:

	Graphic(std::string source);

	void resize_resolution(int horizontal, int vertical);

	void print(Data data);

	cv::Mat getImage();

	const int STANDART_WIDTH = 6000;

	const int STANDART_HEIGHT = 4000;
	
	const int SMALL_WIDTH = 3000;
	
	const int SMALL_HEIGHT = 2000;

private:

	const int STANDART_THICKNESS = 10;

	const double STANDART_FONT_SCALE = 3.5;

	const std::pair <double, double> DATE_POSITION_PERCENT = std::make_pair(3, 94);

	const std::pair <double, double> DISTANCE_POSITION_PERCENT = std::make_pair(90, 5);

	const std::pair <double, double> LATITUDE_AIM_POSITION_PERCENT = std::make_pair(72, 90);

	const std::pair <double, double> LONGITUDE_AIM_POSITION_PERCENT = std::make_pair(85, 90);

	const std::pair <double, double> LATITUDE_OBSERVER_POSITION_PERCENT = std::make_pair(72, 95);

	const std::pair <double, double> LONGITUDE_OBSERVER_POSITION_PERCENT = std::make_pair(85, 95);

	cv::Mat image;

	void print_text(std::string text, cv::Point text_position);

	int screen_width;

	int screen_height;
	
	int font = cv::FONT_HERSHEY_SIMPLEX;
	
	double font_scale;
	
	cv::Scalar WHITE = cv::Scalar(255, 255, 255);

	cv::Scalar BLACK = cv::Scalar(0, 0, 0);

	cv::Scalar TEXT_COLOR = WHITE;

	cv::Scalar RECTANGLE_COLOR = BLACK;
	
	int thickness;
	
	const int LINE_TYPE = 8;

	const int RECTANLGE_SHIFT = 0;

	const int RECTANGLE_THICKNESS = -1; //-1 to fill rectangle
	
	cv::Point date_position;
	
	cv::Point distance_position;
	
	cv::Point latitude_aim_position;
	
	cv::Point longitude_aim_position;
	
	cv::Point latitude_observer_position;
	
	cv::Point longitude_observer_position;

};