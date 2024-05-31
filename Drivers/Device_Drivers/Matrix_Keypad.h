/*
 * Matrix_Keypad.h
 *
 *  Created on: Feb 17, 2024
 *      Author: youstina
 */

#ifndef DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_
#define DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_

#include"stm32f1xx_hal.h"
#include<stdint.h>


///
///peripheral configuration
/// @struct Keypad
/// @brief
/// Structure used to configure the keypad
typedef struct Keypad {
	///
	/// attribute: Keypad rows
	uint8_t Rows;
	///
	/// attribute: Kepad columns
	uint8_t Columns;

	///
	/// holds status of the buttons
	uint32_t Button_Status;

	///
	/// peripheral configuration
	GPIO_TypeDef *Row_Port;
	uint8_t Row_Start_Pin;

	GPIO_TypeDef *Column_Port;
	uint8_t Column_Start_Pin;
	uint32_t InputMask;
	uint32_t OutputMask;
} Keypad_Matrix_t;

//initialize
void Keypad_Matrix_init(Keypad_Matrix_t *kp);
/// @fn void Keypad_Matrix_refresh(Keypad_Matrix_t*)
/// @brief
///
/// @param kp
void Keypad_Matrix_refresh(Keypad_Matrix_t *kp);
/// @fn uint8_t Keypad_Matrix_key_status(Keypad_Matrix_t*, uint8_t)
/// @brief
///
/// @param kp
/// @param key
/// @return
uint8_t Keypad_Matrix_key_status(Keypad_Matrix_t *kp, uint8_t key);
///
///
static void Hardware_Generate_Delay(uint16_t delay);
static uint8_t Hardware_Get_Inputs(Keypad_Matrix_t *kp);
static void HardwareInterface_SetOutputs(Keypad_Matrix_t *kp, uint8_t OutputStatus);
uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key);
static uint8_t HardwareInterface_Get_Inputs(Keypad_Matrix_t *kp);
#endif /* DEVICE_DRIVERS_MATRIX_KEYPAD_MATRIX_KEYPAD_H_ */
