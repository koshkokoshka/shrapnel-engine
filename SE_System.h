#ifndef SE_TYPES_H
#define SE_TYPES_H

/**
 * Basic types
 */
#include <stddef.h>
#define nil NULL

#include <stdint.h>
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;
typedef float f32;
typedef double f64;
typedef size_t reg;

/**
 * Standard C library
 */
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

/**
 * Useful macros
 */
#define sizeofarray(array) (sizeof(array) / sizeof((array)[0]))

#endif