#pragma once
#include "Drive.h"
#include "raspicam_cv.h"

#include <stdlib.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <errno.h>
#include <stdio.h>

#define TURN_SIZE 3000000

class CDetect
{
private:
	CDrive drive;
	typedef std::chrono::duration<int, std::ratio<1, 100>> frame_100;
	typedef std::chrono::duration<int, std::ratio<1, 100>> frame_50;
	
	typedef enum { GREEN, ORANGE, PED } Colour;
	int currentColour;

	bool runGreen = true, runOrange = true, runPedestrian = true;

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;
	int position;

	double max_area, current_area;
	double green_area, orange_area, ped_area;

	Scalar white = Scalar(255, 255, 255);

	Scalar CurrentColour_Min;
	Scalar CurrentColour_Max;

	Scalar orange_Min = Scalar(0, 170, 20);
	Scalar orange_Max = Scalar(15, 255, 255);

	Scalar green_Min = Scalar(40, 110, 40);
	Scalar green_Max = Scalar(55, 255, 255);

	Scalar ped_Min = Scalar(90, 50, 50);
	Scalar ped_Max = Scalar(120, 255, 255);

	raspicam::RaspiCam_Cv Camera;
	Mat camera;
	Mat binary_img;
	Mat HSV_img;

public:
	CDetect();
	~CDetect();

	void findCenter();
	void GreenR();
	void OrangeL();
	void Pedestrian();
	void run();
};

