#pragma once

#define LOG_TEST(name) logmsg("----------------------------------------------------TESTING "#name"\n");
#define LOG_UNIT_TEST() logmsg("---------------------------------In \"%s\"\n", __FUNCTION__)

void openLogStream();

void closeLogStream();

void logmsg(const char * format, ...);
