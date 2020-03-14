#include "Data.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

void Data::parse_data(const std::string& data) {
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
	if (formated_date[0].length() > 2) {
		return formated_date[2] + "." + formated_date[1] + "." + formated_date[0];
	}
	else {
		return formated_date[0] + "." + formated_date[1] + "." + formated_date[2];
	}
}

std::string Data::parse_coordinates(std::string coord) {
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
