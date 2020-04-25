#include "Tests.h"

	void Test::allTest() {
		testParseCoordinates();
		std::cout << std::endl;

		testParseDateFormat();
		std::cout << std::endl;

		testParseData();
		std::cout << std::endl;
	}

	void Test::testParseData() {
		int rightTests = 4;
		int wrongTests = 5;
		std::cout << "############################" << std::endl;
		std::cout << "#### TEST DATA PARSING #####" << std::endl;
		std::cout << "############################" << std::endl << std::endl;
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
			std::cout << test << std::endl;
			std::cout << "******************" << std::endl << std::endl;
			try {
				Data data_test;
				data_test.parse_data(test);
				print_resultParseData(data_test);
			} catch (const char* message) {
				if (index <= rightTests) {
					counter = 10000;
				}
				if (index > rightTests) {
					counter++;
				}
				std::cerr << message << std::endl << std::endl;
			}
		}
		if (counter == wrongTests) {
			std::cout << "ALL TESTS PASSED!" << std::endl << std::endl;
		} else {
			std::cout << "FAILED!" << std::endl << std::endl;
		}
		system("pause");
	}

	void Test::print_resultParseData(Data data) {
		std::cout << "DATE: " << data.date << ' ' << std::endl;
		std::cout << "NAME: " << data.name << ' ' << std::endl;
		std::cout << "AZIMUTH: " << data.azimuth << ' ' << std::endl;
		std::cout << "PITCH: " << data.pitch << ' ' << std::endl;
		std::cout << "ANGLE: " << data.angle << ' ' << std::endl;
		std::cout << "LATITUDE OBSERVER: " << data.latitude_observer << ' ' << std::endl;
		std::cout << "LONGITUDE OBSERVER: " << data.longitude_observer << ' ' << std::endl;
		std::cout << "LATITUDE AIM: " << data.latitude_aim << ' ' << std::endl;
		std::cout << "LONGITUDE AIM: " << data.longitude_aim << ' ' << std::endl;
		std::cout << "DISTANCE: " << data.distance << ' ' << std::endl;
		std::cout << "HEIGHT OF GPS: " << data.height_GPS << ' ' << std::endl;
		std::cout << std::endl << std::endl;
	}

	void Test::testParseCoordinates() {
		int rightTests = 4;
		int wrongTests = 5;
		std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
		std::cout << "@@@@ TEST COORDINATES @@@@@@" << std::endl;
		std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl << std::endl;
		std::string test1 = "70.33333";
		std::string test2 = "150.715";
		std::string test3 = "-10.535";
		std::string test4 = "-100";
		//incorrect tests
		std::string testWrong1 = "-1000";
		std::string testWrong2 = "186.3333";
		std::string testWrong3 = "1860.327";
		std::string testWrong4 = "-22822.666";
		std::string testWrong5 = "1500";
		std::vector<std::string> tests = { test1, test2, test3, test4, testWrong1, testWrong2, testWrong3, testWrong4, testWrong5};
		int index = 0;
		int counter = 0;
		for (std::string test : tests) {
			index++;
			std::cout << "******************" << std::endl;
			std::cout << "***** TEST " + std::to_string(index) + " *****" << std::endl;
			std::cout << test << std::endl;
			std::cout << "******************" << std::endl << std::endl;
			try {
				Data data_test;
				std::cout << data_test.parse_coordinates(test) << std::endl;
				std::cout << std::endl;
			}
			catch (const char* message) {
				if (index <= rightTests) {
					counter = 10000;
				}
				if (index > rightTests) {
					counter++;
				}
				std::cerr << message << std::endl << std::endl;
			}
		}
		if (counter == wrongTests) {
			std::cout << "ALL TESTS PASSED!" << std::endl << std::endl;
		}
		else {
			std::cout << "FAILED!" << std::endl << std::endl;
		}
		system("pause");
	}

	void Test::testParseDateFormat() {
		int rightTests = 4;
		int wrongTests = 5;
		std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
		std::cout << "%%%% TEST DATE FORMAT PARSING %%%%%%" << std::endl;
		std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl << std::endl;
		std::string test1 = "11.10.2020";
		std::string test2 = "2020-09-14";
		std::string test3 = "24-05-2000";
		std::string test4 = "2000.07.10";
		//incorrect tests
		std::string testWrong1 = "66.11.6666";
		std::string testWrong2 = "11.66.2020";
		std::string testWrong3 = "2066-20-20";
		std::string testWrong4 = "39-12-6666";
		std::string testWrong5 = "66-66-6666";
		std::vector<std::string> tests = { test1, test2, test3, test4, testWrong1, testWrong2, testWrong3, testWrong4, testWrong5 };
		int index = 0;
		int counter = 0;
		for (std::string test : tests) {
			index++;
			std::cout << "******************" << std::endl;
			std::cout << "***** TEST " + std::to_string(index) + " *****" << std::endl;
			std::cout << test << std::endl;
			std::cout << "******************" << std::endl << std::endl;
			try {
				Data data_test;
				std::cout << data_test.parse_date_format(test) << std::endl;
				std::cout << std::endl;
			}
			catch (const char* message) {
				if (index <= rightTests) {
					counter = 10000;
				}
				if (index > rightTests) {
					counter++;
				}
				std::cerr << message << std::endl << std::endl;
			}
		}
		if (counter == wrongTests) {
			std::cout << "ALL TESTS PASSED!" << std::endl << std::endl;
		}
		else {
			std::cout << "FAILED!" << std::endl << std::endl;
		}
		system("pause");
	}