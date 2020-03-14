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

private:

	cv::Mat image;

	void print_text(std::string text, cv::Point text_position);

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