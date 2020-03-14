#pragma once
#include <iostream>

class Data {
public:
	
	void parse_data(const std::string& data);

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

	std::string parse_date_format(std::string date);

	std::string parse_coordinates(std::string coord);
};