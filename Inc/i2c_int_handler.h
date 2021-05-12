/*
 * i2c_int_handler.h
 *
 *  Created on: 12 мая 2021 г.
 *      Author: User
 */

#ifndef I2C_INT_HANDLER_H_
#define I2C_INT_HANDLER_H_


/*
 * Include
 */

#include <stdint.h>
#include "i2c_driver.h"
#include "gpio_driver.h"
#include "stm32f2xx.h"  /* include MCU  specific header*/


/**
  * @brief  Handle TXE flag for Master
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_MasterTransmit_TXE(i2c_handle_t *hi2c);


/**
  * @brief  Memory Tx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
void HAL_I2C_MemTxCpltCallback(i2c_handle_t *hi2c);


 /**
   * @brief  Master Tx Transfer completed callbacks.
   * @param  hi2c: pointer to a i2c_handle_t structure that contains
   *         the configuration information for I2C module
   * @retval None
   */
void HAL_I2C_MasterTxCpltCallback(i2c_handle_t *hi2c);


/**
  * @brief  Master Tx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
  void HAL_I2C_MasterTxCpltCallback(i2c_handle_t *hi2c);


/**
  * @brief  Memory Rx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
 void HAL_I2C_MemRxCpltCallback(i2c_handle_t *hi2c);


/**
  * @brief  Slave Rx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
 void HAL_I2C_SlaveRxCpltCallback(i2c_handle_t *hi2c);


/** @brief  Slave Tx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
  void HAL_I2C_SlaveTxCpltCallback(i2c_handle_t *hi2c);


/**
  * @brief  Master Rx Transfer completed callbacks.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
 void HAL_I2C_MasterRxCpltCallback(i2c_handle_t *hi2c);


/**
  * @brief  Handle BTF flag for Master transmitter
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval nope
  */
static void I2C_MasterTransmit_BTF(i2c_handle_t *hi2c);


/**
  * @brief  Handle BTF flag for Master receiver
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_MasterReceive_BTF(i2c_handle_t *hi2c);


/**
  * @brief  Handle ADD flag for Slave
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_Slave_ADDR(i2c_handle_t *hi2c);

void hal_clear_stop_flag(i2c_handle_t *hi2c);


/**
  * @brief  Handle STOPF flag for Slave
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_Slave_STOPF(i2c_handle_t *hi2c);


/**
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_Slave_AF(i2c_handle_t *hi2c);


/**
  * @brief  Handle TXE flag for Slave
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_SlaveTransmit_TXE(i2c_handle_t *hi2c);


/**
  * @brief  Handle BTF flag for Slave transmitter
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_SlaveTransmit_BTF(i2c_handle_t *hi2c);


/**
  * @brief  Handle RXNE flag for Master
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_MasterReceive_RXNE(i2c_handle_t *hi2c);


/**
  * @brief  Handle BTF flag for Slave receiver
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_SlaveReceive_BTF(i2c_handle_t *hi2c);


/**
  * @brief  Handle RXNE flag for Slave
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
static void I2C_SlaveReceive_RXNE(i2c_handle_t *hi2c);


/**
  * @brief  This function handles I2C event interrupt request.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
void HAL_I2C_EV_IRQHandler(i2c_handle_t *hi2c);


/**
  * @brief  I2C error callbacks
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_I2C_ErrorCallback(i2c_handle_t *I2cHandle);


/**
  * @brief  This function handles I2C error interrupt request.
  * @param  hi2c: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval HAL status
  */
void HAL_I2C_ER_IRQHandler(i2c_handle_t *hi2c);



#endif /* I2C_INT_HANDLER_H_ */
