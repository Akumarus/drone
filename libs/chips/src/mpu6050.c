#include "mpu6050.h"


#define MPU6050_ADDR 0xD0

#define I2C_TIMOUT 100

#define REG_SMPLRT_DIV	0x19
#define REG_GYROS_CONF	0x1B
#define REG_ACCEL_CONF	0x1C
#define REG_ACCEL_XOUT	0x3B
#define REG_TEMP_OUT_H	0x41
#define REG_GYROS_XOUT	0x43
#define REG_PWR_MNMT_1	0x6B
#define REG_WHO_I_AM 		0x75

void mpu6050_init(I2C_HandleTypeDef *I2Cx){
	
	uint8_t	data_tx;
	uint8_t data_rx;	
	
	// check device ID
	HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_WHO_I_AM, 1, &data_rx, 1, I2C_TIMOUT);
  
	if(data_rx == MPU6050_ADDR >> 1)
	{
		// ...
		data_tx = 0x00;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_PWR_MNMT_1, 1, &data_tx, 1, I2C_TIMOUT);
		
		// ...
		data_tx = 0x07;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_SMPLRT_DIV, 1, &data_tx, 1, I2C_TIMOUT);
		
		// ...
		data_tx = 0x00;
		HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_GYROS_CONF, 1, &data_tx, 1, I2C_TIMOUT);
		
		// ...
		data_tx = 0x00;
    HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, REG_ACCEL_CONF, 1, &data_tx, 1, I2C_TIMOUT);
   }
}

void mpu6050_read_accel(I2C_HandleTypeDef *I2Cx, mpu6050_t *p)
{
	uint8_t data_rx[6];
	HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_ACCEL_XOUT, 1, data_rx, 6, I2C_TIMOUT);
	
	p->accel_x_raw = (int16_t)(data_rx[0] << 8 | data_rx[1]);
	p->accel_y_raw = (int16_t)(data_rx[2] << 8 | data_rx[3]);
	p->accel_z_raw = (int16_t)(data_rx[4] << 8 | data_rx[5]);
	
	//...
	p->accel_x = p->accel_x_raw / 16384.0f;
	p->accel_y = p->accel_y_raw / 16384.0f;
	p->accel_z = p->accel_z_raw / 16384.0f;
}

void mpu6050_read_gyros(I2C_HandleTypeDef *I2Cx, mpu6050_t *p)
{
	uint8_t data_rx[6];
	HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_ACCEL_XOUT, 1, data_rx, 6, I2C_TIMOUT);
	
	p->gyros_x_raw = (int16_t)(data_rx[0] << 8 | data_rx[1]);
	p->gyros_y_raw = (int16_t)(data_rx[2] << 8 | data_rx[3]);
	p->gyros_z_raw = (int16_t)(data_rx[4] << 8 | data_rx[5]);
	
	//...
	p->gyros_x = p->gyros_x_raw / 16384.0f;
	p->gyros_y = p->gyros_y_raw / 16384.0f;
	p->gyros_z = p->gyros_z_raw / 16384.0f;
}
void mpu6050_read_temp(I2C_HandleTypeDef *I2Cx, mpu6050_t *p)
{
	uint8_t data_rx[2];
	int16_t	temp_raw;
	
	HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, REG_TEMP_OUT_H, 1, data_rx, 2, I2C_TIMOUT);
	
	temp_raw = (int16_t)(data_rx[0] << 8 | data_rx[1]);
	p->temp =  (float)(temp_raw / (float)340.0 + (float)36.53);
}

