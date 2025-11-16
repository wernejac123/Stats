//gaurd against multile copies of header
#ifndef TABLE_H
#define TABLE_H
#define MAX_NAME 10
#define MAX_PTS 1000 //maximum number of points in arrays x & y

typedef struct Table{
	char *name; //name of the table
	double *x; 
	double *y;
	unsigned int next; //next available position in arrays x & y
}Table;

//don't forget to change function definition in table.c if declaration changes

Table* creat_table();
int free_table(Table **ptr);
int print_table(Table *ptr);
int uinsert_end(Table **ptr, double x, double y); //insert point at end of table
#endif
