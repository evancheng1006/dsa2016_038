#ifndef LONGWORD_H
#define LONGWORD_H

#include <cstring>

#ifndef MAXWORD
#define MAXWORD (200)
#endif
typedef struct lONGWORD {
	char c[MAXWORD];
} LONGWORD;

inline bool operator < (LONGWORD const & lhs, LONGWORD const & rhs) {
	if (strncmp(lhs.c, rhs.c, MAXWORD) < 0) {
		return true;
	}
	return false;
}
// header file should online declare the function, not implement the function. Therefore, use "inline" to avoid redeclaration.

#endif
