#include "stdafx.h"
#include "Detect.h"


CDetect::CDetect()
{
	Camera.open();
	if (!Camera.isOpened)
		cout << "Cannot Open Camera" << endl;
}


CDetect::~CDetect()
{
	Camera.release();
}

/*
Camera.grab();
Camera.retrieve ( camera );
cv::imshow("asdf", camera);
cv::waitKey(100);
*/
/*
void CDetect::findCenter() 
{
	Camera.grab();
	Camera.retrieve(camera);

	cvtColor(camera, HSV_img, CV_RGB2HSV);
	blur(HSV_img, HSV_img, Size(5, 5));

	inRange(HSV_img, CurrentColour_Min, CurrentColour_Max, binary_img);

	erode(binary_img, binary_img, Mat());
	dilate(binary_img, binary_img, Mat());

	max_area = 0.0;
	findContours(binary_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<Moments> moment_point(contours.size());
	int x_position(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		current_area = contourArea(contours[i], false);
		if (current_area > max_area)
		{
			max_area = current_area;
			moment_point[i] = moments(contours[i], false);
			x_position = (moment_point[i].m10 / moment_point[i].m00);
			//drawContours(camera, contours, i, white, 2, 8, hierarchy, 0, Point());
		}

		switch (currentColour)
		{
		case 0:
			green_area = max_area;
			break;
		case 1:
			orange_area = max_area;
			break;
		case 2:
			ped_area = max_area;
			break;
		}
		cout << "Center Point: " << x_position << endl;
		position = x_position;
	}
}
*/

void CDetect::findCenter()
{
	Camera.grab();
	Camera.retrieve(camera);

	cvtColor(camera, HSV_img, CV_RGB2HSV);
	blur(HSV_img, HSV_img, Size(5, 5));

	inRange(HSV_img, green_Min, green_Max, green_img);
	erode(green_img, green_img, Mat());
	dilate(green_img, green_img, Mat());

	inRange(HSV_img, orange_Min, orange_Max, orange_img);
	erode(orange_img, orange_img, Mat());
	dilate(orange_img, orange_img, Mat());

	inRange(HSV_img, ped_Min, ped_Max, ped_img);
	erode(ped_img, ped_img, Mat());
	dilate(ped_img, ped_img, Mat());

	max_area = 0.0;
	findContours(binary_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<Moments> moment_point(contours.size());
	int x_position(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		current_area = contourArea(contours[i], false);
		if (current_area > max_area)
		{
			max_area = current_area;
			moment_point[i] = moments(contours[i], false);
			x_position = (moment_point[i].m10 / moment_point[i].m00);
			//drawContours(camera, contours, i, white, 2, 8, hierarchy, 0, Point());
		}
		/*
		switch (currentColour)
		{
		case 0:
			green_area = max_area;
			break;
		case 1:
			orange_area = max_area;
			break;
		case 2:
			ped_area = max_area;
			break;
		}
		*/
		cout << "Center Point: " << x_position << endl;
		position = x_position;
	}
}

void CDetect::findGreen()
{

}

void CDetect::findOrange()
{

}

void CDetect::findPed()
{

}


void CDetect::GreenR()
{
	CurrentColour_Min = green_Min;
	CurrentColour_Max = green_Max;
	position = 0;
	currentColour = GREEN;
	findCenter();

	while (green_area > 100)
	{
		findCenter();
		//runOrange = false, runPedestrian = false;

		if (position > LBOUND) {
			cout << "green_right" << endl;
			drive.right();
		}
		else if (position < RBOUND) {
			drive.left();
			cout << "green_left" << endl;
		}
		else if (green_area > TURN_SIZE)
		{
			cout << "green big" << endl;
			drive.turn_90 = true;
			drive.right();
			drive.s_break();
		}
		else
			drive.forward();
		drive.turn_90 = false;
	}
}

void CDetect::OrangeL()
{
	CurrentColour_Min = orange_Min;
	CurrentColour_Max = orange_Max;
	position = 0;
	currentColour = ORANGE;
	findCenter();

	while (orange_area > 100)
	{
		findCenter();
		//runOrange = false, runPedestrian = false;

		if (position > LBOUND) {
			cout << "orange_right" << endl;
			drive.right();
		}
		else if (position < RBOUND) {
			drive.left();
			cout << "orange_left" << endl;
		}
		else if (orange_area > TURN_SIZE)
		{
			cout << "orange big" << endl;
			drive.turn_90 = true;
			drive.left();
			drive.s_break();
		}
		else
			drive.forward();

		drive.turn_90 = false;
	}
}

void CDetect::Pedestrian()
{
	CurrentColour_Min = ped_Min;
	CurrentColour_Max = ped_Max;
	position = 0;
	currentColour = PED;
	findCenter();

	while (ped_area > 100)
	{
		findCenter();
		//runOrange = false, runPedestrian = false;

		if (position > LBOUND) 
		{
			cout << "ped_right" << endl;
			drive.right();
		}
		else if (position < RBOUND) 
		{
			cout << "ped_left" << endl;
			drive.left();
		}
		else if (ped_area > TURN_SIZE)
		{
			cout << "ped big" << endl;
			drive.turn_90 = true;
			drive.pedestrian();
		}
		else
			drive.forward();

		drive.turn_90 = false;
	}
}

void CDetect::run() 
{
	GreenR();
	OrangeL();
	Pedestrian();
}

void CDetect::control()
{
	cout << "Please Press the key: " << endl;
	cin >> current_mode;
	while(current_mode == 'z')
	{
		prev_mode = current_mode;
		if (current_mode == 'w')
			drive.forward();
		else if (current_mode == 'a')
			drive.left();
		else if (current_mode == 'd')
			drive.right();
		else if (current_mode == 's')
			drive.reverse();
		else if (current_mode == 'q')
			drive.s_break();
		else if (current_mode == 'e')
			drive.pedestrian();
		else if (current_mode == 'z')
			drive.s_break();
		else
			cout << "Input valid control";

		if (current_mode != prev_mode)
			cin >> current_mode;
	}
}
