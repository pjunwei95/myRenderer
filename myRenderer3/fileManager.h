#pragma once
#include <stdio.h>

extern FILE* pfout;

void readFromFile(const char * fileName);

FILE * startLog();

//void startLog(FILE * pfout);

//FILE * startLog(FILE * pfout);

void endLog(FILE * pfout);

//void function();
