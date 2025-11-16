#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

//this function was contributed to by James Hall from the FreeDOS project
//and modified for this project
//BUG: does not handle leading trailing whitespace
int test_double(char *str){
        /*str is a tring
        n is number of characters to test*/
        /*use strlen-1 for n if it has a '\n' in it
        else use strlen*/
        //checks if str is a valid double
        /*returns 0 if it is not a valid double, 1 if it is valid
        and -1 if an error occurred*/
        unsigned short dec_cnt = 0;
        char *ptr = str;

        //check for NULL pointer
        if(str == NULL){
                fprintf(stderr, "bool test_double(char *str, size_t): Error: ");
                fprintf(stderr, "str is a NULL pointer\n");
                return -1; //non-critical error
        }

        if(ptr[0] == '-') ptr++; //next position in pointer

        while((ptr[0] != '\0') && (ptr[0] != '\n')){
        	if(ptr[0] == '.'){
                	if(++dec_cnt > 1)
                        	return 0;
                }
        	else if((ptr[0] < '0') || (ptr[0] > '9'))
                	return 0;

                ptr++;
        }
        return 1;
}

double min(double *ptr, unsigned int n){
	//calculate minimum value of an array
	//returns minimum
	double m = ptr[0];

	for(unsigned int i = 0; i < n; i++)
		if(ptr[i] < m) m = ptr[i];
	return m;
}

double max(double *ptr, unsigned int n){
        //calculate maximum value of an array
        //returns maximum
        double m = ptr[0];

        for(unsigned int i = 0; i < n; i++)
                if(ptr[i] > m) m = ptr[i];
        return m;
}

