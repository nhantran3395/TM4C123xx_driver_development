/**
*@file tm4c123xx_gpio.c
*@brief provide functions for interfacing with GPIO pin
*
*This source file provide functions for interfacing with GPIO pins on tm4c123xx MCUs.
*
*@author Tran Thanh Nhan
*@date 26/07/2019
*/

#include "tm4c123xx_gpio.h"  

void GPIO_CLK_ctr (GPIOA_Type *GPIOxPtr, uint8_t enOrDis)
{
	if (enOrDis == ENABLE){
		if(GPIOxPtr==GPIOA){
			SYSCTL->RCGCGPIO |= (1<<0);
		}else if(GPIOxPtr==GPIOB){
			SYSCTL->RCGCGPIO |= (1<<1);
		}else if(GPIOxPtr==GPIOC){
			SYSCTL->RCGCGPIO |= (1<<2);
		}else if(GPIOxPtr==GPIOD){
			SYSCTL->RCGCGPIO |= (1<<3);
		}else if(GPIOxPtr==GPIOE){
			SYSCTL->RCGCGPIO |= (1<<4);
		}else if(GPIOxPtr==GPIOF){
			SYSCTL->RCGCGPIO |= (1<<5);
		}			
	}else{
		if(GPIOxPtr==GPIOA){
			SYSCTL->RCGCGPIO &= ~(1<<0);
		}else if(GPIOxPtr==GPIOB){
			SYSCTL->RCGCGPIO &= ~(1<<1);
		}else if(GPIOxPtr==GPIOC){
			SYSCTL->RCGCGPIO &= ~(1<<2);
		}else if(GPIOxPtr==GPIOD){
			SYSCTL->RCGCGPIO &= ~(1<<3);
		}else if(GPIOxPtr==GPIOE){
			SYSCTL->RCGCGPIO &= ~(1<<4);
		}else if(GPIOxPtr==GPIOF){
			SYSCTL->RCGCGPIO &= ~(1<<5);
		}
	}
}

void GPIO_init (GPIO_Handle_t *GPIOpinxHandlePtr){
	uint8_t pinMode = GPIOpinxHandlePtr->GPIOpinConfigPtr->mode;
	uint8_t pinNumber = GPIOpinxHandlePtr->GPIOpinConfigPtr->pinNumber;
	uint8_t puPdr = GPIOpinxHandlePtr->GPIOpinConfigPtr->puPdr;
	uint8_t outType = GPIOpinxHandlePtr->GPIOpinConfigPtr->outType;
	uint8_t drive = GPIOpinxHandlePtr->GPIOpinConfigPtr->driveSel;
	uint8_t slewRate = GPIOpinxHandlePtr->GPIOpinConfigPtr->slewRateCtrl;
	
	if(pinMode == GPIO_MODE_IN || pinMode >= GPIO_MODE_INTRPT_FE){	
		
		/*general configuration for GPIO pin input mode and interrupt*/
		GPIOpinxHandlePtr->GPIOxPtr->AFSEL &= ~(1<<pinNumber);
		GPIOpinxHandlePtr->GPIOxPtr->DIR &= ~(1<<pinNumber);
		GPIOpinxHandlePtr->GPIOxPtr->ODR &= ~(1<<pinNumber);
		GPIOpinxHandlePtr->GPIOxPtr->DEN |= 1<<pinNumber;
		
		if(puPdr == GPIO_NO_PUPDR){
			GPIOpinxHandlePtr->GPIOxPtr->PUR &= ~(1<<pinNumber);
			GPIOpinxHandlePtr->GPIOxPtr->PDR &= ~(1<<pinNumber);
		}else if(puPdr == GPIO_PU){
			GPIOpinxHandlePtr->GPIOxPtr->PUR |= 1<<pinNumber;
		}else if(puPdr == GPIO_PDR){
			GPIOpinxHandlePtr->GPIOxPtr->PDR |= 1<<pinNumber;
		}
		
		if (pinMode >= GPIO_MODE_INTRPT_FE){
		/*configuration for GPIO pin interrupt mode*/
			
			//GPIOpinxHandlePtr->GPIOxPtr->ICR |= 1<<pinNumber;
			GPIOpinxHandlePtr->GPIOxPtr->IS |= 1<<pinNumber;
			GPIOpinxHandlePtr->GPIOxPtr->IM = 1<<pinNumber;
			__enable_irq();
			
			if(pinMode == GPIO_MODE_INTRPT_FE){
				GPIOpinxHandlePtr->GPIOxPtr->IBE &= ~(1<<pinNumber);
				GPIOpinxHandlePtr->GPIOxPtr->IEV &= ~(1<<pinNumber);
			}else if(pinMode == GPIO_MODE_INTRPT_RE){
				GPIOpinxHandlePtr->GPIOxPtr->IBE &= ~(1<<pinNumber);
				GPIOpinxHandlePtr->GPIOxPtr->IEV |= 1<<pinNumber;				
			}else if (pinMode == GPIO_MODE_INTRPT_RFE){
				GPIOpinxHandlePtr->GPIOxPtr->IBE |= 1<<pinNumber;			
			}
		}
		
	}else if(pinMode == GPIO_MODE_OUT){
		
		/*configuration for GPIO output pin*/
		GPIOpinxHandlePtr->GPIOxPtr->AFSEL &= ~(1<<pinNumber);
		GPIOpinxHandlePtr->GPIOxPtr->DIR |= 1<<pinNumber;
		GPIOpinxHandlePtr->GPIOxPtr->DEN |= 1<<pinNumber;
		
		if(outType == GPIO_OTYPE_OD){
			/*open drain mode*/
			GPIOpinxHandlePtr->GPIOxPtr->ODR |= 1<<pinNumber;
		}else if(outType == GPIO_OTYPE_NONE){
			/*none open drain mode; pull up or pull down or none*/
			GPIOpinxHandlePtr->GPIOxPtr->ODR &= ~(1<<pinNumber);
			if(puPdr == GPIO_NO_PUPDR){
				GPIOpinxHandlePtr->GPIOxPtr->PUR &= ~(1<<pinNumber);
				GPIOpinxHandlePtr->GPIOxPtr->PDR &= ~(1<<pinNumber);
			}else if(puPdr == GPIO_PU){
				GPIOpinxHandlePtr->GPIOxPtr->PUR |= 1<<pinNumber;
			}else if(puPdr == GPIO_PDR){
				GPIOpinxHandlePtr->GPIOxPtr->PDR |= 1<<pinNumber;
			}
		}
		
		if(drive==GPIO_DRIVE_2MA){
			GPIOpinxHandlePtr->GPIOxPtr->DR2R |= 1<<pinNumber;
		}else if (drive==GPIO_DRIVE_4MA){
			GPIOpinxHandlePtr->GPIOxPtr->DR2R |= 1<<pinNumber;
		}else if (drive==GPIO_DRIVE_8MA){
			GPIOpinxHandlePtr->GPIOxPtr->DR8R |= 1<<pinNumber;
			if(slewRate == GPIO_SLEWRATE_EN){
					GPIOpinxHandlePtr->GPIOxPtr->SLR |= 1<<pinNumber;
			}else{
					GPIOpinxHandlePtr->GPIOxPtr->SLR &= ~(1<<pinNumber);
			}
		}		
	}
}

/**
*@brief Deinitilize GPIO pin
*@param Pointer to base address of GPIO port x registers
*@return none
*/
void GPIO_deinit (GPIOA_Type *GPIOxPtr);

uint8_t GPIO_read_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber)
{
	return (uint8_t)(GPIOxPtr->DATA>>pinNumber)&0x01;
}

/**
*@brief Read data from GPIO input port
*@param Pointer to base address of GPIO port x registers
*@return Data from GPIO port
*/
uint16_t GPIO_read_port (GPIOA_Type *GPIOxPtr);

void GPIO_write_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber, uint8_t setOrClear)
{
	if(setOrClear == SET){
		GPIOxPtr->DATA = 1<<pinNumber;
	}else{
		GPIOxPtr->DATA = ~(1<<pinNumber);
	}
}

/**
*@brief Write data to GPIO output port
*@param Pointer to base address of GPIO port x registers
*@param Set or clear action
*@return none
*/
void GPIO_write_port (GPIOA_Type *GPIOxPtr);

void GPIO_toggle_pin (GPIOA_Type *GPIOxPtr, uint8_t pinNumber)
{
	GPIOxPtr->DATA ^= 1<<pinNumber;
}

void GPIO_Intrpt_priority_config (uint8_t IRQnumber, uint8_t priority)
{
	uint8_t registerNo = IRQnumber/4;
	uint8_t sectionNo = IRQnumber%4;
	
	NVIC->IP[registerNo] = priority<<(8*sectionNo + IRQ_PRI_NUM_OF_BITS_IMPLEMENTED);
}

void GPIO_Intrpt_ctrl (uint8_t IRQnumber, uint8_t enOrDis)
{
	if(enOrDis == ENABLE){
		NVIC->ISER[0] |= 1<<IRQnumber;
	}else{
		NVIC->ICER[0] |= 1<<IRQnumber;
	}
}

void GPIO_Intrpt_handler (GPIOA_Type *GPIOxPtr, uint8_t pinNumber)
{
	GPIOxPtr->ICR |= 1<<pinNumber;
}
