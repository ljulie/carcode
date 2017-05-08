#pragma once
//#include <pigpio.h>
//#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>

// OpenCV Include
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define AIN1 4
#define BIN1 17
#define AIN2 3
#define BIN2 27
#define PWMA 2
#define PWMB 22
#define STBY 18
#define SERV 12

#define SERV_MAX 2400
#define SERV_MIN 600

#define RBOUND (330)
#define LBOUND (310)

#define LOW 0
#define HIGH 1

class CDrive
{
public:
	CDrive();
	~CDrive();

	bool turn_90 = false;

	void forward();
	void reverse();
	void left();
	void right();
	void s_break();
	void pedestrian();

private:
	void stop();
};

