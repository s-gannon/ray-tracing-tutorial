#ifndef PNM_H
#define PNM_H

// includes

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// structures

typedef struct rgba_s{
	uint8_t r, g, b, a;
} rgba_t;

typedef struct pnm_s{
	uint8_t type: 3;	//type only needs 3 bits because PNM types; only 1 to 7
	uint16_t max_val;
	uint32_t width, height;		
	rgba_t* data;
} pnm_t;
/*
Creates an rgba_t struct given R, G, B, and A as well as the maximum value
Returns 1 if successful, returns 0 if there was an issue
*/
int pnm_create_rgba(rgba_t* dest, uint32_t r, uint32_t g, uint32_t b, uint32_t a, uint32_t max_val);

pnm_t pnm_init(char* path);

#endif
