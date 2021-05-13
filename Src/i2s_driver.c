/*
 * i2s_driver.c
 *
 *  Created on: 11 мая 2021 г.
 *      Author: User
 */

#include "i2c_driver.h"


/******************************************************************************/
/*                                                                            */
/*                      Driver exposed APIs                                   */
/*                                                                            */
/******************************************************************************/

void hal_i2c_enable_peripheral(I2C_TypeDef *i2cx) {
	i2cx->CR1 |= I2C_REG_CR1_ENABLE_I2C;
}

static void hal_i2c_disable_peripheral(I2C_TypeDef *i2cx) {
	i2cx->CR1 &= ~I2C_REG_CR1_ENABLE_I2C;
}

static void hal_i2c_set_own_address1(I2C_TypeDef *i2cx, uint32_t own_address) {
	i2cx->OAR1 &= ~(0x7f << 1);
	i2cx->OAR1 |= (own_address << 1);
}

static void hal_i2c_manage_clock_stretch(I2C_TypeDef *i2cx, uint32_t no_stretch) {
	if (no_stretch) {
		i2cx->CR1 |= I2C_REG_CR1_NOSTRETCH;  // disabled clock stretching
	} else {
		i2cx->CR1 &= ~I2C_REG_CR1_NOSTRETCH;
	}
}

static void hal_i2c_configure_ccr(I2C_TypeDef *i2cx, uint32_t pclk, uint32_t clkspeed,
		uint32_t duty_cycle) {

	double Thigh, Tlow, Tpclk;
	uint32_t ccr;
	if (clkspeed <= 100000) {
		/* configure ccr for standard mode */
		ccr = (pclk * 1000000) / (clkspeed << 1);
	} else {
		if (duty_cycle == I2C_FM_DUTY_2) {
			ccr = (pclk * 1000000) / (3 * clkspeed);
		}
		if (duty_cycle == I2C_FM_DUTY_16BY9) {
			/* this is to reach 400khz in fm mode */
			ccr = (pclk * 1000000) / (25 * clkspeed);
		}
	}
	i2cx->CCR |= ccr;
}

static void hal_i2c_rise_time_configuration(I2C_TypeDef *i2cx, uint32_t freqrange,
		uint32_t ClockSpeed) {
	/*---------------------------- I2Cx TRISE Configuration --------------------*/
	/* Configure I2Cx: Rise Time */
	//  hi2c->Instance->TRISE = I2C_RISE_TIME(freqrange, hi2c->Init.ClockSpeed);
	uint32_t trise;
	if (ClockSpeed <= 100000) {
		trise = freqrange + 1;
	} else {
		trise = (((freqrange * 300) / 1000) + 1);
	}
	i2cx->TRISE &= ~(0x3F);
	i2cx->TRISE |= trise;
}

static void hal_i2c_clk_init(I2C_TypeDef *i2cx, uint32_t clkspeed, uint32_t duty_cycle) {
	uint32_t pclk = I2C_PERIPHERAL_CLK_FREQ_10MHZ;
	i2cx->CR2 &= ~(0x3F);
	i2cx->CR2 |= (0x3F & pclk);
	hal_i2c_rise_time_configuration(i2cx, pclk, clkspeed);
	hal_i2c_configure_ccr(i2cx, pclk, clkspeed, duty_cycle);
}

static void hal_i2c_set_addressing_mode(I2C_TypeDef *i2cx, uint32_t adr_mode) {
	if (adr_mode == I2C_ADDRMODE_10BI)
		i2cx->OAR1 |= I2C_REG_OAR1_ADDRMODE;
	else
		i2cx->OAR1 &= ~I2C_REG_OAR1_ADDRMODE;
}

static void hal_i2c_set_fm_mode_duty_cycle(I2C_TypeDef *i2cx, uint32_t duty_cycle) {
	if (duty_cycle == I2C_FM_DUTY_16BY9) {
		i2cx->CCR |= I2C_REG_CCR_DUTY;
	} else {
		i2cx->CCR &= ~I2C_REG_CCR_DUTY;
	}
}

void hal_i2c_manage_ack(I2C_TypeDef *i2cx, uint32_t ack_noack) {
	if (ack_noack == I2C_ACK_ENABLE)
		i2cx->CR1 |= I2C_REG_CR1_ACK;
	else
		i2cx->CR1 &= ~I2C_REG_CR1_ACK;
}

static void hal_i2c_generate_start_condition(I2C_TypeDef *i2cx) {
	i2cx->CR1 |= I2C_REG_CR1_START_GEN;
}

static void hal_i2c_generate_stop_condition(I2C_TypeDef *i2cx) {
	i2cx->CR1 |= I2C_REG_CR1_STOP_GEN;
}

static void hal_i2c_configure_tx_rx_interrupt(I2C_TypeDef *i2cx, uint32_t val) {
	if (val)
		i2cx->CR2 |= I2C_REG_CR2_BUF_INT_ENABLE;
	else
		i2cx->CR2 &= ~I2C_REG_CR2_BUF_INT_ENABLE;
}

static void hal_i2c_configure_error_interrupt(I2C_TypeDef *i2cx, uint32_t val) {
	if (val)
		i2cx->CR2 |= I2C_REG_CR2_ERR_INT_ENABLE;
	else
		i2cx->CR2 &= ~I2C_REG_CR2_ERR_INT_ENABLE;
}

static void hal_i2c_configure_evt_interrupt(I2C_TypeDef *i2cx, uint32_t val) {
	if (val)
		i2cx->CR2 |= I2C_REG_CR2_EVT_INT_ENABLE;
	else
		i2cx->CR2 &= ~I2C_REG_CR2_EVT_INT_ENABLE;
}

static uint8_t i2c_bus_busy(I2C_TypeDef *i2cx) {
	if (i2cx->SR2 & I2C_REG_SR2_BUS_BUSY_FLAG)
		return 1;
	else
		return 0;
}


/*
 * @brief wait for start condition
 */
static uint8_t i2c_wait_untill_sb_set(I2C_TypeDef *i2cx) {
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	if (i2cx->SR1 & I2C_REG_SR1_SB_FLAG) {
		return 1;
	}
	return 0;
}

static uint8_t i2c_wait_untill_addr_set(I2C_TypeDef *i2cx) {
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.

	if (i2cx->SR1 & I2C_REG_SR1_ADDR_SENT_FLAG) {
		return 1;
	}
	return 0;
}



/*
 *  @brief Initialize the given I2C
 *  @param *handle : Handle to the I2C Peripheral, which the application wants to initialize
 *  @retval None
 */
void hal_i2c_init(i2c_handle_t *handle) {
	hal_i2c_clk_init(handle->Instance, handle->Init.ClockSpeed,
			handle->Init.DutyCycle);

	hal_i2c_set_addressing_mode(handle->Instance, handle->Init.AddressingMode);

	hal_i2c_manage_ack(handle->Instance, handle->Init.ack_enable);

	hal_i2c_manage_clock_stretch(handle->Instance, handle->Init.NoStretchMode);

	hal_i2c_set_own_address1(handle->Instance, handle->Init.OwnAddress1);
}

void hal_i2c_send_addr_first(I2C_TypeDef *i2cx, uint8_t address) {

	i2cx->DR = address;

}

void clear_addr_flag(I2C_TypeDef *i2cx) {
	uint16_t val;

	val = i2cx->SR1;
	val = i2cx->SR2;

	UNUSED(val);  // prevent compiler warning
}


/*
 *  @brief API to do master data transmission
 *  @param *handle : Handle to the I2C Peripheral structure
 *  @param  slave_address : address to which we want to tx
 *  @param  *buffer : pointer to tx buffer
 *  @param  len : len of the data to be TX in bait
 *  @retval None
 */
void hal_i2c_master_tx(i2c_handle_t *handle, uint8_t slave_address,
		uint8_t *buffer, uint32_t len) {

	handle->pBuffPtr = buffer;
	handle->XferCount = len;
	handle->XferSize = len;
	handle->State = HAL_I2C_STATE_BUSY_TX;

	hal_i2c_enable_peripheral(handle->Instance);

	/* doesnt care for PE = 0 */
	while (i2c_bus_busy(handle->Instance))
		; //need to include timeout

	/* Disable Pos FEDOR: IS THIS really needed ??*/
	handle->Instance->CR1 &= ~I2C_CR1_POS;

	hal_i2c_generate_start_condition(handle->Instance);

	/* wait till sb is set */

	while (!i2c_wait_untill_sb_set(handle->Instance))
		;

	//clear_sb_flag(); ???

	hal_i2c_send_addr_first(handle->Instance, slave_address);

	while (!i2c_wait_untill_addr_set(handle->Instance))
		;

	clear_addr_flag(handle->Instance); // IS THIS really needed ?? FEDOR: Yes it need. It clear ADDR flag in SR1

	/* enable the buff, err , event interrupts */
	hal_i2c_configure_tx_rx_interrupt(handle->Instance, 1);
	hal_i2c_configure_error_interrupt(handle->Instance, 1);
	hal_i2c_configure_evt_interrupt(handle->Instance, 1);
}


/*
 *  @brief API to do master data reception
 *  @param *handle : Handle to the I2C Peripheral structure
 *  @param  slave_address : address from which we want to Rx
 *  @param  *buffer : pointer to Rx buffer
 *  @param  len : len of the data to be Rx in bait
 *  @retval None
 */
void hal_i2c_master_rx(i2c_handle_t *handle, uint8_t slave_addr,
		uint8_t *buffer, uint32_t len) {

	handle->pBuffPtr = buffer;
	handle->XferCount = len;
	handle->XferSize = len;
	handle->State = HAL_I2C_STATE_BUSY_RX;

	hal_i2c_enable_peripheral(handle->Instance);

	while (i2c_bus_busy(handle->Instance))
		;

	handle->Instance->CR1 &= ~I2C_CR1_POS;

	handle->Instance->CR1 |= I2C_CR1_ACK;

	hal_i2c_generate_start_condition(handle->Instance);

	/* wait till sb is set */

	while (!i2c_wait_untill_sb_set(handle->Instance))
		;

	//clear_sb_flag(); ???

	hal_i2c_send_addr_first(handle->Instance, slave_addr);

	while (!i2c_wait_untill_addr_set(handle->Instance))
		;

	clear_addr_flag(handle->Instance); // IS THIS really needed ?? FEDOR: Yes it need. It clear ADDR flag in SR1

	/* Enable the buff, err , event interrupts */
	hal_i2c_configure_tx_rx_interrupt(handle->Instance, 1);
	hal_i2c_configure_error_interrupt(handle->Instance, 1);
	hal_i2c_configure_evt_interrupt(handle->Instance, 1);
}


/*
 *  @brief API to do slave data transmission
 *  @param *handle : Handle to the I2C Peripheral structure
 *  @param  *buffer : pointer to tx buffer
 *  @param  len : len of the data to be TX in bait
 *  @retval None
 */
void hal_i2c_slave_tx(i2c_handle_t *handle, uint8_t *buffer, uint32_t len) {

	handle->pBuffPtr = buffer;
	handle->XferCount = len;
	handle->XferSize = len;

	handle->State = HAL_I2C_STATE_BUSY_TX;

	//while(i2c_bus_busy(handle->Instance) );

	handle->Instance->CR1 &= ~I2C_CR1_POS;

	hal_i2c_enable_peripheral(handle->Instance);

	/* Enable Address Acknowledge */
	handle->Instance->CR1 |= I2C_CR1_ACK;

	/* ENABLE the buff, err , event interrupts */
	hal_i2c_configure_tx_rx_interrupt(handle->Instance, 1);
	hal_i2c_configure_error_interrupt(handle->Instance, 1);
	hal_i2c_configure_evt_interrupt(handle->Instance, 1);
}


/*
 *  @brief API to do slave data reception
 *  @param *handle : Handle to the I2C Peripheral structure
 *  @param  *buffer : pointer to Rx buffer
 *  @param  len : len of the data to be Rx in bait
 *  @retval None
 */
void hal_i2c_slave_rx(i2c_handle_t *handle, uint8_t *buffer, uint32_t len) {
	handle->pBuffPtr = buffer;
	handle->XferCount = len;
	handle->XferSize = len;

	handle->State = HAL_I2C_STATE_BUSY_RX;

	uint32_t val;

	//while(12c_bus_busy(handle->Instance) );

	handle->Instance->CR1 &= ~I2C_CR1_POS;

	hal_i2c_enable_peripheral(handle->Instance);

	handle->Instance->CR1 |= I2C_CR1_ACK;

	/* disable the buff, err , event interrupts */
	hal_i2c_configure_tx_rx_interrupt(handle->Instance, 1);
	hal_i2c_configure_error_interrupt(handle->Instance, 1);
	hal_i2c_configure_evt_interrupt(handle->Instance, 1);

#if 0
	val = handle->Instance->CR2;
	val = handle->Instance->CR1;
	val = handle->Instance->OAR1;
#else
	UNUSED(val);
#endif
}







