#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "file.h" //structure mainly for copying a file into a buffer 
#include "stats.h" //this file includes table.h
#include "version.h"

//NOTE: exit() closes files, but does not free memory

int main(int argc, char *argv[]){
	//check arguments
        if(argc != 2){
		//check arguments
                fprintf(stderr, "\nmain(int argc, char *argv[]): Error:number of arguments\n\n");
                return 1; //error
        }
	else if((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)){
		//PRINT_VERSION(); //macro defined in version.h
		printf("%s\n", VERSION);
		exit(EXIT_SUCCESS);
	}

	//declarations and handle errors
	file_buffer *buff = creat_buff(argv[1]);
	if(buff == NULL) exit(EXIT_FAILURE);

	Stat *stat = creat_stat();
	if(stat == NULL){ 
		free_buff(&buff);
		exit(EXIT_FAILURE);
	} //end of declarations
	else if(cp_file2table(&buff, argv[1], &stat->tbl) != 0){
		//copy file to buffer & handle error
		free_buff(&buff);
		free_stat(&stat);
		exit(EXIT_FAILURE);
	}
	else if(free_buff(&buff) != 0){
		free_stat(&stat);
		exit(EXIT_FAILURE); //free buffer
	}
	else if(print_table(stat->tbl) != 0) exit(EXIT_FAILURE); //test. although it might be necessary in stats file
	else if(calc_stat(&stat) != 0) exit(EXIT_FAILURE); //assume if pointer is NULL, Stats stat was never created. don't free it
	else if(print_stat(stat) != 0) exit(EXIT_FAILURE); //assume if pointer is NULL, Stats stat was never created. don't free it
        else if(free_stat(&stat) != 0) exit(EXIT_FAILURE); //free stat (and Table inside)

	return 0;
}
