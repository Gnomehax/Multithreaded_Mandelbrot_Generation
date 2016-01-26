#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <thread>

double mapReal(int x, int imageWidth, double minReal, double maxReal);
double mapImaginary(int y, int imageHeight, double minImaginary, double maxImaginary);
int findMandelbrot(double cReal, double cImaginary, int max_iter);
void drawMandelBrot(std::vector<std::tuple<int, int, int>  > &pixels, int startRow, int endRow);

auto imageWidth = 512;
auto imageHeight = 512;
auto maxN = 255;
auto minReal = -1.5;
auto maxReal = 0.7;
auto minImaginary = -1.0;
auto maxImaginary = 1.0;

int main() {

	
	auto variance = 0;
	auto varianceSquared = 0;
	auto varianceSum = 0;
	auto standardDeviation = 0.0;
	std::vector<int> timeVector;
	std::vector<std::tuple<int, int, int>  > pixels;
	std::vector<std::tuple<int, int, int>  > pixels2;
	std::vector<std::tuple<int, int, int>  > pixels3;
	std::vector<std::tuple<int, int, int>  > pixels4;
	std::vector<std::tuple<int, int, int>  > pixels5;
	std::vector<std::tuple<int, int, int>  > pixels6;
	std::vector<std::tuple<int, int, int>  > pixels7;
	std::vector<std::tuple<int, int, int>  > pixels8;

	std::ofstream fout("output.ppm", std::ofstream::out);
	fout << "P3" << std::endl; // PPM file
	fout << imageWidth << " " << imageHeight << std::endl; //Image Dimensions
	fout << "256" << std::endl; // Max RGB pixel value

	std::cout << "Serial timing:" << std::endl;
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		std::thread t([&]() {drawMandelBrot(pixels, 0, imageHeight); });
		t.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	auto sum = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	auto average = sum / timeVector.size();

	for (auto n : timeVector) {
		variance = n - average;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "Serial timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		std::thread t([&]() {drawMandelBrot(pixels, 0, imageHeight); });
		t.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	auto sum10 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	auto average10 = sum10 / timeVector.size();

	for (auto n : timeVector) {
		variance = n - average10;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average10 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "2 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 2); });
		std::thread t2([&]() {drawMandelBrot(pixels2, (imageHeight / 2) + 1, imageHeight); });
		t1.join();
		t2.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}
	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	double sum2 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average2 = sum2 / timeVector.size();
	double speedUp2 = average / average2;
	double efficiency2 = speedUp2 / 2;

	for (auto n : timeVector) {
		variance = n - average2;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average2 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp2 << std::endl;
	std::cout << "Efficiency: " << efficiency2 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "3 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 3); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 3) + 1), (imageHeight / 3) * 2 ); });
		std::thread t3([&]() {drawMandelBrot(pixels3, (((imageHeight / 3) * 2) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}
	
	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());	
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());	
	double sum3 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average3 = sum3 / timeVector.size();
	double speedUp3 = average / average3;
	double efficiency3 = speedUp3 / 3;

	for (auto n : timeVector) {
		variance = n - average3;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average3 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp3 << std::endl;
	std::cout << "Efficiency: " << efficiency3 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "4 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		pixels4.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 4); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 4) + 1), imageHeight / 2); });
		std::thread t3([&]() {drawMandelBrot(pixels3, ((imageHeight / 2) + 1), (imageHeight / 4) * 3); });
		std::thread t4([&]() {drawMandelBrot(pixels4, (((imageHeight / 4) * 3) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());
	pixels.insert(pixels.end(), pixels4.begin(), pixels4.end());
	double sum4 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average4 = sum4 / timeVector.size();
	double speedUp4 = average / average4;
	double efficiency4 = speedUp4 / 4;

	for (auto n : timeVector) {
		variance = n - average4;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average4 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp4 << std::endl;
	std::cout << "Efficiency: " << efficiency4 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "5 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		pixels4.clear();
		pixels5.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 5); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 5) + 1), (imageHeight / 5) * 2); });
		std::thread t3([&]() {drawMandelBrot(pixels3, (((imageHeight / 5) * 2)+ 1), (imageHeight / 5) * 3); });
		std::thread t4([&]() {drawMandelBrot(pixels4, (((imageHeight / 5) * 3) + 1), (imageHeight / 5) * 4); });
		std::thread t5([&]() {drawMandelBrot(pixels5, (((imageHeight / 5) * 4) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());
	pixels.insert(pixels.end(), pixels4.begin(), pixels4.end());
	pixels.insert(pixels.end(), pixels5.begin(), pixels5.end());
	double sum5 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average5 = sum5 / timeVector.size();
	double speedUp5 = average / average5;
	double efficiency5 = speedUp5 / 5;

	for (auto n : timeVector) {
		variance = n - average5;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average5 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp5 << std::endl;
	std::cout << "Efficiency: " << efficiency5 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "6 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		pixels4.clear();
		pixels5.clear();
		pixels6.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 6); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 6) + 1), imageHeight / 3); });
		std::thread t3([&]() {drawMandelBrot(pixels3, ((imageHeight / 3) + 1), (imageHeight / 2)); });
		std::thread t4([&]() {drawMandelBrot(pixels4, ((imageHeight / 2) + 1), (imageHeight / 3) * 2); });
		std::thread t5([&]() {drawMandelBrot(pixels5, (((imageHeight / 3) * 2) + 1), (imageHeight / 6) * 5); });
		std::thread t6([&]() {drawMandelBrot(pixels6, (((imageHeight / 6) * 5) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());
	pixels.insert(pixels.end(), pixels4.begin(), pixels4.end());
	pixels.insert(pixels.end(), pixels5.begin(), pixels5.end());
	pixels.insert(pixels.end(), pixels6.begin(), pixels6.end());
	double sum6 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average6 = sum6 / timeVector.size();
	double speedUp6 = average / average6;
	double efficiency6 = speedUp6 / 6;

	for (auto n : timeVector) {
		variance = n - average6;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average6 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp6 << std::endl;
	std::cout << "Efficiency: " << efficiency6 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "7 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		pixels4.clear();
		pixels5.clear();
		pixels6.clear();
		pixels7.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 7); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 7) + 1), (imageHeight / 7) * 2); });
		std::thread t3([&]() {drawMandelBrot(pixels3, (((imageHeight / 7) * 2) + 1), (imageHeight / 7) * 3); });
		std::thread t4([&]() {drawMandelBrot(pixels4, (((imageHeight / 7) * 3) + 1), (imageHeight / 7) * 4); });
		std::thread t5([&]() {drawMandelBrot(pixels5, (((imageHeight / 7) * 4) + 1), (imageHeight / 7) * 5); });
		std::thread t6([&]() {drawMandelBrot(pixels6, (((imageHeight / 7) * 5) + 1), (imageHeight / 7) * 6); });
		std::thread t7([&]() {drawMandelBrot(pixels7, (((imageHeight / 7) * 6) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());
	pixels.insert(pixels.end(), pixels4.begin(), pixels4.end());
	pixels.insert(pixels.end(), pixels5.begin(), pixels5.end());
	pixels.insert(pixels.end(), pixels6.begin(), pixels6.end());
	pixels.insert(pixels.end(), pixels7.begin(), pixels7.end());
	double sum7 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average7 = sum7 / timeVector.size();
	double speedUp7 = average / average7;
	double efficiency7 = speedUp7 / 7;

	for (auto n : timeVector) {
		variance = n - average7;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average7 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp7 << std::endl;
	std::cout << "Efficiency: " << efficiency7 << std::endl;
	std::cout << std::endl;

	//reset variables for accurate standard deviation
	variance = 0;
	varianceSquared = 0;
	varianceSum = 0;
	standardDeviation = 0.0;

	std::cout << "8 Parallel Threads timing:" << std::endl;
	timeVector.clear();
	for (int x = 0; x < 5; x++) {
		auto startTime = std::chrono::steady_clock::now();
		pixels.clear();
		pixels2.clear();
		pixels3.clear();
		pixels4.clear();
		pixels5.clear();
		pixels6.clear();
		pixels7.clear();
		pixels8.clear();
		std::thread t1([&]() {drawMandelBrot(pixels, 0, imageHeight / 8); });
		std::thread t2([&]() {drawMandelBrot(pixels2, ((imageHeight / 8) + 1), imageHeight / 4); });
		std::thread t3([&]() {drawMandelBrot(pixels3, ((imageHeight / 4) + 1), (imageHeight / 8) * 3); });
		std::thread t4([&]() {drawMandelBrot(pixels4, (((imageHeight / 8) * 3) + 1), (imageHeight / 8) * 4); });
		std::thread t5([&]() {drawMandelBrot(pixels5, (((imageHeight / 8) * 4) + 1), (imageHeight / 8) * 5); });
		std::thread t6([&]() {drawMandelBrot(pixels6, (((imageHeight / 8) * 5) + 1), (imageHeight / 8) * 6); });
		std::thread t7([&]() {drawMandelBrot(pixels7, (((imageHeight / 8) * 6) + 1), (imageHeight / 8) * 7); });
		std::thread t8([&]() {drawMandelBrot(pixels8, (((imageHeight / 8) * 7) + 1), imageHeight); });
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();

		auto endTime = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << int(time.count()) << " ms" << std::endl;
		timeVector.push_back(int(time.count()));
	}

	pixels.insert(pixels.end(), pixels2.begin(), pixels2.end());
	pixels.insert(pixels.end(), pixels3.begin(), pixels3.end());
	pixels.insert(pixels.end(), pixels4.begin(), pixels4.end());
	pixels.insert(pixels.end(), pixels5.begin(), pixels5.end());
	pixels.insert(pixels.end(), pixels6.begin(), pixels6.end());
	pixels.insert(pixels.end(), pixels7.begin(), pixels7.end());
	pixels.insert(pixels.end(), pixels8.begin(), pixels8.end());
	double sum8 = std::accumulate(timeVector.begin(), timeVector.end(), 0);
	double average8 = sum8 / timeVector.size();
	double speedUp8 = average / average8;
	double efficiency8 = speedUp8 / 8;

	for (auto n : timeVector) {
		variance = n - average8;
		varianceSquared = variance * variance;
		varianceSum += varianceSquared;
	}

	standardDeviation = sqrt(varianceSum / timeVector.size());
	std::cout << "Average: " << average8 << " ms" << std::endl;
	std::cout << "Standard Deviation: " << standardDeviation << " ms" << std::endl;
	std::cout << "Speed Up: " << speedUp8 << std::endl;
	std::cout << "Efficiency: " << efficiency8 << std::endl;
	std::cout << std::endl;
	std::cout << "Please wait: Writing to file" << std::endl;
	
	for (auto n : pixels) {
		fout << std::get<0>(n) << " " << std::get<1>(n) << " " << std::get<2>(n) << " ";
	}
	fout.close();

	std::cout << "Finished writing to file!" << std::endl;
	return 0;
}

double mapReal(int x, int imageWidth, double minReal, double maxReal) {

	auto range = maxReal - minReal;
	return x * (range / imageWidth) + minReal;
}
double mapImaginary(int y, int imageHeight, double minImaginary, double maxImaginary) {
	
	auto range = maxImaginary - minImaginary;
	return y * (range / imageHeight) + minImaginary;
}
int findMandelbrot(double x0, double y0, int max_iter) {

	auto i = 0; //iteration start
	auto x = x0; //starting z real value
	auto y = y0; //starting z imaginary value
	auto x2 = x * x;
	auto y2 = y * y;

	while (x2 + y2 < 4.0) {
		if (++i == max_iter) break;
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}

	return i; // return iteration
}

void drawMandelBrot(std::vector<std::tuple<int, int, int>  > &total, int startRow, int endRow) {

	for (int y = startRow; y < endRow; y++) { //Each row
		for (int x = 0; x < imageWidth; x++) { //Each pixel in each row

			auto cReal = mapReal(x, imageWidth, minReal, maxReal);
			auto cImaginary = mapImaginary(y, imageHeight, minImaginary, maxImaginary);
			auto n = findMandelbrot(cReal, cImaginary, maxN);

			auto r = (n % 256);
			auto g = (n % 256);
			auto b = (n % 256);
			total.push_back(std::tuple<int, int, int>(r, g, b));
		}
	}
}