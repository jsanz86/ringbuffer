/*
 * serial.h
 *
 *  Created on: Aug 7, 2025
 *      Author: jsanchez
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "main.h"
#include "stm32_adv_trace.h"
#include "usart.h"
#include "usart_if.h"
#include "dma.h"
#include "ringbuffer.h"


typedef struct serial_com
{
	UART_HandleTypeDef *huart;
	RingBufferTypeDef *rx_buffer;
	RingBufferTypeDef *tx_buffer;
	int (*Available)( void );
	int (*Read)( void );
	int (*Read_Bytes)(uint8_t *data, uint16_t size);
	void (*Write)(uint8_t c);
	void (*Write_Bytes)(uint8_t *data, uint16_t size);
	void (*Send)( void );

}Serial_TypeDef;


extern uint8_t charRx_serial1;

extern RingBufferTypeDef 	rx_buffer_dbg;
extern RingBufferTypeDef 	tx_buffer_dbg;

extern RingBufferTypeDef 	rx_buffer_serial1;
extern RingBufferTypeDef 	tx_buffer_serial1;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

extern Serial_TypeDef SerialDBG;
extern Serial_TypeDef Serial1;

extern uint8_t uart_ready;

#define SerialPrint(...) 	do{ {UTIL_ADV_TRACE_COND_FSend(VLEVEL_L, T_REG_OFF, TS_OFF, __VA_ARGS__);} }while(0);


#define SerialPrintLn(...)	do{ {UTIL_ADV_TRACE_COND_FSend(VLEVEL_L, T_REG_OFF, TS_OFF, __VA_ARGS__);}\
								 {UTIL_ADV_TRACE_COND_FSend(VLEVEL_L, T_REG_OFF, TS_OFF, "\r\n");}\
								 }while(0);

void Serial_Setup(void);


int Serial_isAvailable( void );
int Serial_Read( void );
int Serial_Read_Bytes(uint8_t*data, uint16_t size);
void Serial_Write_Bytes(uint8_t*data, uint16_t size);
void Serial_Write(uint8_t c);
void Serial_Send( void );


int Serial1_isAvailable( void );
int Serial1_Read( void );
int Serial1_Read_Bytes(uint8_t *data, uint16_t size);
void Serial1_Write(uint8_t c);
void Serial1_Write_Bytes(uint8_t *data, uint16_t size);
void Serial1_Send( void );
void Serial1_SetTimeout( uint32_t timeout);

#endif /* SERIAL_H_ */
