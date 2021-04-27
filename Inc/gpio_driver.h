

#ifndef _HAL_GPIO_DRIVERS_H_
#define _HAL_GPIO_DRIVERS_H_


#include <stdint.h>

/* include MCU  specific header*/
#include "stm32f4xx.h"


/*				Macros for GPIO initialization			*/

/*GPIO Mode setting values*/
#define GPIO_PIN_INPUT_MODE					((uint32_t)0x00)
#define GPIO_PIN_OUTPUT_MODE				((uint32_t)0x01)
#define GPIO_PIN_ALT_FUN_MODE				((uint32_t)0x02)
#define GPIO_PIN_ANALOG_MODE				((uint32_t)0x03)

/*GPIO OP type setting values*/
#define GPIO_PIN_OP_TYPE_PUSHPULL			((uint32_t)0x00)
#define GPIO_PIN_OP_TYPE_OPENDRAIN			((uint32_t)0x01)

/*GPIO Speed type selection (this register set front rise/fall time, but reducing this time you have to play for in more current(AMP)!!
 * For efficiency you need set as low speed as possible*/
#define GPIO_PIN_SPEED_LOW					((uint32_t)0x00)
#define GPIO_PIN_SPEED_MEDIUM				((uint32_t)0x01)
#define GPIO_PIN_SPEED_HIGH					((uint32_t)0x02)
#define GPIO_PIN_SPEED_VERY_HIGH			((uint32_t)0x03)

/*GPIO pull up/pull down internal resistor selection*/
#define GPIO_PIN_NO_PULL_PUSH				((uint32_t)0x00)
#define GPIO_PIN_PULL_UP					((uint32_t)0x01)
#define GPIO_PIN_PUSH_DOWN					((uint32_t)0x02)

/*Redefine port address*/

#define GPIO_PORT_A 						GPIOA
#define GPIO_PORT_B 						GPIOB
#define GPIO_PORT_C 						GPIOC
#define GPIO_PORT_D 						GPIOD
#define GPIO_PORT_E 						GPIOE
#define GPIO_PORT_F 						GPIOF
#define GPIO_PORT_G 						GPIOG
#define GPIO_PORT_H 						GPIOH
#define GPIO_PORT_I 						GPIOI

/* Macros to enable clocking for gpio port */

#define _HAL_RCC_GPIOA_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 0))
#define _HAL_RCC_GPIOB_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 1))
#define _HAL_RCC_GPIOC_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 2))
#define _HAL_RCC_GPIOD_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 3))
#define _HAL_RCC_GPIOE_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 4))
#define _HAL_RCC_GPIOF_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 5))
#define _HAL_RCC_GPIOG_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 6))
#define _HAL_RCC_GPIOH_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 7))
#define _HAL_RCC_GPIOI_CLK_ENABLE()			(RCC->AHB1ENR |= (1 << 8))

/*
 * 						Data Structure for GPIO pin Initialization
 * */

/*
 * @brief 	GPIO pin configuration structure
 * 			This structure will be filled and passed to driver by pinter to initialize the gpio pin
 * */

typedef struct
{
	uint32_t pin;						/* specifies the GPIO pins to be configured */

	uint32_t mode;						/* no cap comment */

	uint32_t op_type;					/* no cap comment */

	uint32_t pull;						/* no cap comment */

	uint32_t speed;						/* no cap comment */

	uint32_t alternate_function;		/* no cap comment */

}gpio_pin_conf_t;

/*I don't know for what in, mb i will understand it after
 * @brief I2C pinspack enumeration
 * */
typedef enum
{
	INT_RISING_EDGE,
	INT_FALLING_EDGE,
	INT_FALLING_RISING_EDGE,
}int_edge_sel_t;


/*
 * 								Driver exposed APIs
 * */

/*
 * @brief Initializes the gpio pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	*gpio_pin_conf 	: pointer to the pin configuration structure
 * @retval	void
 */

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf);

/*
 * @brief Read a value from a given pin number
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no		: GPIO pin number
 * @retval	uint8_t			: Value read
 */

uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no);

/*
 * @brief Write a value to a given pin number
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	val				: Value to write
 * @retval	void
 */

void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no,uint8_t val);

/*
 * @brief Set the alternate function for the given pin
 * @param	*GPIOx 			: pointer to GPIO Port base address
 * @param	pin_no			: GPIO pin number
 * @param	alt_fun_value	: number of alternate function to set
 * @retval	void
 */

void hal_gpio_set_alt_function(GPIO_TypeDef *GPIOx, uint16_t pin_no,uint16_t alt_fun_value);

/*
 * @brief Configure the interrupt for a given pin number
 * @param	pin_no			: GPIO pin number
 * @param	edge_sel		: Triggering set selection value of type "int_edge_sel_t"
 * @retval	void
 */

void hal_gpio_configure_interrupt(uint16_t pin_no,int_edge_sel_t edge_sel);

/*
 * @brief Enable the interrupt for a given pin number ad irg number
 * @param	pin_no			: GPIO pin number
 * @param	irq_no			: irq_number to be enabled in NVIC
 * @retval	void
 */

void hal_gpio_enable_interrupt(uint16_t pin_no,IRQn_Type irq_no);

/*
 * @brief Enable the interrupt for a given pin number ad irg number
 * @param	pin_no			: GPIO pin number
 * @retval	void
 */

void hal_gpio_clear_interrupt(uint16_t pin_no);

#endif /* _HAL_GPIO_DRIVER_H_ */



