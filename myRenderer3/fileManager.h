#pragma once
#include <stdio.h>

void readFromFile(const char * fileName);

FILE * startLog();

//void startLog(FILE * pfout);

//FILE * startLog(FILE * pfout);

void endLog(FILE * pfout);

//void function();
