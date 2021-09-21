#ifndef __UTF8_UTILS_H__
#define __UTF8_UTILS_H__

extern int utf8decode(const char *, long *);
extern int utf8encode(long *, char *);
extern int utf8size(const char *);
extern int isfullutf8(char *, int);

#endif