#ifndef VEC3_H
#define VEC3_H
//	includes
#include <stdarg.h>
//	defines
#define VEC_SIZE 3
//	structs
typedef struct vec3_s{
	double x, y, z;
}vec3_t;
//	constructor/initializer
vec3_t vec3_init(vec3_t* dest, double _x, double _y, double _z);
//	unary arithmetic
vec3_t vec3_negate(vec3_t* dest, vec3_t vec);
//	binary arithmetic
vec3_t vec3_add(vec3_t* dest, vec3_t u, vec3_t v);
void vec3_add_eq(vec3_t* u, vec3_t v);
vec3_t vec3_sub(vec3_t* dest, vec3_t u, vec3_t v);
void vec3_sub_eq(vec3_t* u, vec3_t v);
vec3_t vec3_mul(vec3_t* dest, vec3_t vec, double scalar);
void vec3_mul_eq(vec3_t* vec, double scalar);
vec3_t vec3_div(vec3_t* dest, vec3_t vec, double scalar);
void vec3_div_eq(vec3_t* vec, double scalar);
//	additional math functions
double vec3_length_squared(vec3_t vec);

double vec3_length(vec3_t vec);
//	utility functions
double* vec3_to_arr(vec3_t vec);

void vec3_print(vec3_t vec);

double vec3_dot_prod(vec3_t u, vec3_t v);

vec3_t vec3_cross_prod(vec3_t* dest, vec3_t u, vec3_t v);

vec3_t vec3_normalize(vec3_t* dest, vec3_t vec);

#endif
