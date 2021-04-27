/*
 * main.h
 *
 *  Created on: Apr 15, 2021
 *      Author: User
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "gpio_driver.h"
#include "SPI_driver.h"
#include <stdint.h>
#include "stm32f2xx.h"

#define TEST_DEFINE_FOR_GIT                             100500

/********************************************************************************/
/*                                                                            	*/
/*                        		Define for SPI			                    	*/
/* 																				*/
/********************************************************************************/

/* Defines used for transfer communication */
#define CMD_MASTER_READ                               ((uint16_t)0x1234)
#define CMD_MASTER_WRITE                              ((uint16_t)0x5678)
#define CMD_LENGTH                                     2
#define DATA_LENGTH                                    4
#define ACK_LEN                                        2
#define SPI_ACK_BYTES                                  0xD5E5


/* Definition for SPIx's NVIC */
#define SPIx_IRQn                        SPI2_IRQn
#define SPIx_IRQHandler                  SPI2_IRQHandler

#define EXTIx_IRQn                 		EXTI0_IRQn              // if it for interrupt define need EXTI15 from GPIOG!!!
#define EXTIx_IRQHandler           		EXTI0_IRQHandler

/* Button details */
#define GPIO_BUTTON_PIN   0										// if it for interrupt define need EXTI15 from GPIOG!!!
#define GPIO_BUTTON_PORT  GPIOA

/* Macros used for Configuring gpios for SPI functionality */
#define GPIOB_PIN_13      13

#define GPIOB_PIN_14      14

#define GPIOB_PIN_15      15

#define SPI_CLK_PIN   GPIOB_PIN_13
#define SPI_MISO_PIN  GPIOB_PIN_14
#define SPI_MOSI_PIN  GPIOB_PIN_15

/* SPI alternate functionality value */
#define GPIO_PIN_AF5_SPI2   0x05


/********************************************************************************/
/*                                                                            	*/
/*                        		function defifnition		                 	*/
/* 																				*/
/********************************************************************************/



void spi_gpio_init(void);
void led_init(void);
void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#define LED_RED					9
#define LED_BLUE				7


#endif /* MAIN_H_ */
