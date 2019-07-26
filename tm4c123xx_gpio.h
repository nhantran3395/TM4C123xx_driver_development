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

#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define ENABLE 1
#define DISABLE 0
#define SET 1
#define CLEAR 0

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
*@GPIO_MODE
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
*GPIO_PUPDR_MODE
*GPIO pin input modes
*/
#define GPIO_NO_PUPDR 0
#define GPIO_PU 1
#define GPIO_PDR 2

typedef struct
{
}GPIO_Pin_config_t;

typedef struct 
{
}GPIO_Handle_t;

/**
*@brief GPIO port clock setup 
*@param Pointer to base address of GPIO port x registers
*@param Enable or disable action
*@return none
*/
void GPIO_CLK_ctr (void);

/**
*@brief Initialize GPIO pin
*@param Pointer to GPIO_Handle struct
*@return none
*/
void GPIO_init (void);

/**
*@brief Deinitilize GPIO pin
*@param Pointer to base address of GPIO port x registers
*@return none
*/
void GPIO_deinit (void);

/**
*@brief Read data from GPIO input pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@return Data from GPIO input pin
*/
uint8_t GPIO_read_pin (void);

/**
*@brief Read data from GPIO input port
*@param Pointer to base address of GPIO port x registers
*@return Data from GPIO port
*/
uint16_t GPIO_read_port (void);

/**
*@brief Write data to GPIO output pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@param Set or clear action
*@return none
*/
void GPIO_write_pin (void);

/**
*@brief Write data to GPIO output port
*@param Pointer to base address of GPIO port x registers
*@param Set or clear action
*@return none
*/
void GPIO_write_port (void);

/**
*@brief Toggle GPIO output pin
*@param Pointer to base address of GPIO port x registers
*@param GPIO pin number
*@return none
*/
void GPIO_toggle_pin (void);

/**
*@brief Config interrupt priority
*@param IRQ number
*@param Priority
*@return none
*/
void GPIO_Intrpt_priority_config (void);

/**
*@brief Enable or disable GPIO pin 's interrupt 
*@param IRQ number
*@param Enable or disable action
*@return none
*/
void GPIO_Intrpt_ctrl (void);

/**
*@brief Handler for GPIO pin 's interrupt
*@param GPIO pin number
*@return none
*/
void GPIO_Intrpt_handler (void);

#endif 