/**
*@file tm4c123xx_gpio.h
*@brief provide functions for interfacing with GPIO pin
*
*This header file provide functions for interfacing with GPIO pins on tm4c123xx MCUs.
*
*@author Tran Thanh Nhan
*@date 26/07/2019
*/

#ifndef TM4C123XX_GPIO_H
#define TM4C123XX_GPIO_H

#include "TM4C123GH6PM.h"                    // Device header
#include <stdint.h>

#define ENABLE 1
#define DISABLE 0
#define SET 1
#define CLEAR 0

#define IRQ_NUM_PORTA 0
#define IRQ_NUM_PORTB 1
#define IRQ_NUM_PORTC 2
#define IRQ_NUM_PORTD 3
#define IRQ_NUM_PORTE 4
#define IRQ_NUM_PORTF 5
#define IRQ_PRI_NUM_OF_BITS_IMPLEMENTED 4

/*
*@GPIO_PIN_NO
*GPIO pin number
*/
#define GPIO_PIN_NO_0	0
#define GPIO_PIN_NO_1	1
#define GPIO_PIN_NO_2	2
#define GPIO_PIN_NO_3	3
#define GPIO_PIN_NO_4	4
#define GPIO_PIN_NO_5	5
#define GPIO_PIN_NO_6	6
#define GPIO_PIN_NO_7	7

/*
*@GPIO_MODE_SEL
*GPIO pin possible modes
*/
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANL 3
#define GPIO_MODE_INTRPT_FE	4	//Interrupt, falling edge
#define GPIO_MODE_INTRPT_RE	5	//Interrupt, raising edge
#define GPIO_MODE_INTRPT_RFE	6	//Interrupt, both edge

/*
*@GPIO_PUPDR_SEL
*GPIO pin pull up/ pull down selection
*/
#define GPIO_NO_PUPDR 0
#define GPIO_PU 1
#define GPIO_PDR 2

/*
*@GPIO_OUTTYPE_SEL
*GPIO pin open drain selection
*/
#define GPIO_OTYPE_NONE 0
#define GPIO_OTYPE_OD 1

/*
*@GPIO_DRIVE_SEL
*GPIO drive current selection
*/
#define GPIO_DRIVE_2MA 0
#define GPIO_DRIVE_4MA 1
#define GPIO_DRIVE_8MA 2

/*
*@GPIO_SLEWRATE_SEL
*GPIO slewrate selection
*/
#define GPIO_SLEWRATE_DIS 0
#define GPIO_SLEWRATE_EN 1


typedef struct
{
	uint8_t pinNumber;	/*Refer to @GPIO_PIN_NO for possible value*/
	uint8_t mode;	/*Refer to @GPIO_MODE_SEL for possible value*/
	uint8_t puPdr;	/*Refer to @GPIO_PUPDR_SEL for possible value*/
	uint8_t outType;	/*Refer to @GPIO_OUTTYPE_SEL for possible value*/
	uint8_t driveSel;	/*Refer to @GPIO_DRIVE_SEL for possible value*/
	uint8_t slewRateCtrl;	/*Refer to @GPIO_SLEWRATE_SEL for possible value*/
	uint8_t altFunc;	
}GPIO_Pin_config_t;

typedef struct 
{
	GPIOA_Type *GPIOxPtr;
	GPIO_Pin_config_t *GPIOpinConfigPtr;
}GPIO_Handle_t;

/**
*@brief GPIO port clock setup 
*@param Pointer to base address of GPIO port x registers
*@param Enable or disable action
*@return none
*/
void GPIO_CLK_ctr (GPIOA_Type *GPIOxPtr, uint8_t enOrDis);

/**
*@brief Initialize GPIO pin
*@param Pointer to GPIO_Handle struct
*@return none
*/
void GPIO_init (GPIO_Handle_t *GPIOpinxHandlePtr);

/**
*@brief Deinitilize GPIO pin
*@param Pointer to base address of GPIO port x registers
*@return none
*/
void GPIO_deinit (GPIOA_Type *GPIOxPtr);

/**
*@brief Read data from GPIO input pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@return Data from GPIO input pin
*/
uint8_t GPIO_read_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber);

/**
*@brief Read data from GPIO input port
*@param Pointer to base address of GPIO port x registers
*@return Data from GPIO port
*/
uint16_t GPIO_read_port (GPIOA_Type *GPIOxPtr);

/**
*@brief Write data to GPIO output pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@param Set or clear action
*@return none
*/
void GPIO_write_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber, uint8_t setOrClear);

/**
*@brief Write data to GPIO output port
*@param Pointer to base address of GPIO port x registers
*@param Set or clear action
*@return none
*/
void GPIO_write_port (GPIOA_Type *GPIOxPtr);

/**
*@brief Toggle GPIO output pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@return none
*/
void GPIO_toggle_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber);

/**
*@brief Config interrupt priority
*@param IRQ number
*@param Priority
*@return none
*/
void GPIO_Intrpt_priority_config (uint8_t IRQnumber, uint8_t priority);

/**
*@brief Enable or disable GPIO pin 's interrupt 
*@param IRQ number
*@param Enable or disable action
*@return none
*/
void GPIO_Intrpt_ctrl (uint8_t IRQnumber, uint8_t enOrDis);

/**
*@brief Handler for GPIO pin 's interrupt
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@return none
*/
void GPIO_Intrpt_handler (GPIOA_Type *GPIOxPtr, uint8_t pinNumber);

#endif 