#ifndef H_I2C_SENSOR
#define H_I2C_SENSOR

/**
 * @file i2c_sensor.h
 * @brief Class for TSL2561 sensors. A TSL2561 use the I2C bus on the raspberry
 * @author Vuzi
 * @version 0.1
 */

#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>

#include "sensor.h"


namespace sensor {

	/**
	 * I2C sensor. I2C sensor needs a special intialization, and a special way of retreiving data
	 * from the sensor (reading a special file)
	 */
	class i2c_sensor : public sensor {

		public:
			i2c_sensor(uint16_t, int);
			~i2c_sensor();

		protected:
			/**
			 * Return the address of the device
			 * @return The address of the device
			 */
			uint16_t getDeviceAddress();

			/**
			 * Read and return data on the specified register
			 * @param  uint16_t The instruction where to read
			 * @return          The value read
			 */
			uint16_t readRegister(uint16_t);

			/**
			 * Write a value in the specified register
			 * @param  uint16_t The instruction where to write at
			 * @param  uint16_t The value to write
			 */
			void writeRegister(uint16_t, uint16_t);

			/**
			 * Open the bus to read data from. If the opening failed, the filed
			 * descriptor is set to -1
			 * @return          The bus descriptor, or -1 on error 
			 */
			int openBus();

			/**
			 * Return the file descriptor of the bus, or -1
			 * @return The bus file descriptor
			 */
			int getBus();

			/**
			 * Close the bus
			 */
			void closeBus();

		private:
			int i2c_fd;              // File descriptor of the bus
			uint16_t deviceAddress;  // Adress of the device
	};
}

#endif // H_I2C_SENSOR