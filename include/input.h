
#ifndef __INPUT__
#define __INPUT__

#include<stdio.h>
#include<stdlib.h>
#include<data_structure.h>
//#include<utilities_lmjd.h>

#define BLEN 200

static int get_a_line(FILE *fp, char *buf);
void populate_data(FILE *frestart, char line[], char restfile[],char trajfile[], char ergfile[], mdsys_t *sys);
void readRetart(FILE *fp, mdsys_t *ptr_sys, char restfile[]);

#endif