// File: utils.hh
// Date: Fri Aug 16 17:16:44 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#ifndef __HEAD__UTILS
#define __HEAD__UTILS

#include <cstdarg>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <sstream>
using namespace std;

#define REP(x, y) for (int x = 0; x < (y); x ++)
#define REPL(x, y, z) for (int x = y; x < (z); x ++)
#define REPD(x, y, z) for (int x = y; x >= (z); x --)
#define P(a) std::cout << (a) << std::endl

string TERM_COLOR(int k);

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

void c_printf(const char* col, const char* fmt, ...);

void c_fprintf(const char* col, FILE* fp, const char* fmt, ...);

#endif //HEAD
