//gaurd against multile copies of header
#ifndef FILE_H
#define FILE_H

#include "table.h"

#define BUFF_COLS 100 //max columns in buffer
#define MAX_LINES (MAX_PTS + 1) //extra since file includes a name

typedef struct file_buffer{
	FILE *fp;
	char *buff; //holds 1 line from the file
	unsigned int line_cnt; //line count
}file_buffer;

file_buffer* creat_buff();
int free_buff(file_buffer **ptr);
int cp_file2table(file_buffer **buff, char *file_name, Table **tbl);
#endif
