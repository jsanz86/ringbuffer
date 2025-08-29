/*
 * serial.c
 *
 *  Created on: Aug 7, 2025
 *      Author: jsanchez
 */



#include "usart_if.h"
#include "main.h"
#include "stdio.h"
#include "sys_app.h"
#include "stm32_lpm.h"
#include "stm32_lpm_if.h"
#include "stdint.h"
#include "sys_conf.h"
#include "stm32_adv_trace.h"
#include "serial.h"

extern uint8_t charRx;
uint8_t charRx_serial1;

RingBufferTypeDef 	rx_buffer_dbg;
RingBufferTypeDef 	tx_buffer_dbg;

RingBufferTypeDef 	rx_buffer_serial1;
RingBufferTypeDef 	tx_buffer_serial1;


extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;

Serial_TypeDef SerialDBG ;
Serial_TypeDef Serial1 ;

uint8_t uart_ready = 1;

void Serial_Setup (void) {

	UART_WakeUpTypeDef WakeUpSelection;

	/*Set wakeUp event on start bit*/
	WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_STARTBIT;

	/*initialize serial debug buffer */
	SerialDBG.huart = &huart2;
	SerialDBG.tx_buffer = &tx_buffer_dbg;
	rbuffer_init(SerialDBG.tx_buffer);

	SerialDBG.rx_buffer = &rx_buffer_dbg;
	rbuffer_init(SerialDBG.rx_buffer);

	SerialDBG.Available = &Serial_isAvailable;
	SerialDBG.Read = &Serial_Read;
	SerialDBG.Read_Bytes = &Serial_Read_Bytes;
	SerialDBG.Write = &Serial_Write;
	SerialDBG.Write_Bytes = &Serial_Write_Bytes;
	SerialDBG.Send = &Serial_Send;

	HAL_UARTEx_StopModeWakeUpSourceConfig(SerialDBG.huart, WakeUpSelection);
	/* Enable USART interrupt */
	__HAL_UART_ENABLE_IT(SerialDBG.huart, UART_IT_WUF);
	/*Enable wakeup from stop mode*/

	HAL_UARTEx_EnableStopMode(SerialDBG.huart);
	HAL_UART_Receive_IT(SerialDBG.huart, &charRx, 1);

	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_26);

	/*initialize serial GEM buffer */
	Serial1.huart = &huart1;
	Serial1.tx_buffer = &tx_buffer_serial1;
	rbuffer_init(Serial1.tx_buffer);

	Serial1.rx_buffer = &rx_buffer_serial1;
	rbuffer_init(Serial1.rx_buffer);

	Serial1.Available = &Serial1_isAvailable;
	Serial1.Read = &Serial1_Read;
	Serial1.Read_Bytes = &Serial1_Read_Bytes;
	Serial1.Write = &Serial1_Write;
	Serial1.Write_Bytes = &Serial1_Write_Bytes;
	Serial1.Send = &Serial1_Send;

	HAL_UARTEx_StopModeWakeUpSourceConfig(Serial1.huart, WakeUpSelection);
	/* Enable USART interrupt */
	__HAL_UART_ENABLE_IT(Serial1.huart, UART_IT_WUF);
	/*Enable wakeup from stop mode*/

	HAL_UARTEx_EnableStopMode(Serial1.huart);

	HAL_UART_Receive_IT(Serial1.huart, &charRx_serial1, 1);

}


int Serial_isAvailable( void )
{
	return rbuffer_isavailable(SerialDBG.rx_buffer);
}

int Serial_Read( void )
{
	return rbuffer_read(SerialDBG.rx_buffer);
}

int Serial_Read_Bytes(uint8_t *data, uint16_t size)
{
	return rbuffer_read_bytes(SerialDBG.rx_buffer, data, size);
}

void Serial_Write(uint8_t c)
{
	rbuffer_write(SerialDBG.tx_buffer, c);
}

void Serial_Write_Bytes(uint8_t *data, uint16_t size)
{
	rbuffer_write_bytes(SerialDBG.tx_buffer, data, size);
}

void Serial_Send( void )
{

}

/** 		SERIAL GEM 		**/


int Serial1_isAvailable( void )
{
	return rbuffer_isavailable(Serial1.rx_buffer);
}

int Serial1_Read( void )
{
	return rbuffer_read(Serial1.rx_buffer);
}

int Serial1_Read_Bytes(uint8_t *data, uint16_t size)
{
	return rbuffer_read_bytes(Serial1.rx_buffer, data, size);
}

void Serial1_Write(uint8_t c)
{
	rbuffer_write(Serial1.tx_buffer, c);
}

void Serial1_Write_Bytes(uint8_t *data, uint16_t size)
{
	rbuffer_write_bytes(Serial1.tx_buffer, data, size);
}

void Serial1_Send( void )
{
	uint8_t data[255];
	uint16_t size = (RING_BUFFER_SIZE + Serial1.tx_buffer->head - Serial1.tx_buffer->tail) % RING_BUFFER_SIZE;

	rbuffer_read_bytes(Serial1.tx_buffer, data, size);

	HAL_UART_Transmit(Serial1.huart, data, size, 1000);
}


void Serial1_SetTimeout( uint32_t timeout){

}
/** 	END SERIAL GEM				**/
