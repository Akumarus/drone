
/*

	- Name:		mpu6050 driver
	- Data: 	13.02.2024
	- Author:	Akuma
	
*/

#include "stdint.h"
#include "i2c.h"

// mpu6050 stucture
typedef struct 
{
	//acceleration
	int16_t accel_x_raw;
	int16_t accel_y_raw;
	int16_t accel_z_raw;
	
	float 	accel_x;
	float		accel_y;
	float		accel_z;
	
	//gyroscope
	int16_t gyros_x_raw;
	int16_t gyros_y_raw;
	int16_t gyros_z_raw;
	
	float 	gyros_x;
	float		gyros_y;
	float		gyros_z;

	float		temp;
}mpu6050_t;


void mpu6050_init(I2C_HandleTypeDef *I2Cx);
void mpu6050_read_accel(I2C_HandleTypeDef *I2Cx, mpu6050_t *p);
void mpu6050_read_gyros(I2C_HandleTypeDef *I2Cx, mpu6050_t *p);
void mpu6050_read_temp(I2C_HandleTypeDef *I2Cx, mpu6050_t *p);
