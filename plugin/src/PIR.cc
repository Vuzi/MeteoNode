/**
 * @file PIR.cc
 * @brief Class implementation for all PIR sensors
 * @author Vuzi
 * @version 0.1
 */

#include "PIR.h"

/**
 * @namespace sensor
 *
 * Name space used to store every class and functions related to the sensors
 */
namespace sensor {

    /**
     *  @brief Constructor
     *  @param pin : Value of which pin to read data on
     */
    PIR_sensor::PIR_sensor(unsigned _pin, int _freq, std::string _name):gpio_sensor(_pin, _freq, _name) {}

    PIR_sensor::~PIR_sensor() {}

    const std::string PIR_sensor::getType() {
        return "PIR";
    }

    void PIR_sensor::initialize() {

        int iErr = wiringPiSetup();
        if (iErr == -1) {
            std::cout << "ERROR : Failed to init WiringPi " << iErr << std::endl;
        }

        // TODO handle init error
    }

    int PIR_sensor::readData(int* piDetection) {
        uint8_t laststate = HIGH;

        // Prepare to read the pin
        pinMode(getPin(), INPUT);

        // Read the pin
        int timer = getTime(&laststate);

        if(timer < 0) // Capture failed
            return 0;

        if(laststate == HIGH)
            *piDetection = 1;
        else
            *piDetection = 0;

        return 1;
    }

    std::list<result> PIR_sensor::getResults() {
        std::list<result> results;

        int iDetection = -1;

        for(int i = 0; i < 10; i++) {
            if (readData(&iDetection) == 1) {
                // Humidity
                resultValue captureValue;
                captureValue.i = iDetection;

                result detection(resultType::DETECTION, captureValue);

                // Add to the list and return
                results.push_back(detection);

                return results;
            } else {
                // In some case, no value will be read. Waiting a few seconds usually allow
                // to read ne data from the sensor
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        // TODO throw exception
        std::cout << "Error :( " << std::endl;
        return results; // Return empty list of results
    }

}
