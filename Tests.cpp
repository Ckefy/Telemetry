#include "Tests.h"

	void Test::test() {
		std::string test1 = "21.09.2015 16:16 SOMETHING.JPG 0 15 33 90 70,3333 21 15 150 55";
		std::string test2 = "2015-09-21 16:16 ogogo.JPG 0 15 33 -90 +70,3333 21 15 150 55";
		std::string test3 = "21-09-2015 16:16 RANDOM_TEST.JPG 0 15 33 +90 -70,3333 -21 -15 150 55";
		std::string test4 = "2015.09.21 16:16 special.JPG 0 15 33 90 +70,3333 21 15 150 55";
		//incorrect tests
		std::string testLongitude = "21.09.2015 16:16 program.JPG 0 15 33 -91 70,3333 21 15 150 55";
		std::string testLatitude = "21.09.2015 16:16 SOMETHING.JPG 0 15 33 90 186,3333 21 15 150 55";
		std::string testMonth = "21.15.2015 16:16 SOMETHING.JPG 0 15 33 90 70,3333 21 15 150 55";
		std::string testDays = "66.11.2015 16:16 SOMETHING.JPG 0 15 33 90 70,3333 21 15 150 55";
		std::string testLessInform = "10.15.2015 16:16 SOMETHING.JPG 0 15 33";
		std::vector<std::string> tests = { test1, test2, test3, test4, testLongitude, testLatitude, testMonth, testDays, testLessInform };
		int index = 0;
		int counter = 0;
		for (std::string test : tests) {
			index++;
			std::cout << "******************" << std::endl;
			std::cout << "***** TEST " + std::to_string(index) + " *****" << std::endl;
			std::cout << "******************" << std::endl << std::endl;
			try {
				Data data_test;
				data_test.parse_data(test);
				print_result(data_test);
			} catch (const char* message) {
				if (index > 4) {
					counter++;
				}
				std::cerr << message << std::endl << std::endl;
			}
		}
		if (counter == 5) {
			std::cout << "ALL TESTS PASSED!" << std::endl << std::endl;
		} else {
			std::cout << "FAILED!" << std::endl << std::endl;
		}
		system("pause");
	}

	void Test::print_result(Data data) {
		std::cout << "DATE: " << data.date << ' ' << std::endl;
		std::cout << "NAME: " << data.name << ' ' << std::endl;
		std::cout << "AZIMUTH: " << data.azimuth << ' ' << std::endl;
		std::cout << "TANGAGE: " << data.tangage << ' ' << std::endl;
		std::cout << "ANGLE: " << data.angle << ' ' << std::endl;
		std::cout << "LATITUDE OBSERVER: " << data.latitude_observer << ' ' << std::endl;
		std::cout << "LONGITUDE OBSERVER: " << data.longitude_observer << ' ' << std::endl;
		std::cout << "LATITUDE AIM: " << data.latitude_aim << ' ' << std::endl;
		std::cout << "LONGITUDE AIM: " << data.longitude_aim << ' ' << std::endl;
		std::cout << "DISTANCE: " << data.distance << ' ' << std::endl;
		std::cout << "HEIGHT OF GPS: " << data.height_GPS << ' ' << std::endl;
		std::cout << std::endl << std::endl;
	}