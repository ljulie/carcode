#include "stdafx.h"
#include "Drive.h"


CDrive::CDrive()
{
	if (gpioInitialise() < 0)
		cout << "initialised gpio" << endl;

	gpioSetMode(AIN1, PI_OUTPUT);
	gpioSetMode(BIN1, PI_OUTPUT);
	gpioSetMode(AIN2, PI_OUTPUT);
	gpioSetMode(BIN2, PI_OUTPUT);
	gpioSetMode(PWMA, PI_OUTPUT);
	gpioSetMode(PWMB, PI_OUTPUT);
	gpioSetMode(STBY, PI_OUTPUT);

	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, HIGH);

	gpioWrite(STBY, HIGH);

	gpioWrite(BIN1, HIGH);
	gpioWrite(BIN2, LOW);
	gpioPWM(PWMA, 80);
	gpioPWM(PWMB, 80);
}


CDrive::~CDrive()
{
	gpioPWM(PWMA, HIGH);
	gpioPWM(PWMB, HIGH);

	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, LOW);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, LOW);
}

void CDrive::forward()
{
	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, HIGH);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, HIGH);
}

void CDrive::reverse()
{
	gpioWrite(AIN1, HIGH);
	gpioWrite(AIN2, LOW);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, HIGH);
}

void CDrive::left()
{
	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, HIGH);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, LOW);

	if (turn_90)
		waitKey(1000);
}

void CDrive::right()
{
	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, LOW);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, HIGH);

	if (turn_90)
		waitKey(1000);
}

void CDrive::s_break()
{
	//waitKey(1000);
	gpioWrite(AIN1, HIGH);
	gpioWrite(AIN2, HIGH);
	gpioWrite(BIN1, HIGH);
	gpioWrite(BIN2, HIGH);
	waitKey(1000);
}

void CDrive::stop()
{
	gpioPWM(PWMA, HIGH);
	gpioPWM(PWMB, HIGH);
	gpioWrite(AIN1, LOW);
	gpioWrite(AIN2, LOW);
	gpioWrite(BIN1, LOW);
	gpioWrite(BIN2, LOW);
}

void CDrive::pedestrian()
{
	drive.s_break();
	for (int serv = SERV_MIN; serv < SERV_MAX; serv + 10)
		gpioServo(SERV, serv);
}