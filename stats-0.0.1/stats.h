//gaurd against multile copies of header
#ifndef STATS_H
#define STATS_H

#include "table.h"

//this structure is to store staitistical calculations for a table

typedef struct Stat{
	Table *tbl;
	unsigned int n; //number of elements in x & y
	//x stats
	double meanx;
	double sumx; ////sumation of x
	double sumx2; ////sumation of x^2
	double ox; //population standard deviation x
	double ox2; //standard variance of x
	double sx; //sample standard deviation of x
	double sx2; //sample variance of x	
	//y stats
	double meany;
        double sumy; ////sumation of y
        double sumy2; ////sumation of y^2
        double oy; //population standard deviation y
        double oy2; //standard variance of y
        double sy; //sample standard deviation of y
        double sy2; //sample variance of y
	//x & y
	double sumxy; //summation of (x[i] * y[i])

	//new features
	double minx; //min of x
	double maxx; //max of x
	double miny; //min of y
	double maxy; //max of y
}Stat;

Stat* creat_stat();
int free_stat(Stat **ptr);
int calc_stat(Stat **ptr);
int print_stat(Stat *ptr);
#endif

