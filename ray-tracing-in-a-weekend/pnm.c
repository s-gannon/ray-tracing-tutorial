#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "pnm.h"

#define RGB_MAX		255
#define FULL_ALPHA	255
#define SPACE     	' '
#define TAB       	'\t'
#define NEWLINE   	'\n'

#define DEBUG_STATEMENTS 0

int pnm_create_rgba(rgba_t* dest, uint32_t r, uint32_t g, uint32_t b, uint32_t a, uint32_t max_val){
	dest->r = round(((double)r / (double)max_val) * RGB_MAX);	//this should only round to at most 255
	dest->g = round(((double)g / (double)max_val) * RGB_MAX);
	dest->b = round(((double)b / (double)max_val) * RGB_MAX);
	dest->a = round(((double)a / (double)max_val) * RGB_MAX);

	if(dest->r > max_val)
		return 0;
	if(dest->g > max_val)
		return 0;
	if(dest->b > max_val)
		return 0;
	if(dest->a > max_val)
		return 0;
	return 1;
}

pnm_t pnm_init(char* path){
	pnm_t image;
	FILE* file = fopen(path, "r");
	uint32_t pixels_read = 0;

	if(file == NULL){
		perror("[ERROR] Opening file");
		exit(EXIT_FAILURE);
	}

	if(getc(file) != 'P'){
		fprintf(stderr, "[ERROR] Invalid header!\n");
		exit(EXIT_FAILURE);
	}

	int image_type = getc(file) - '0';	//char '1' is 49 in decimal, so subtract by '0'
	if(image_type < 1 || image_type > 7){
		fprintf(stderr, "[ERROR] Invalid image type!\n");
		exit(EXIT_FAILURE);
	}
	image.type = image_type;	//can use a switch for all 7 different types

	getc(file);	//throw away the next whitespace char
	fscanf(file, "%d", &image.width);
	fscanf(file, "%d", &image.height);
	fscanf(file, "%c", &image.max_val);

	image.data = calloc((image.width * image.height), sizeof(rgba_t));
	
	switch(image.type){	//todo: change from switch to if - else if - else
		case 1:{	//pbm, bitmap with only white and black pixels
			const rgba_t COL_WHITE = (rgba_t){
				.r = RGB_MAX, 
				.g = RGB_MAX, 
				.b = RGB_MAX, 
				.a = FULL_ALPHA
			};
			const rgba_t COL_BLACK = (rgba_t){
				.r = 0, 
				.g = 0, 
				.b = 0, 
				.a = FULL_ALPHA
			};

			int stop_read = 0;

			while(!stop_read){
				char input;
				switch(input = getc(file)){
					case '0':{
						if(DEBUG_STATEMENTS)
							fprintf(
								stdout, 
								"[DEBUG] Reading pixel %d...\n", 
								pixels_read
							);
						image.data[pixels_read++] = COL_WHITE;
						if(DEBUG_STATEMENTS)
							fprintf(
								stdout, 
								"[DEBUG] Pixel %d read successfully!\n", 
								pixels_read - 1
							);
						break;
					}
					case '1':{
						if(DEBUG_STATEMENTS)
							fprintf(
								stdout, 
								"[DEBUG] Reading pixel %d...\n", 
								pixels_read
							);
						image.data[pixels_read++] = COL_BLACK;
						if(DEBUG_STATEMENTS)
							fprintf(
								stdout, 
								"[DEBUG] Pixel %d read successfully!\n", 
								pixels_read - 1
							);
						break;
					}
					case SPACE:
					case TAB:
					case NEWLINE:{
						break;	//just skip the whitespace characters
					}
					case EOF:{
						stop_read = 1;	//end the loop
						break;
					}
					default:{
						fprintf(
							stderr, 
							"[ERROR] Invalid character read in file!\n"
						);
						fprintf(
							stderr, 
							"Character: %c (%d)\n",
							input,
							input
						);
						exit(EXIT_FAILURE);

						break;
					}
				}
			}
		
			break;
		}
		case 2:{	//black and white image
			int input;

			while((fscanf(file, "%d", &input)) != EOF){
				if(DEBUG_STATEMENTS)
					fprintf(
						stdout, 
						"[DEBUG] Reading pixel %d...\n", 
						pixels_read
					);
				if(input > image.max_val){
					fprintf(
						stderr,
						"[ERROR] Value is larger than the max value!\n"
					);
					fprintf(stderr,"Value: %d\n", input);
					exit(EXIT_FAILURE);
				}
				int ret_value = pnm_create_rgba(
					&image.data[pixels_read++], 
					input, 
					input, 
					input, 
					FULL_ALPHA, 
					image.max_val
				);

				if(ret_value){
					if(DEBUG_STATEMENTS)
						fprintf(
							stdout, 
							"[DEBUG] Pixel %d read successfully!\n",
							pixels_read - 1
						);
				}
				else{
					fprintf(
						stderr, 
						"[ERROR] Error reading P2 image data!\n"
					);
					exit(EXIT_FAILURE);
				}
			}

			if(pixels_read != (image.width * image.height)){
				fprintf(
					stderr, 
					"[ERROR] Number of pixels read is invalid!\n"
				);
				fprintf(stderr, "Number read: %d\n", pixels_read);
				fprintf(
					stderr,
					"Dimensions : %d by %d (%d pixels)\n",
					image.width,
					image.height,
					image.width * image.height
				);
				exit(EXIT_FAILURE);
			}

			break;
		}
		case 3:{	//standard RGB image
			int input;
			uint32_t col_val = 0;
			uint32_t temp_rgb[3];

			while((fscanf(file, "%d", &input)) != EOF){
				if(DEBUG_STATEMENTS)
					fprintf(
						stdout, 
						"[DEBUG] Reading pixel %d...\n", 
						pixels_read
					);
				if(input > image.max_val){
					fprintf(
						stderr,
						"[ERROR] Value is larger than the max value!\n"
					);
					fprintf(stderr,"Value: %d\n", input);
					exit(EXIT_FAILURE);
				}
				
				if(col_val == 0 || col_val == 1)
					temp_rgb[col_val++] = input;
				else if(col_val == 2){
					temp_rgb[col_val] = input;
					col_val = 0;	//reset col_val to 0 for the next RGB set

					pnm_create_rgba(
						&image.data[pixels_read++], 
						temp_rgb[0], 
						temp_rgb[1], 
						temp_rgb[2], 
						FULL_ALPHA, 
						image.max_val
					);

					if(DEBUG_STATEMENTS)
						fprintf(
							stdout, 
							"[DEBUG] Pixel %d read successfully!\n",
							pixels_read - 1
						);
				}
				else{
					fprintf(
						stderr, 
						"[ERROR] Error reading P3 image data!\n"
					);
					exit(EXIT_FAILURE);
				}
			}

			if(pixels_read != (image.width * image.height)){
				fprintf(
					stderr, 
					"[ERROR] Number of pixels read is invalid!\n"
				);
				fprintf(stderr, "Number read: %d\n", pixels_read);
				fprintf(
					stderr,
					"Dimensions : %d by %d (%d pixels)\n",
					image.width,
					image.height,
					image.width * image.height
				);
				exit(EXIT_FAILURE);
			}

			break;
		}
		case 4:{
			fprintf(
				stderr,
				"[ERROR] P4 file type not supported!\n"
			);
			exit(EXIT_FAILURE);

			break;
		}
		case 5:{
			fprintf(
				stderr,
				"[ERROR] P5 file type not supported!\n"
			);
			exit(EXIT_FAILURE);

			break;
		}
		case 6:{
			fprintf(
				stderr,
				"[ERROR] P6 file type not supported!\n"
			);
			exit(EXIT_FAILURE);

			break;
		}
		case 7:{
			fprintf(
				stderr,
				"[ERROR] P7 file type not supported!\n"
			);
			exit(EXIT_FAILURE);

			break;
		}
		default:{
			fprintf(
				stderr, 
				"[ERROR] Invalid image type passed!\n"
			);
			fprintf(
				stderr, 
				"Image type value: %d\n", 
				image.type
			);
			exit(EXIT_FAILURE);
			
			break;
		}
	}

	return image;
}
