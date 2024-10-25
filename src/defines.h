#ifndef DEFINES_H
#define DEFINES_H

/* unsigned int types */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* signed int types */
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

/* floating point types */
typedef float f32;
typedef double f64;

#define true 1
#define false 0

#define null 0
#define u32_max 0x100000000 /* 4.294.967.295 */

#if defined (__clang__)
#   define COMPILER_CLANG
#elif defined (_MSC_VER)
#   define COMPILER_CL
#elif defined (__GNUC__)
#   define COMPILER_GCC
#endif

#if defined (COMPILER_CLANG)
#   define FILE_NAME __FILE_NAME__
#else
#   define FILE_NAME __FILE__
#endif

#define Gigabytes(count) (u64) (count * 1024 * 1024 * 1024)
#define Megabytes(count) (u64) (count * 1024 * 1024)
#define Kilobytes(count) (u64) (count * 1024)

#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)<(b))?(b):(a))

#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

#endif /* DEFINES_H */
