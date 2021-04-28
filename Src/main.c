/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


#include "main.h"

/* data declaration */

/* SPI handle for our SPI device */
spi_handle_t SpiHandle;





int main(void)


{
	uint32_t i=0;
	uint8_t addcm[CMD_LENGTH];
	uint8_t ack_buf[2];

	spi_gpio_init();


	led_init();  										// configure LED


	/* Configure USER Button as ext interrupt throw EXTI15 */

	_HAL_RCC_GPIOG_CLK_ENABLE();
	gpio_pin_conf_t gpio_pin_conf;
	gpio_pin_conf.pin = 15;
	gpio_pin_conf.mode = GPIO_PIN_INPUT_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	hal_gpio_init(GPIOG,&gpio_pin_conf);

	RCC->APB2ENR |= (1 << 14);
	SYSCFG->EXTICR[3] &= (0b1111 << 12);
	SYSCFG->EXTICR[3] |= (0b0110 << 12);
	hal_gpio_configure_interrupt(15, INT_FALLING_EDGE);
	hal_gpio_enable_interrupt(15, EXTI15_10_IRQn);

	_HAL_RCC_SPI2_CLK_ENABLE();


	/*fill up the SPI handle structure */
	SpiHandle.Instance				= SPI_2;

	SpiHandle.Init.BaudRatePrescaler = SPI_REG_CR1_BR_PCLK_DIV_32;
	SpiHandle.Init.Direction         = SPI_ENABLE_2_LINE_UNI_DIR;
	SpiHandle.Init.CLKPhase          = SPI_SECOND_CLOCK_TRANS;
	SpiHandle.Init.CLKPolarity       = SPI_CPOL_LOW;
	SpiHandle.Init.DataSize          = SPI_8BIT_DF_ENABLE;
	SpiHandle.Init.FirstBit          = SPI_MSB_FIRST;
	SpiHandle.Init.NSS               = SPI_SSM_ENABLE;
	SpiHandle.Init.Mode              = SPI_MASTER_MODE_SEL;

	SpiHandle.State = HAL_SPI_STATE_READY;

	/* Call driver API to initialize the SPI device */
	hal_spi_init(&SpiHandle);

	/* Enable the IRQs in the NVIC */
	NVIC_EnableIRQ(SPI2_IRQn);


	while (1)
		;
}

void led_init(void){
	gpio_pin_conf_t gpio_pin_conf;

	_HAL_RCC_GPIOI_CLK_ENABLE();
	gpio_pin_conf.pin = LED_RED;
	gpio_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	hal_gpio_init(GPIOI,&gpio_pin_conf);

	_HAL_RCC_GPIOC_CLK_ENABLE();
	gpio_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIOC, &gpio_pin_conf);

}

void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin) {
	if (hal_gpio_read_from_pin(GPIOx, pin))
		hal_gpio_write_to_pin(GPIOx, pin, 0);
	else
		hal_gpio_write_to_pin(GPIOx, pin, 1);
}

void spi_gpio_init(void){
	gpio_pin_conf_t gpio_pin_conf;

	_HAL_RCC_GPIOI_CLK_ENABLE();

	/* configure GPIOB_PIN_13 for SPI CLK functionality */
	gpio_pin_conf.pin = SPI_CLK_PIN;
	gpio_pin_conf.mode = GPIO_PIN_ALT_FUN_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_PUSH_DOWN;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;

	hal_gpio_set_alt_function(GPIOI, SPI_CLK_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOI,&gpio_pin_conf);

	/* configure GPIOB_PIN_14 for SPI MISO functionality */
	gpio_pin_conf.pin = SPI_MISO_PIN;
	gpio_pin_conf.pull = GPIO_PIN_PULL_UP;

	hal_gpio_set_alt_function(GPIOI, SPI_MISO_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOI, &gpio_pin_conf);

	/* configure GPIOB_PIN_15 for SPI MISO functionality */
	gpio_pin_conf.pin = SPI_MOSI_PIN;
	gpio_pin_conf.pull = GPIO_PIN_PULL_UP;

	hal_gpio_set_alt_function(GPIOI, SPI_MOSI_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOI, &gpio_pin_conf);
}

void EXTI15_10_IRQHandler(void){
	hal_gpio_clear_interrupt(15);
	led_toggle(GPIOI,LED_RED);
	led_toggle(GPIOC,LED_BLUE);
}
