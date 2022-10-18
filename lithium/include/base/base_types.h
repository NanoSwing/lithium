#ifndef LI_BASE_TYPES_H
#define LI_BASE_TYPES_H

typedef unsigned char      U8; 
typedef unsigned short     U16;
typedef unsigned int       U32;
typedef unsigned long long U64;
typedef unsigned long      Usize;

typedef signed char      I8; 
typedef signed short     I16;
typedef signed int       I32;
typedef signed long long I64;
typedef signed long      Isize;

typedef float  F32;
typedef double F64;

typedef U8  B8;
typedef U32 B32;
#ifndef true
	#define true 1
#endif // true
#ifndef false
	#define false 0
#endif // false

#endif // LI_BASE_TYPES_H
