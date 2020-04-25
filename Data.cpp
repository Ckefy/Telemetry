#include "Data.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

enum Data::Measurements {

	RIGHT_ANGLE = 90,

	STRAIGHT_ANGLE = 180,
	
	MONTHES = 12,			//number of monthes in 1 year
	
	DAYS = 31,				//number of days in 1 month (upper bound)
	
	SECONDS = 60			//number of seconds in 1 minute
};

void Data::parse_data(const std::string& data) {

	enum Parsing_indexes {
		date_index = 0,
		
		time_index = 1,
		
		name_index = 2,
		
		azimuth_index = 3,
		
		pitch_index = 4,
		
		angle_index = 5,
		
		latitude_obs_index = 6,
		
		longitude_obs_index = 7,
		
		latitude_aim_index = 8,
		
		longitude_aim_index = 9,
		
		distance_index = 10,

		height_index = 11,
	};

	std::vector<std::string> parsed;
	std::istringstream iss(data);
	
	for (std::string s; iss >> s;) {
		std::replace(s.begin(), s.end(), ',', '.');
		parsed.push_back(s);
	}
	
	if (parsed.size() < NUMBER_OF_DATA) {
		throw "ERROR: There are less information than expected!\nExpected format: \
				\nDate\nName\nAzimuth\nPitch\nAngle\nLatitude of observer\nLongitude of observer \
				\nLatitude of aim\nLongitude of aim\nDistance\nHeight of GPS";
	}

	this -> date = parse_date_format(parsed[date_index]) + " " + parsed[time_index];
	
	this -> name = parsed[name_index];
	
	this -> azimuth = parsed[azimuth_index];
	
	this -> pitch = parsed[pitch_index];
	
	this -> angle = parsed[angle_index];

	if (std::abs(stod(parsed[latitude_obs_index])) <= RIGHT_ANGLE) {
		this -> latitude_observer = parse_coordinates(parsed[6]);
	} else {
		throw "ERROR: Latitude of observer can`t be more than 90 degrees!";
	}

	if (std::abs(stod(parsed[longitude_obs_index])) <= STRAIGHT_ANGLE) {
		this -> longitude_observer = parse_coordinates(parsed[7]);
	} else {
		throw "ERROR: Longitude of observer can`t be more than 180 degrees!";
	}

	if (std::abs(stod(parsed[latitude_aim_index])) <= RIGHT_ANGLE) {
		this -> latitude_aim = parse_coordinates(parsed[8]);
	} else {
		throw "ERROR: Latitude of aim can`t be more than 90 degrees!";
	}

	if (std::abs(stod(parsed[longitude_aim_index])) <= STRAIGHT_ANGLE) {
		this -> longitude_aim = parse_coordinates(parsed[9]);
	} else {
		throw "ERROR: Longitude of aim can`t be more than 180 degrees!";
	}

	this -> distance = parsed[distance_index] + "m";
	
	this -> height_GPS = parsed[height_index];
}

std::string Data::parse_date_format(std::string date) {
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
	if (stoi(formated_date[1]) > MONTHES) {
		throw "ERROR: There are only 12 months in the year";
	}
	
	if (formated_date[0].length() > 2) {
		if (stoi(formated_date[2]) > DAYS) {
			throw "ERROR: There are maximum 31 days in the month";
		}
		return formated_date[2] + "." + formated_date[1] + "." + formated_date[0];
	} else {
		if (stoi(formated_date[0]) > DAYS) {
			throw "ERROR: There are maximum 31 days in the month";
		}
		return formated_date[0] + "." + formated_date[1] + "." + formated_date[2];
	}
}

std::string Data::parse_coordinates(std::string coord) {
	if (std::abs(stod(coord)) > STRAIGHT_ANGLE) {
		throw "ERROR: Wrong coordinates format! Must be less than 180 degrees";
	}

	bool minus = coord[0] == '-' ? true : false;
	if (minus) {
		coord = coord.substr(1);
	}

	if (coord.find('.') == std::string::npos) {
		return coord + ".00.00";
	}

	int degree = stoi(coord.substr(0, coord.find('.')));
	
	double mod = stod("0." + coord.substr(coord.find('.') + 1));

	std::string minutes = std::to_string(mod * SECONDS);
	
	double seconds = stod("0." + minutes.substr(minutes.find('.') + 1)) * SECONDS;
	
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
