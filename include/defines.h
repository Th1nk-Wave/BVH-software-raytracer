#ifndef __DEFINES_H_
#define __DEFINES_H_

#define FLOAT_INFINITY 1e30f

#define uint unsigned int


#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define clamp(a,x,b) (((x)<(a))?(a):((b)<(x))?(b):(x))

#endif