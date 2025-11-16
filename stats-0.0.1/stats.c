#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
#include "misc.h"
#include "stats.h"

Stat* creat_stat(){
	//create a Stat structure (holds stats calculations for a tble)
  	//returns Stat* on success or NULL on failure
	Stat *ptr = (Stat*)malloc(sizeof(Stat));

	//test error message
	//free(ptr);
	//ptr = NULL;

	if(ptr == NULL){
		fprintf(stderr, "\nstats.c:Stats* creat_stats(): ");
		fprintf(stderr, "Error:ptr is a NULL pointer\n\n");
		return NULL;
	}

	ptr->tbl = creat_table();
	
	//test error message
	//free_table(&ptr->tbl);
        //ptr->tbl = NULL;

	if(ptr->tbl == NULL){
		free(ptr);
		ptr = NULL; 
		return NULL;
	}

	//set values to 0
	ptr->n = 0;
        ptr->meanx = 0.0;
        ptr->sumx = 0.0;
        ptr->sumx2 = 0.0;
        ptr->ox = 0.0;
        ptr->ox2 = 0.0;
        ptr->sx = 0.0;
        ptr->sx2 = 0.0;
        ptr->meany = 0.0;
        ptr->sumy = 0.0;
        ptr->sumy2 = 0.0;
        ptr->oy = 0.0;
        ptr->oy2 = 0.0;
        ptr->sy = 0.0;
        ptr->sy2 = 0.0;
        ptr->sumxy = 0.0;
	ptr->minx = 0.0;
        ptr->maxx = 0.0;
        ptr->miny = 0.0;
        ptr->maxy = 0.0;


	//debug mode when DEBUG = 1 in debug.h
	#if DEBUG
	printf("stat was created\n");
	getchar(); //enter any charcter to continue
	#endif

	return ptr;
}

int free_stat(Stat **ptr){
	//free Stat structure (inluding the Table instance in it)
	//returns 0 on success or 1 on error

	//test error message
	//free_table(&(*ptr)->tbl);
	//free(*ptr);
        //ptr = NULL;


	if((ptr == NULL) || (*ptr == NULL)){
		fprintf(stderr, "\nstats.c:Stats* creat_stats(): ");
		fprintf(stderr, "Error:ptr or *ptr is a NULL pointer\n\n");
		return 1;
	}
	free_table(&(*ptr)->tbl);
	free(*ptr);
	*ptr = NULL;

	//debug mode when DEBUG = 1 in debug.h
        #if DEBUG
	printf("stat was freed\n");
	getchar(); //enter any character to continue
	#endif

	return 0;
}

int calc_stat(Stat **ptr){
	//calculate stats of (*ptr)->tbl
	//returns 0 on success or 1  on error

	//have to calculates stats out of order of structure and order printed

	//check error message
	//free_stat(ptr);
	//*ptr = NULL;

	//check for NULL pointers
	if((ptr == NULL) || (*ptr == NULL)){
		fprintf(stderr, "\nstats.c:int calc_stats(Stat **ptr): Error:");
		fprintf(stderr, "ptr or *ptr is a NULL pointer\n\n");
		return 1;
	}

	(*ptr)->n = (*ptr)->tbl->next;

	Table *temp = creat_table(); //to hold values for x[i] - meanx 
	//and y[i] - meany
	double sum_tempx = 0.0, sum_tempy = 0.0; //sum the x and y values in Table temp

	for(unsigned int i = 0; i < (*ptr)->n; i++){
		(*ptr)->sumx += (*ptr)->tbl->x[i];         //sumx
		(*ptr)->sumx2 += pow((*ptr)->tbl->x[i],2); //sumx2
		(*ptr)->sumy += (*ptr)->tbl->y[i];         //sumy
                (*ptr)->sumy2 += pow((*ptr)->tbl->y[i],2); //sumy2
		(*ptr)->sumxy += (*ptr)->tbl->x[i] * (*ptr)->tbl->y[i]; //sumxy
	}

	(*ptr)->meanx = (*ptr)->sumx / (*ptr)->n;
	(*ptr)->meany = (*ptr)->sumy / (*ptr)->n;

	//create table to hold x[i] - meanx & y[i] - meany
	for(unsigned int i = 0; i < (*ptr)->n; i++)
		uinsert_end(&temp, pow((*ptr)->tbl->x[i] - (*ptr)->meanx, 2), pow((*ptr)->tbl->y[i] - (*ptr)->meany, 2));

	//sum valuse of x & y in Table temp
	for(unsigned int i = 0; i < (*ptr)->n; i++){
		sum_tempx += temp->x[i];
		sum_tempy += temp->y[i];
	}

	//debug mmode when DEBUG = 1 in debug.h
	#if DEBUG
	//debug print temp table & sum_tempx & sum_tempy
	strcpy(temp->name, "temp\n"); //table has to have a name or print_table() will exit on error
        print_table(temp);
	printf("sum_tempx = %f\n", sum_tempx);
	printf("sum_tempy = %f\n", sum_tempy);
	getchar(); //enter any character to continue
	#endif

	free_table(&temp); //free temp Table. no longer needed adter this

	//ox, sx, oy and sy don't take sqrt of ox2, sx2, oy2 and sy2
	//full calculation on their own to avoid rounding errors
	(*ptr)->ox = sqrt(sum_tempx / (*ptr)->n);
	(*ptr)->ox2 = sum_tempx / (*ptr)->n;
	(*ptr)->sx =  sqrt(sum_tempx / ((*ptr)->n - 1));
	(*ptr)->sx2 = sum_tempx / ((*ptr)->n - 1);
	(*ptr)->oy = sqrt(sum_tempy / (*ptr)->n);
	(*ptr)->oy2 = sum_tempy / (*ptr)->n;
	(*ptr)->sy = sqrt(sum_tempy / ((*ptr)->n - 1));
	(*ptr)->sy2 = sum_tempy / ((*ptr)->n - 1);

	//calculate min & max of x & y
	(*ptr)->minx = min((*ptr)->tbl->x, (*ptr)->n);
	(*ptr)->miny = min((*ptr)->tbl->y, (*ptr)->n);
	(*ptr)->maxx = max((*ptr)->tbl->x, (*ptr)->n);
	(*ptr)->maxy = max((*ptr)->tbl->y, (*ptr)->n);
	return 0;
}
int print_stat(Stat *ptr){
	//print stats for (*ptr)->tbl
	//returns 0 on success or 1 on failure

	//test error message
	//free_stat(&ptr);
	//ptr = NULL;

	//chck for NULL pointers
	 if((ptr == NULL)){
                fprintf(stderr, "\nstats.c:int print_stats(Stat *ptr): Error:");
                fprintf(stderr, "ptr is a NULL pointer\n\n");
                return 1;
        }

	printf("\nn=%u\n", ptr->n);
        printf("mean x=%15.8E\n", ptr->meanx);
        printf("sum x=%15.8E\n", ptr->sumx);
        printf("sum x2=%15.8E\n", ptr->sumx2);
        printf("ox=%15.8E\n", ptr->ox);
        printf("ox^2=%15.8E\n", ptr->ox2);
        printf("Sx=%15.8E\n", ptr->sx);
        printf("Sx^2=%15.8E\n", ptr->sx2);
        printf("mean y=%15.8E\n", ptr->meany);
        printf("sum y=%15.8E\n", ptr->sumy);
        printf("sum y^2=%15.8E\n", ptr->sumy2);
        printf("oy=%15.8E\n", ptr->oy);
        printf("oy^2=%15.8E\n", ptr->oy2);
        printf("Sy=%15.8E\n", ptr->sy);
        printf("Sy^2=%15.8E\n", ptr->sy2);
        printf("sum xy=%15.8E\n\n", ptr->sumxy);
	printf("min x=%15.8E\n", ptr->minx); 
        printf("max x=%15.8E\n", ptr->maxx);
        printf("min y=%15.8E\n", ptr->miny); 
        printf("max y=%15.8E\n", ptr->maxy); 

	return 0;
}
