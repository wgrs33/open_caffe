#include "opencaffe/base/devices/pid_controller.h"
#include <iostream>
#include <iomanip>

int main(void) {

    OpenCaffe::PidController<int> pid(1,5,0);
    pid.setOutputLimits(0,100);
	pid.setOutputRampRate(5);

    int setpoint=90;
    int sensor=0;
    int real_sensor;
    // int analogRead = 129;

    int analogRead[500];

    for (int i = 0; i < 500; ++i) {
        if (i > 200)
            analogRead[i] = 100;
        else
            analogRead[i] = i;
    }

    for (int i = 0; i < 120; ++i) {
        sensor = (int)(sensor * 0.95 + analogRead[i] *.05);
        // setpoint = analogRead;

        //Run through the PID calculations, and get the desired output values
        int out = pid.getOutput(sensor, setpoint);
        // sensor = sensor + out;

        // std::cout << std::fixed << std::showpoint << std::setprecision(3);
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Setpoint: " << setpoint;
        std::cout << "\tInput: " << analogRead[i];
        std::cout << "\tSensor: " << sensor;
        std::cout << "\tOutput: " << out;
        std::cout << "\tError: " << setpoint - sensor << std::endl;
    }

    return 0;
}