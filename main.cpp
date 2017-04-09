/**
CS440 Programming Assignment 1:COMPUTER VISION

REBECCA WOLF
NIKITA GAWANDE
TANATSIGWA HUNGWE


Using Skeleton Code from:
CS440_Lab3.cpp
@author: Ajjen Joshi
@version: 1.0 9/17/2014
*/

#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

//Global variables
int thresh = 128;
int max_thresh = 255;
RNG rng(12345);


/**
Function that returns the maximum of 3 integers
@param a first integer
@param b second integer
@param c third integer
*/
int myMax(int a, int b, int c);

/**
Function that returns the minimum of 3 integers
@param a first integer
@param b second integer
@param c third integer
*/
int myMin(int a, int b, int c);

/**
Function that detects whether a pixel belongs to the skin based on RGB values
@param src The source color image
@param dst The destination grayscale image where skin pixels are colored white and the rest are colored black
*/
void mySkinDetect(Mat& src, Mat& dst);

// Function that returns the index of the max contour in the contours vector
int findmaxcontour(vector<vector<Point>> contours);



// main function
int main()
{

	//-------------------------------------------------------------- TEMPLATE IMAGE (2): OPEN HAND--------------------------------------------------------------------//


	Mat src; Mat src_gray; Mat blur_gray;
	// Load source image and convert it to gray
	src = imread("hand.jpg", 1);


	// Convert image to gray
	// Documentation for cvtColor: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
	cvtColor(src, src_gray, CV_BGR2GRAY);


	// Blur the image
	// Documentation for blur: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=blur#blur
	blur(src_gray, blur_gray, Size(3, 3));


	// Convert into binary image using thresholding
	// Documentation for threshold: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html?highlight=threshold#threshold
	// Example of thresholding: http://docs.opencv.org/doc/tutorials/imgproc/threshold/threshold.html
	Mat thres_output;
	threshold(blur_gray, thres_output, thresh, max_thresh, 0);



	//  FIND CONTOURS
	vector<vector<Point>> contours2;
	vector<Vec4i> hierarchy2;
	// Documentation for finding contours: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=findcontours#findcontours
	findContours(thres_output, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Find largest contour
	int maxind2 = findmaxcontour(contours2);


	// FIND CONVEX HULL OF TEMP
	vector<vector<Point> >hull2(contours2.size());

	//Find convex hull object for each contour
	for (int i = 0; i < contours2.size(); i++) {
		convexHull(Mat(contours2[i]), hull2[i], false);
	}

	Mat drawing2 = Mat::zeros(thres_output.size(), CV_8UC3);

	//only display the convex hull of largest contour
	Scalar color2 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing2, contours2, maxind2, color2, 1, 8, vector<Vec4i>(), 0, Point());
	drawContours(drawing2, hull2, maxind2, color2, 1, 8, vector<Vec4i>(), 0, Point());



	// now draw convex hull in window
	namedWindow("Temp Hull: Open Hand", CV_WINDOW_AUTOSIZE);
	imshow("Temp Hull: Open Hand", drawing2);



	//-------------------------------------------------------------- TEMPLATE IMAGE (3): VULCAN--------------------------------------------------------------------//


	Mat src3; Mat src_gray3; Mat blur_gray3;
	// Load source image and convert it to gray
	src3 = imread("vulcan.jpg", 1);



	// Convert image to gray
	// Documentation for cvtColor: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
	cvtColor(src3, src_gray3, CV_BGR2GRAY);


	// Blur the image
	// Documentation for blur: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=blur#blur
	blur(src_gray3, blur_gray3, Size(3, 3));


	// Convert into binary image using thresholding
	// Documentation for threshold: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html?highlight=threshold#threshold
	// Example of thresholding: http://docs.opencv.org/doc/tutorials/imgproc/threshold/threshold.html
	Mat thres_output3;
	threshold(blur_gray3, thres_output3, thresh, max_thresh, 0);


	//  FIND CONTOURS
	vector<vector<Point>> contours3;
	vector<Vec4i> hierarchy3;
	// Documentation for finding contours: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=findcontours#findcontours
	findContours(thres_output3, contours3, hierarchy3, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	

	// Find largest contour
	int maxind3 = findmaxcontour(contours3);


	// FIND CONVEX HULL OF TEMP
	vector<vector<Point> >hull3(contours3.size());
	//Find convex hull object for each contour
	for (int i = 0; i < contours3.size(); i++) {
		convexHull(Mat(contours3[i]), hull3[i], false);
	}

	Mat drawing3 = Mat::zeros(thres_output3.size(), CV_8UC3);

	//only display the convex hull and contours of largest object
	Scalar color3 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing3, contours3, maxind3, color3, 1, 8, vector<Vec4i>(), 0, Point());
	drawContours(drawing3, hull3, maxind3, color3, 1, 8, vector<Vec4i>(), 0, Point());


	// now draw convex hull in window
	namedWindow("Temp Hull: Vulcan", CV_WINDOW_AUTOSIZE);
	imshow("Temp Hull: Vulcan", drawing3);

	//-------------------------------------------------------------- TEMPLATE IMAGE (4): POINTED HAND--------------------------------------------------------------------//


	Mat src4; Mat src_gray4; Mat blur_gray4;
	// Load source image and convert it to gray
	src4 = imread("becca_point.jpg", 1);

	// Convert image to gray
	// Documentation for cvtColor: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
	cvtColor(src4, src_gray4, CV_BGR2GRAY);


	// Blur the image
	// Documentation for blur: http://docs.opencv.org/modules/imgproc/doc/filtering.html?highlight=blur#blur
	blur(src_gray4, blur_gray4, Size(3, 3));


	// Convert into binary image using thresholding
	// Documentation for threshold: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html?highlight=threshold#threshold
	// Example of thresholding: http://docs.opencv.org/doc/tutorials/imgproc/threshold/threshold.html
	Mat thres_output4;
	threshold(blur_gray4, thres_output4, thresh, max_thresh, 0);

	//  FIND CONTOURS
	vector<vector<Point>> contours4;
	vector<Vec4i> hierarchy4;
	// Documentation for finding contours: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=findcontours#findcontours
	findContours(thres_output4, contours4, hierarchy4, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Find largest contour
	int maxind4 = findmaxcontour(contours4);


	// FIND CONVEX HULL OF TEMP
	vector<vector<Point> >hull4(contours4.size());

	// Find convex hull object for each contour
	for (int i = 0; i < contours4.size(); i++) {
		convexHull(Mat(contours4[i]), hull4[i], false);
	}

	Mat drawing4 = Mat::zeros(thres_output4.size(), CV_8UC3);

	//only display the convex hull of largest contour
	Scalar color4 = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	drawContours(drawing4, contours4, maxind4, color4, 1, 8, vector<Vec4i>(), 0, Point());
	drawContours(drawing4, hull4, maxind4, color4, 1, 8, vector<Vec4i>(), 0, Point());


	// now draw convex hull in window
	namedWindow("Temp Hull: Point Hand", CV_WINDOW_AUTOSIZE);
	imshow("Temp Hull: Point Hand", drawing4);


	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------//



	// Using live video input:
	VideoCapture cap(0);
	// if not successful, exit program
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}


	Mat frame0;
	Mat currentFrame;


	// read a new frame from video
	bool bSuccess0 = cap.read(frame0);

	//if not successful, break loop
	if (!bSuccess0) {
		cout << "Cannot read a frame from video stream" << endl;
	}



	//create a window called "MyVideo"
	//namedWindow("MyVideo", WINDOW_AUTOSIZE);


	int frameCounter = 0;


	while (1) {

		frameCounter++;

		// read a new frame from video
		Mat frame;
		bool bSuccess = cap.read(frame);

		//if not successful, break loop
		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// destination frame
		Mat frameDest;
		frameDest = Mat::zeros(frame.rows, frame.cols, CV_8UC1); //Returns a zero array of same size as src mat, and of type CV_8UC1


		//----------------
		//	Skin color detection
		//----------------
		mySkinDetect(frame, frameDest);
		imshow("Skin", frameDest);

		//----------------
		//	Video Contouring
		//----------------


		// Contours (blobs in binary image) are stored in 2-dimensional vector. 
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		// Find contours
		// Documentation for finding contours: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=findcontours#findcontours
		findContours(frameDest, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


		// Find largest contour
		int maxind = findmaxcontour(contours);
	

		//----------------
		//	CONVEX HULL METHOD FOR SKIN DETECTION
		//----------------

		vector<vector<Point> >hull(contours.size());

		//Find convex hull object for each contour in frame
		for (int i = 0; i < contours.size(); i++) {
			convexHull(Mat(contours[i]), hull[i], false);
		}

		Mat drawing = Mat::zeros(frameDest.size(), CV_8UC3);

		//only display the convex hull of largest contour in frame
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, maxind, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, maxind, color, 1, 8, vector<Vec4i>(), 0, Point());


		// now draw convex hull in window
		namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
		imshow("Hull demo", drawing);




		//Mat contour_output = Mat::zeros(frame.size(), CV_8UC3);

		// Draw contours

		// first fill in contours
		//drawContours(contour_output, contours, maxind, Scalar(255, 0, 0), CV_FILLED, 8, hierarchy);

		// now outline contours
		//drawContours(contour_output, contours, maxind, Scalar(0, 0, 255), 2, 8, hierarchy);

		// Documentation for drawing rectangle: http://docs.opencv.org/modules/core/doc/drawing_functions.html
		//rectangle(contour_output, boundrec, Scalar(0, 255, 0), 1, 8, 0);


		// Draw Video Contours Window

		//namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		//imshow("Contours", contour_output);


		//imshow("MyVideo", frame);

		frame0 = frame;


		// MATCH SHAPES FUNCTION
		// compares 2 shapes and returns out a correlation value
		// here we compare the hull of the templates to the hull of the current frame

		double contour_match_value = matchShapes(hull[maxind], hull2[maxind2], CV_CONTOURS_MATCH_I1, 0); //  open hand
		double contour_match_value3 = matchShapes(hull[maxind], hull3[maxind3], CV_CONTOURS_MATCH_I1, 0);  //  vulcan
		double contour_match_value4 = matchShapes(hull[maxind], hull4[maxind4], CV_CONTOURS_MATCH_I1, 0);  //  point hand



		//  Set threshold values for each shape comparison
		//  if hull comparisons are within range, display gesture label
		if (contour_match_value < 0.1) {
			cout << " THAT IS AN OPEN HAND, SIR/MADAM!!!" << endl;
		}

		else if (contour_match_value3 < 0.06) {
			cout << " THAT IS THE VULCAN SALUTE, LLAP SIR/MADAM!!!" << endl;
		}
		else if (contour_match_value4 < 0.15) {
			cout << " THAT IS A POINTED HAND, SIR/MADAM!!!" << endl;
		}


		if (waitKey(30) == 27) {
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}



	cap.release();

	// Wait until keypress
	waitKey(0);
	return(0);
}


//Function that returns the maximum of 3 integers
int myMax(int a, int b, int c) {
	int m = a;
	(void)((m < b) && (m = b));
	(void)((m < c) && (m = c));
	return m;
}

//Function that returns the minimum of 3 integers
int myMin(int a, int b, int c) {
	int m = a;
	(void)((m > b) && (m = b));
	(void)((m > c) && (m = c));
	return m;
}

//Function that detects whether a pixel belongs to the skin based on RGB values
void mySkinDetect(Mat& src, Mat& dst) {
	//Surveys of skin color modeling and detection techniques:
	//Vezhnevets, Vladimir, Vassili Sazonov, and Alla Andreeva. "A survey on pixel-based skin color detection techniques." Proc. Graphicon. Vol. 3. 2003.
	//Kakumanu, Praveen, Sokratis Makrogiannis, and Nikolaos Bourbakis. "A survey of skin-color modeling and detection methods." Pattern recognition 40.3 (2007): 1106-1122.
	for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++){
			//For each pixel, compute the average intensity of the 3 color channels
			Vec3b intensity = src.at<Vec3b>(i, j); //Vec3b is a vector of 3 uchar (unsigned character)
			int B = intensity[0]; int G = intensity[1]; int R = intensity[2];
			if ((R > 95 && G > 40 && B > 20) && (myMax(R, G, B) - myMin(R, G, B) > 15) && (abs(R - G) > 15) && (R > G) && (R > B)){
				dst.at<uchar>(i, j) = 255;
			}
		}
	}
}


int findmaxcontour(vector<vector<Point>> contours)
{
	int largest_area = 0;
	int largest_contour_index = 0;

	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a>largest_area)
		{
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
		}
	}
	return largest_contour_index;
}