/*
 * ringbuffer.c
 *
 *  Created on: Jun 2, 2025
 *      Author: jsanchez
 */

#include "ringbuffer.h"

#include "main.h"
#include "string.h"
#include "stm32_adv_trace.h"

void rbuffer_init(RingBufferTypeDef *rb)
{
	memset(rb->buffer, 0, RING_BUFFER_SIZE);
	rb->head = 0;
	rb->tail = 0;
}

int rbuffer_isavailable(RingBufferTypeDef* rb)
{
	return (RING_BUFFER_SIZE + rb->head - rb->tail) % RING_BUFFER_SIZE;
}

int rbuffer_read(RingBufferTypeDef* rb)
{

	// if the head isn't ahead of the tail, we don't have any characters
	if (rb->head == rb->tail) {

		return 0;
	} else {

		char c = rb->buffer[rb->tail];
		rb->tail = (uint8_t)(rb->tail + 1) % RING_BUFFER_SIZE;

		return c;
	}

}

void rbuffer_write(RingBufferTypeDef* rb, uint8_t c)
{


	if (((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail) {
		rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;  // Move tail forward (overwrite)
	}

	rb->buffer[rb->head] = c;
	rb->head = (rb->head + 1) % RING_BUFFER_SIZE;



}

int rbuffer_read_bytes(RingBufferTypeDef* rb, uint8_t* data, uint16_t size)
{
	uint32_t tick = HAL_GetTick();
	int i = 0;

	do {
		// if the head isn't ahead of the tail, we don't have any characters
		if (rbuffer_isavailable(rb)) {
			char c = rb->buffer[rb->tail];
			rb->tail = (uint8_t)(rb->tail + 1) % RING_BUFFER_SIZE;
			data[i] = c;
			i++;
			if (i == size) {

				return i;
			}
		}

	}while (HAL_GetTick() - tick < 1000);


	return i = 0;
}

void rbuffer_write_bytes(RingBufferTypeDef* rb, uint8_t*data, uint16_t size){

	int i = 0;
	for(i = 0 ; i < size; i++) {

		if (((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail) {
				rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;  // Move tail forward (overwrite)
		}
		rb->buffer[rb->head] = data[i];
		rb->head = (rb->head + 1) % RING_BUFFER_SIZE;

	}
}
