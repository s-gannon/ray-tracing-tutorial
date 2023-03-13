#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "vec3.h"

vec3_t vec3_init(vec3_t* dest, double _x, double _y, double _z){
	//if the vec3 pointer `vec` is not NULL
	if(dest){
		dest->x = _x;
		dest->y = _y;
		dest->z = _z;

		return *dest;	//avoids performing instructions again
	}
	return (vec3_t){.x = _x, .y = _y, .z = _z};
}
//	unary arithmetic
vec3_t vec3_negate(vec3_t* dest, vec3_t vec){
	if(dest){
		dest->x *= -1;
		dest->y *= -1;
		dest->z *= -1;

		return *dest;
	}

	return (vec3_t){
		.x = -1 * vec.x,
		.y = -1 * vec.y,
		.z = -1 * vec.z
	};
}
//	binary arithmetic
vec3_t vec3_add(vec3_t* dest, vec3_t u, vec3_t v){
	//if the vec3 pointer `dest` is not NULL
	if(dest){
		dest->x = u.x + v.x;
		dest->y = u.y + v.y;
		dest->z = u.z + v.z;

		return *dest;	//avoids performing instructions again
	}
	return (vec3_t){
		.x = u.x + v.x,
		.y = u.y + v.y,
		.z = u.z + v.z
	};
}
void vec3_add_eq(vec3_t* u, vec3_t v){
	if(!u){	//check for NULL pointer error
		return;
	}

	u->x += v.x;
	u->y += v.y;
	u->z += v.z;

	return;
}

vec3_t vec3_sub(vec3_t* dest, vec3_t u, vec3_t v){
	//if the vec3 pointer `dest` is not NULL
	if(dest){
		dest->x = u.x - v.x;
		dest->y = u.y - v.y;
		dest->z = u.z - v.z;

		return *dest;	//avoids performing instructions again
	}
	return (vec3_t){
		.x = u.x - v.x,
		.y = u.y - v.y,
		.z = u.z - v.z
	};
}
void vec3_sub_eq(vec3_t* u, vec3_t v){
	if(!u){	//check for NULL pointer error
		return;
	}

	u->x -= v.x;
	u->y -= v.y;
	u->z -= v.z;

	return;
}

vec3_t vec3_mul(vec3_t* dest, vec3_t vec, double scalar){
	//if the vec3 pointer `dest` is not NULL
	if(dest){
		dest->x = scalar * vec.x;
		dest->y = scalar * vec.y;
		dest->z = scalar * vec.z;

		return *dest;	//avoids performing instructions again
	}
	return (vec3_t){
		.x = scalar * vec.x,
		.y = scalar * vec.y,
		.z = scalar * vec.z
	};
}
void vec3_mul_eq(vec3_t* vec, double scalar){
	if(!vec){	//check for NULL pointer error
		return;
	}

	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;

	return;
}

vec3_t vec3_div(vec3_t* dest, vec3_t vec, double scalar){
	//if the vec3 pointer `dest` is not NULL
	double inverse = (1 / scalar);
	vec3_t vector;

	if(dest){
		return vec3_mul(dest, vec, inverse);
	}
	
	return vec3_mul(NULL, vec, inverse);
}
void vec3_div_eq(vec3_t* vec, double scalar){
	if(!vec){	//check for NULL pointer error
		return;
	}

	double inverse = (1 / scalar);
	vec3_mul_eq(vec, scalar);

	return;
}
//	additional math functions
double vec3_length_squared(vec3_t vec){
	return vec3_dot_prod(vec, vec);
}

double vec3_length(vec3_t vec){
	return sqrt(length_squared(vec));
}

double* vec3_to_arr(vec3_t vec){
	return (double[3]){vec.x, vec.y, vec.z};
}

void vec3_print(vec3_t vec){
	printf("<%d, %d, %d>\n", vec.x, vec.y, vec.z);
}

double vec3_dot_prod(vec3_t u, vec3_t v){
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

vec3_t vec3_cross_prod(vec3_t* dest, vec3_t u, vec3_t v){
	if(dest){
		dest->x = (u.y * v.z) - (u.z * v.y);
		dest->y = (u.z * v.x) - (u.x * v.z);
		dest->z = (u.x * v.y) - (u.y * v.x);

		return *dest;
	}

	return (vec3_t){
		.x = (u.y * v.z) - (u.z * v.y),
		.y = (u.z * v.x) - (u.x * v.z),
		.z = (u.x * v.y) - (u.y * v.x)
	};
}

vec3_t vec3_normalize(vec3_t* dest, vec3_t vec){
	double magnitude;

	if(dest){
		magnitude = vec3_length(*dest);

		dest->x /= magnitude;
		dest->y /= magnitude;
		dest->z /= magnitude;

		return *dest;
	}

	magnitude = vec3_length(vec);

	return (vec3_t){
		.x = (vec.x / magnitude),
		.y = (vec.y / magnitude),
		.z = (vec.z / magnitude)
	};
}
