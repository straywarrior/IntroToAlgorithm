#ifndef _TIMECALC_H_
#define _TIMECALC_H_ value
#include <Windows.h>

/*
usage:

LARGE_INTEGER t1, t2, tc
QueryPerformanceFrequency(&tc);
QueryPerformanceCounter(&t1);
foo();//dosomething
QueryPerformanceCounter(&t2);
printf("Use Time:%f\n", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);

*/
#endif