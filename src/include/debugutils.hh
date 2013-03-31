// File: debugutils.hh
// Date: Tue Mar 26 18:35:49 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#ifndef __HEAD__DEBUGUTILS
#define __HEAD__DEBUGUTILS


void __sassert_check__(bool val, const char *expr,
		const char *file, const char *func, int line);


#define sassert(expr) \
	__sassert_check__((expr), # expr, __FILE__, __PRETTY_FUNCTION__, __LINE__)

void error_exit(const char *msg) __attribute__((noreturn));


#ifdef DEBUG

#define print_debug(fmt, ...) \
			__print_debug__(__FILE__, __func__, __LINE__, fmt, ## __VA_ARGS__)


void __print_debug__(const char *file, const char *func, int line, const char *fmt, ...)
	__attribute__((format(printf, 4, 5)));

#else

#define print_debug(fmt, ...)


#endif
#endif //HEAD
