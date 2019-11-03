#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{	
	try {


		String imageName("billy.png"); // by default
		if (argc > 1)
		{
			imageName = argv[1];
		}
		cout << imageName << std::endl;
		Mat image;
		image = imread(imageName, IMREAD_COLOR); // Read the file
		if (image.empty())                      // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}
		cvtColor(image, image, COLOR_BGR2GRAY);
		int width = image.cols;
		int height = image.rows;
		double val;
		double error;
		int pointer = 0;
		double* passahead = new double[width + 1];
		for (int z = 0; z < (width + 1); z++) {
			passahead[z] = 0;
		}
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < (width-1); x++) {
				error = passahead[pointer] + image.at<uint8_t>(y, x);
				if (error > 127) {
					val = 255;
				}
				else {
					val = 0;
				}
				error -= val;
				image.at<uint8_t>(y, x) = val;
				pointer = (pointer + 1) % (width + 1);
				passahead[pointer] += error * 7 / 16;
				passahead[(pointer + width) % (width + 1)] = error * 1 / 16;
				passahead[(pointer + width - 2) % (width + 1)] += error * 3 / 16;
				passahead[(pointer + width - 1) % (width + 1)] += error * 5 / 16;
			}
			error = passahead[pointer] + image.at<uint8_t>(y, width-1);
			if (error > 127) {
				val = 255;
			}
			else {
				val = 0;
			}
			error -= val;
			image.at<uint8_t>(y, width-1) = val;
			pointer = (pointer + 1) % (width + 1);
			passahead[(pointer + width - 2) % (width + 1)] += error * 3 / 16;
			passahead[(pointer + width - 1) % (width + 1)] += error * 5 / 16;
		}
		delete[] passahead;
		//namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
		//imshow("Display window", image);                // Show our image inside it.
		//waitKey(0); // Wait for a keystroke in the window
		imwrite(imageName+"dith.png", image);
		return 0;
	}
	catch (cv::Exception & e)
	{
		cerr << e.msg << endl; // output exception message
	}
}