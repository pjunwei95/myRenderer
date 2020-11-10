#pragma once

#define LOG_TEST(name) logfile("----------------------------------------------------Testing "#name"\n");
#define LOG_UNIT_TEST() logfile("\n********** %s **********\n", __FUNCTION__)

//#define ASSERT(condition) if(!(condition)) logmsg("ASSERT FAILED: %s @ %s (%d)\n", #condition, __FILE__, __LINE__ )

void openLogStream();

void closeLogStream();

void logmsg(const char * format, ...);

void logfile(const char * format, ...);

