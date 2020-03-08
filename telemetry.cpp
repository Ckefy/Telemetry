#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Data {
public:

    void parseData(const std::string& data) {
        std::vector<std::string> parsed;
        std::istringstream iss(data);
        for (std::string s; iss >> s;) {
            parsed.push_back(s);
        }
        this->date = parsed[0];
        this->time = parsed[1];
        this->name = parsed[2];
        this->azimuth = parsed[3];
        this->tangage = parsed[4];
        this->angle = parsed[5];
        this->latitude_observer = parsed[6];
        this->longitude_observer = parsed[7];
        this->latitude_aim = parsed[8];
        this->longitude_aim = parsed[9];
        this->distance = parsed[10];
        this->height_GPS = parsed[11];
    }

private:
    std::string date;
    std::string time;
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
};

int main() {
    Data data;
    std::string file;
    std::string image;
    std::cin >> file >> image;
    std::ifstream input(file);
    std::string data_string;
    std::getline(input, data_string);
    while (data_string.find(image) == std::string::npos) {
        std::getline(input, data_string);
    }
    data.parseData(data_string);
    input.close();
}
