#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "file.h" //also includes table.h
#include "misc.h"

file_buffer* creat_buff(){
	//create a file buffer for a file
	// buffer holds exactly 1 line at a time
	//name is name of file
	//pass argv[1] as the name 
	//returns dynamic file_buffer or NULL on error

	//allocate space for dynamic file_buffer
	file_buffer *ptr = (file_buffer*)malloc(sizeof(file_buffer));

	//check error message 
	//free(ptr);
	//ptr = NULL;

	//checked each logical path of this function with valgrind
	//showed no leaks possible

	//check allocation for NULL pointers
	if(ptr == NULL){
		fprintf(stderr, "\nfile.c:file_buffer* creat_buffer(): Error:");
		fprintf(stderr, "failed to allocate memory for ptr\n\n");
		return NULL;
	}

	//allocate space for ptr->buff
	ptr->buff = (char*)malloc(BUFF_COLS * sizeof(char));

	//check error message
	//free(ptr->buff);
	//ptr->buff = NULL;

	//check allocation for ptr->buff
	if(ptr->buff == NULL){
		fprintf(stderr, "\nfile.c:file_buffer* creat_buffer(): Error:");
		fprintf(stderr, "failed to allocate memory for ptr->buff\n\n");
		free(ptr);
		ptr = NULL;
		return NULL;
	}

	ptr->line_cnt = 0;

	//debug mode when DEBUG = 1 in debug.h
	#if DEBUG
	printf("buffer was created\n");
	getchar(); //enter any char to continue. 
	#endif

	return ptr;
}

int free_buff(file_buffer **ptr){
	//free memory for a file buffer
	//returns 0 on success and 1 on error

	//check erorr message
	//simulate as if *ptr was never allocated
	//free((*ptr)->buff);
	//(*ptr)->buff = NULL;
	//free(*ptr);
	//ptr = NULL; //will leak 
	// *ptr = NULL; //leak. sets buff in main to NULL before its freed

	//check for NULL pointers
	if((ptr == NULL) || (*ptr == NULL)){
		fprintf(stderr, "file.c:int free_buff(file_buffer **ptr): Error:ptr or *ptr is a NULL pointer\n");
		return 1;
	}

	//free (*ptr)->buff
	free((*ptr)->buff);
	(*ptr)->buff = NULL; //remove dangling pointers

	//free ptr
	free(*ptr);
	*ptr = NULL; //remove dangling pointers

	//debug mode when DEBUG = 1 in debug.h
        #if DEBUG
	printf("buffer was freed\n");
	getchar(); //enter any character to continue
	#endif

	return 0;
}

int cp_file2table(file_buffer **buff, char *file_name, Table **tbl){
	//copy a file to a table
	//copies 1 line of a file to a buffer temporarily
	//returns 0 on success and 1 on error

	//check error messages
	//free_buff(buff);
	//buff = NULL;
	// *buff = NULL;
	//free_table(tbl);
	//tbl = NULL;
	// *tbl = NULL; 

	//check for NULL pointers
	if((buff == NULL) || (*buff == NULL)){
		fprintf(stderr, "\nfile.c:int cp_file2table(file_buffer **buff, char *file_name, Table **tbl): ");
		fprintf(stderr, "Error:buff or *buff is a NULL pointer\n\n");
		return 1; 
	}
	else if((tbl == NULL) || (*tbl == NULL)){
	 	fprintf(stderr, "\nfile.c:int cp_file2table(file_buffer **buff, char *file_name, Table **tbl): ");
                fprintf(stderr, "Error:tbl or *tbl is a NULL pointer\n\n");
                return 1;
        }

	(*buff)->fp = fopen(file_name, "r"); //open file as read-only

	//check if file opened
	if((*buff)->fp == NULL){ 
		//NOTE: any returns after this point need to close the file
		fprintf(stderr, "\nfile.c:int cp_file2table(file_buffer **buff, char *file_name, Table **tbl):");
		fprintf(stderr, "Error: file not found\n\n");
		return 1;
	}

	//debug mode when DEBUG = 1 in debug.h
	#if DEBUG
        printf("file was opened\n");
        getchar();
        #endif

	//read in file and copy to table
	//1st line is the table name; the rest are points
	//read 1 line past MAX_LINES to detect a file too long
	while(((*buff)->line_cnt <= MAX_LINES) && (fgets((*buff)->buff, BUFF_COLS, (*buff)->fp))){
		if((*buff)->line_cnt == 0){
			//line 0 is a table name
			strcpy((*tbl)->name, (*buff)->buff);
		}
		else if((*buff)->line_cnt == MAX_LINES){
			//check file is less than 1001 lines
			//(x & y can hold to 1000 points & 1st line of file is the name
			fprintf(stderr, "\nfile.c:int cp_file2table(file_buffer **buff, char *file_name, Table **tbl):");
			fprintf(stderr, "Error: file is longer than %u lines\n\n", MAX_LINES);
			fclose((*buff)->fp); //valgrind shows a leak unless this is done

			//debug mode when DEBUG = 1 in debug.h
        		#if DEBUG
			printf("file was closeed\n");
        		getchar();
        		#endif

			return 1;
		}
		else if(strstr((*buff)->buff, "\n") == NULL){
			//check if line is too long
			fprintf(stderr, "\nfile.c:int cp_file2table(file_buffer **buff, char *file_name, Table **tbl):");
			fprintf(stderr, "Error: line %u is too long\n", (*buff)->line_cnt+1); //most text editors start at line 1
			//so print it as line_cnt+1 to match this 
			fclose((*buff)->fp); //valgrind shows a leak unless this is done

			//debug mode when DEBUG = 1 in debug.h
                        #if DEBUG
                        printf("file was closeed\n");
                        getchar();
                        #endif

			return 1;
		}
		else{
			//any line after line 0 is a point
			char *tok1 = strtok((*buff)->buff, " ");
			char *tok2 = strtok(NULL, "\n");

			//this can be remove once the whitespace bug is removed. this didn't check for tabs
			//if(strstr(tok1, " ") != NULL) fprintf(stderr, "tok1 has whitespace in it\n");
			//else if(strstr(tok2, " ") != NULL) fprintf(stderr, "tok2 has whitespace in it\n");

			#if DEBUG
			printf("[%u] tok1=%s tok2=%s\n", (*buff)->line_cnt, tok1, tok2); //test to show tokens
			getchar(); //enter any character to view next token
			//tokens are values in file
			#endif

			//check tokens
			if((tok1 == NULL) || (tok2 == NULL)){
				fprintf(stderr, "\nint cp_file2table(file_buffer **buff, char *file_name, Table **tbl): ");
				fprintf(stderr, "Error: invalid format line %u\n\n", (*buff)->line_cnt+1); //text editors usually
				//start line counts at 1 so display as line_cnt+1 to match this behavior
				fclose((*buff)->fp);
				return 1;
			}
			else if((test_double(tok1) != 1) || (test_double(tok2) != 1)){
				//check if tokens are valid doubles
				fprintf(stderr, "\nint cp_file2table(file_buffer **buff, char *file_name, Table **tbl): ");
				fprintf(stderr, "invalid format line %u\n\n", (*buff)->line_cnt+1); //same as about
				//to match text editors starting line counts at 1
				fclose((*buff)->fp);
				return 1;
			}
			else if(uinsert_end(tbl, atof(tok1), atof(tok2)) != 0){
				fclose((*buff)->fp);
				return 1;
			} 
		}
		(*buff)->line_cnt++;
	}

	//debug mode when DEBUG = 1 in debug.h
        #if DEBUG
	printf("\nline_cnt=%u\n\n", (*buff)->line_cnt); //debug
	getchar(); //enter any charcter to continue
	#endif

	//close file
	fclose((*buff)->fp);

	//debug mode when DEBUG = 1 in debug.h
	#if DEBUG
	printf("file was closed\n");
	printf("file was copied to table\n");
	getchar(); //enter any character to continue
	#endif

	return 0;
}
