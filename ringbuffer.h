/*
 * ringbuffer.h
 *
 *  Created on: Jun 2, 2025
 *      Author: jsanchez
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define RING_BUFFER_SIZE 255

typedef struct ring_buffer
{
	uint8_t buffer[RING_BUFFER_SIZE];
	uint8_t head;
	uint8_t tail;
}RingBufferTypeDef;

void rbuffer_init(RingBufferTypeDef *rb);

int rbuffer_isavailable(RingBufferTypeDef* rb);
int rbuffer_read(RingBufferTypeDef* rb);
void rbuffer_write(RingBufferTypeDef* rb, uint8_t c);
int rbuffer_read_bytes(RingBufferTypeDef* rb, uint8_t*data, uint16_t size);
void rbuffer_write_bytes(RingBufferTypeDef* rb, uint8_t*data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFFER_H_ */
