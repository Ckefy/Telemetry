#pragma once
#include <iostream>

class Data {
public:
	
	enum Measurements;

	void parse_data(const std::string& data);

	std::string date;

	std::string name;
	
	std::string azimuth;
	
	std::string pitch;
	
	std::string angle;
	
	std::string latitude_observer;
	
	std::string longitude_observer;
	
	std::string latitude_aim;
	
	std::string longitude_aim;
	
	std::string distance;
	
	std::string height_GPS;

	const int NUMBER_OF_DATA = 12;

	std::string parse_date_format(std::string date);

	std::string parse_coordinates(std::string coord);
};