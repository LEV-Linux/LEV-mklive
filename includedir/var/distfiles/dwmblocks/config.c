#include "config.h"

#include "block.h"
#include "util.h"

Block blocks[] = {
	{"sb-timer",      0,    4},
	{"sb-recording",  0,    5},
	{"sb-internet",   5,    3},
	{"sb-battery",    2,    0},
	{"sb-date",       1,    0},
	{"echo ';'",      0,    0},
	{"sb-brightness", 0,    6},
	{"sb-volume",     0,    1},
	{"sb-xkeyboard",  0,    7},
	{"echo ';'",      0,    0},
	{"sb-disk",       3600, 2},
	{"sb-cpubars",    2,    0},
    {"sb-cputemp",    2,    0},
	{"sb-ram",        4,    0},
};

const unsigned short blockCount = LEN(blocks);
