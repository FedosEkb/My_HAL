/*
 * gpio_driver.c
 *
 *  Created on: Apr 15, 2021
 *      Author: User
 */

#include "gpio_driver.h"


/*
 *						Static helper function
 */

/*
 * @brief Set mode of GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	mode			: mode to be configured
 * @retval	void
 */

static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no,
		uint32_t mode) {
	GPIOx->MODER &= ~(0x03 << (2 * pin_no));
	GPIOx->MODER |= (mode << (2 * pin_no));
}


/*
 * @brief Set output type for GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	op_type			: output type to be configured
 * @retval	void
 */

static void hal_gpio_configure_pin_otype(GPIO_TypeDef *GPIOx, uint16_t pin_no,
		uint32_t op_type) {
	GPIOx->OTYPER |= (op_type << (pin_no));
}

/*
 * @brief Set speed for GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	speed			: speed to be configured
 * @retval	void
 */

static void hal_gpio_configure_pin_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no,
		uint32_t speed) {
	GPIOx->OSPEEDR |= (speed << (2 * pin_no));
}

/*
 * @brief Set speed for GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	resistor		: pull up, push down, nothing
 * @retval	void
 */

static void hal_gpio_configure_pin_resistor(GPIO_TypeDef *GPIOx, uint16_t pin_no,
		uint32_t resistor) {
	GPIOx->PUPDR |= (resistor << (2 * pin_no));
}

/*
 * @brief Set alternate function for GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	alt_fun_value	: alternate function to be configured
 * @retval	void
 */
void hal_gpio_set_alt_function(GPIO_TypeDef *GPIOx, uint16_t pin_no,
		uint16_t alt_fun_value) {
	if (pin_no <= 7)
		GPIOx->AFR[0] |= (alt_fun_value << (4 * pin_no));
	else
		GPIOx->AFR[1] |= (alt_fun_value << (4 * (pin_no % 8)));
}

/*
 * @brief Read a value from for GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @retval	uint8_t			: Value read
 */

uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no) {
	return (uint8_t)((GPIOx->IDR >> pin_no) & 0x00000001);
}

/*
 * @brief Write a value to GPIO pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	value			: value to write
 * @retval	void
 */

void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value) {
	if (value)
		GPIOx->ODR |= (1 << pin_no);
	else
		GPIOx->ODR &= ~(1 << pin_no);
}

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf) {

	hal_gpio_configure_pin_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode); // set pin mode from input structure
	hal_gpio_configure_pin_otype(GPIOx, gpio_pin_conf->pin,
			gpio_pin_conf->op_type);
	hal_gpio_configure_pin_resistor(GPIOx, gpio_pin_conf->pin,
			gpio_pin_conf->pull);
	hal_gpio_configure_pin_speed(GPIOx, gpio_pin_conf->pin,
			gpio_pin_conf->speed);

}

void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel) {


	EXTI->FTSR &= ~(1 << pin_no);
	EXTI->RTSR &= ~(1 << pin_no);
	if ((edge_sel == INT_FALLING_EDGE) || (edge_sel == INT_FALLING_RISING_EDGE))
		EXTI->FTSR |= (1 << pin_no);
	if ((edge_sel == INT_RISING_EDGE) || (edge_sel == INT_FALLING_RISING_EDGE))
		EXTI->RTSR |= (1 << pin_no);
}

void hal_gpio_enable_interrupt(uint16_t pin_no,IRQn_Type irq_no){

	EXTI->IMR |= (1 << pin_no);
	NVIC_EnableIRQ(irq_no);
}

void hal_gpio_clear_interrupt(uint16_t pin_no) {
	if (EXTI->PR & (1 << pin_no))
		EXTI->PR |= (1 << pin_no);
}


