#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "debug.h"

//don't forget to change function declarations in table.h if functions are modified 
//from here

//comments in function should indicate what it does and if it returns anything 
//(what it means)

/*NOTE ABOUT ERRORS IN FUNCTIONS: errors in one function can lead to errors 
 * in other functions 
(EX: program may expect a certain number of points in the array
and  an insert function fails, may cause an error about an empty array in a 
delate function)*/

Table* creat_table(){
	//create a Table structure 
	//returns a Table structure or NULL on error

	//allocate space for whole Table structure & check allocation
	Table *tbl = (Table *)malloc(sizeof(Table));

	//test error message
	//free(tbl);
	//tbl = NULL;

	if(tbl == NULL){
		fprintf(stderr, "\ntable.c:Table* creat_table(): Error:failed ");
		fprintf(stderr, "to allocate memory for tbl\n\n");
		return NULL;
	}

	//allocate space for name & check allocation
	tbl->name = (char *)malloc(MAX_NAME * sizeof(char));

	//test error message
	//free(tbl->name);
	//tbl->name = NULL;

	if(tbl->name == NULL){
		fprintf(stderr, "\ntable.c:Table* creat_table(): Error:failed ");
		fprintf(stderr, "to allocate memory for tbl->name\n\n");
		free(tbl);
		tbl = NULL;
		return NULL;
	}

	//allocate space for x & check allocation
	tbl->x = (double *)calloc(MAX_PTS, sizeof(double));

	//test eror message
	//free(tbl->x);
	//tbl->x = NULL;

	if(tbl->x == NULL){
		fprintf(stderr, "\ntable.c:Table* creat_table(): Error:failed ");
		fprintf(stderr, "to allocate memory for x\n\n");
		free(tbl->name);
		tbl->name = NULL;
		free(tbl);
		tbl = NULL;
		return NULL;
	}

	//allocate space y & check allocation
	tbl->y = (double *)calloc(MAX_PTS, sizeof(double));

	//test erorr message
	//free(tbl->y);
	//tbl->y = NULL; 

	if(tbl->y == NULL){
		fprintf(stderr, "\ntable.c:Table* creat_table(): Error:failed ");
		fprintf(stderr, "to allocate memory for y\n\n");
		free(tbl->name);
		tbl->name = NULL;
		free(tbl->x);
		tbl->x = NULL;
		free(tbl);
		tbl = NULL;
		return NULL;
	}

	//set current position to 0
	tbl->next = 0;
	strcpy(tbl->name, " "); //initialize name so its value is known

	//debug mode when DEBUG = 1 in debug.h
	#if DEBUG
	printf("table was created\n");	
	getchar(); //enter any charcter to continue
	#endif

	return tbl;
}

int free_table(Table **ptr){
	//deallcoate space for a Table structure
	//free elements of Table first
	//returns 0 on success and 1 on error

	//test error messages
	//assume memory was already freed in test or never allocated
	//free((*ptr)->name);
	//(*ptr)->name = NULL;
	//free((*ptr)->x);
	//(*ptr)->x = NULL;
	//free((*ptr)->y);
	//(*ptr)->y = NULL;
	//free(*ptr);
	//*ptr = NULL;
	//ptr = NULL; //test error message
	// *ptr = NULL; //test error message

	//check for NULL pointers
	if((ptr == NULL) || (*ptr == NULL)){
		fprintf(stderr, "\ntable.c:int free_table(Table **ptr): Error:ptr or *ptr is ");
		fprintf(stderr, "a NULL pointer\n\n");
		return 1; //error
	} 

	free((*ptr)->name);
	(*ptr)->name = NULL; //remove possible dangling pointer

	free((*ptr)->x);
	(*ptr)->x = NULL; //remove possible dangling pointer

	free((*ptr)->y);
	(*ptr)->y = NULL; //remove possible dangling pointer

	//free table itself
	free(*ptr);
	*ptr = NULL;

	//debuig mode when DEBUG = 1 in debug.h
	#if DEBUG
	printf("table was freed\n");
	getchar(); //enter any character to continue
	#endif

	return 0; //indicates function successfully executed
}

int print_table(Table *ptr){
	//print a table (name and its x & y coordinates)
	//returns 0 on success and 1 on error

	//does not need a pointer to a pointer (**ptr) since values in the table 
	//are not modified
	unsigned int line_cnt = 0;

	//test error messages
	//ptr = NULL; //valgrind will show leak

	//check for NULL pointer & name has a value
	if(ptr == NULL){
		fprintf(stderr, "\ntable.c:int print_table(Table *ptr): Error:ptr ");
		fprintf(stderr, "is a NULL pointer\n\n");
		return 1; //error;
	}
	else if(ptr->name == NULL){
		fprintf(stderr, "\ntable.c: int print_table(Table *ptr): Error:ptr->name ");
		fprintf(stderr, "is a NULL pointer\n");
		return 1;
	}
	else if((ptr->x == NULL) || (ptr->y == NULL)){
		fprintf(stderr, "\ntable.c: int print_table(Table *ptr): Error: ptr->x or ptr->y ");
                fprintf(stderr, "are NULL pointers\n");
		return 1;
	}
	else if(strcmp(ptr->name, " ") == 0){
		fprintf(stderr, "table.c:int print_table(Table *ptr): Error:ptr->name in not set\n\n");
		return 1;
	}

	printf("%s", ptr->name); //can't have a ':' since ptr->name will have a '\n' at the end
	printf("%15s %15s\n", "x", "y"); //formatted. max digits of double is 15

	for(unsigned int i = 0; i < ptr->next; i++){
		printf("[%u] %15.8E %15.8E\n", i, ptr->x[i], ptr->y[i]); //formated 15 digits each
		//scientific notation
		line_cnt += 1;
		if(line_cnt % 30 == 0) getchar();
	}

	//debug mode when DEBUG=1 in debug.h
	#if DEBUG
	printf("next=%u\n", ptr->next);
	getchar(); //enter any charcater to continue
	#endif

	return 0; //indicates function successfully executed
}

int uinsert_end(Table **ptr, double x, double y){
	//insert point at end of table (for unsorted arrays)
	//returns 0 on success and 1 on error

	//test error messages
	//ptr = NULL;
	//*ptr = NULL;
	//(*ptr)->next = MAX_PTS-1;
        //(*ptr)->next = MAX_PTS;
        //(*ptr)->next = MAX_PTS + 1;


	//check for NULL pointers
	if((ptr == NULL) || (*ptr == NULL)){
		fprintf(stderr, "\ntable.c:int uinsert_end(Table **ptr, double x, double y): ");
		fprintf(stderr, "Error:ptr or *ptr is a NULL pointer\n\n");
		return 1; //non-critical error
	}
	else if(((*ptr)->x == NULL) || ((*ptr)->y == NULL)){
		fprintf(stderr, "table.c:int uinsert_end(Table **ptr, double x, double y): Error");
		fprintf(stderr, "x or y is a NULL pointer\n\n");
		return 1;
	} 
	if((*ptr)->next >= MAX_PTS){ //check if table is full
		fprintf(stderr, "\ntable.c:int uinsert_end(Table **ptr, double x, double y): ");
		fprintf(stderr, "Error:table is full\n\n");
		return 1; //non-critical error
	}

	//not necessary to check for buffer underflow & overfow: will result in -inf and inf if 
	//large enough past 
	//not necessary to check x or y for NULL since they aren't pointers
	(*ptr)->x[(*ptr)->next] = x;
	(*ptr)->y[(*ptr)->next] = y;
	(*ptr)->next += 1;
	return 0;
}
