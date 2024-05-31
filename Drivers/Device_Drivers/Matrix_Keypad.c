/*
 * Matrix_Keypad.c
 *
 *  Created on: Feb 17, 2024
 *      Author: youstina
 */
#include "Matrix_Keypad.h"

void HardwareInterface_initialize(Keypad_Matrix_t *kp) {
	GPIO_InitTypeDef gp = { .Mode= GPIO_MODE_OUTPUT_PP, .Speed = GPIO_SPEED_LOW };
	uint32_t Pins = 0;
	for (int x = 0; x < kp->Rows; x++) {
		Pins |= (1 << (kp->Row_Start_Pin) + x);
	}
	gp.Pin = Pins;
	HAL_GPIO_Init(kp->Row_Port, &gp);

	kp->OutputMask = Pins;
	gp.Mode = GPIO_MODE_INPUT;
	gp.Pull = GPIO_PULLDOWN;
	Pins = 0;
	for (int x = 0; x < kp->Columns; x++) {
		Pins |= (1 << (kp->Column_Start_Pin) + x);
	}
	gp.Pin = Pins;
	HAL_GPIO_Init(kp->Column_Port, &gp);
	kp->InputMask = Pins;
}
void Keypad_Matrix_init(Keypad_Matrix_t *kp) {
	HardwareInterface_initialize(kp);
	HardwareInterface_SetOutputs(kp, 0);
}
void Keypad_Matrix_refresh(Keypad_Matrix_t *kp) {
	kp->Button_Status = 0;
	uint8_t scan = 0b00000001;
	for (uint8_t x = 0; x < kp->Rows; x++) { //kp is pointer to struct that includes number of rows
		HardwareInterface_SetOutputs(kp, scan); //the pins of the rows are now outputs with value scan
		Hardware_Generate_Delay(1);
		kp->Button_Status |= HardwareInterface_Get_Inputs(kp) << (x * kp->Columns); //each row read is shifted by the number of rows
	scan <<= 1; //scan =scan<<1

}
}
uint8_t Keypad_Matrix_key_status(Keypad_Matrix_t *kp, uint8_t key) {

}
uint8_t Keypad_Matrix_ReadKey(Keypad_Matrix_t *kp, uint8_t key){
	if(kp->Button_Status& (1<<key)){
		return 1;
	}
	else{
		return 0;
	}
}
static void HardwareInterface_SetOutputs(Keypad_Matrix_t *kp,
	uint8_t OutputStatus) {
kp->Row_Port->ODR &= ~kp->OutputMask;
kp->Row_Port->ODR |= (uint32_t) OutputStatus << kp->Row_Start_Pin;
}
static void Hardware_Generate_Delay(uint16_t delay) {
HAL_Delay(delay);
}
static uint8_t HardwareInterface_Get_Inputs(Keypad_Matrix_t *kp) {
uint32_t m = kp->Column_Port->IDR & kp->InputMask;
m >>= kp->Column_Start_Pin;
return (uint8_t) m;
}
