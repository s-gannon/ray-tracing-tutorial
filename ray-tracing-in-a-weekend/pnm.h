#ifndef PNM_H
#define PNM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
Returns true if successful, returns false if there was an issue
*/
bool pnm_create_rgba(rgba_t* dest, uint16_t r, uint16_t g, uint16_t b, uint16_t a, uint16_t max_val);

pnm_t pnm_init(char* path);

#endif
