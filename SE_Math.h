#ifndef SE_MATH_H
#define SE_MATH_H

#include "SE_System.h"

#ifdef _WIN33
#define _USE_MATH_DEFINES
#endif
#include <math.h>

/* Min */
static inline i8 SE_MinI8(i8 a, i8 b) { return a < b ? a : b; }
static inline u8 SE_MinU8(u8 a, u8 b) { return a < b ? a : b; }
static inline i16 SE_MinI16(i16 a, i16 b) { return a < b ? a : b; }
static inline u16 SE_MinU16(u16 a, u16 b) { return a < b ? a : b; }
static inline i32 SE_MinI32(i32 a, i32 b) { return a < b ? a : b; }
static inline u32 SE_MinU32(u32 a, u32 b) { return a < b ? a : b; }
static inline int SE_MinInt(int a, int b) { return a < b ? a : b; }
#define SE_MinF32(a, b) fminf(a, b)
#define SE_MinF64(a, b) fmin(a, b)

/* Max */
static inline i8 SE_MaxI8(i8 a, i8 b) { return a > b ? a : b; }
static inline u8 SE_MaxU8(u8 a, u8 b) { return a > b ? a : b; }
static inline i16 SE_MaxI16(i16 a, i16 b) { return a > b ? a : b; }
static inline u16 SE_MaxU16(u16 a, u16 b) { return a > b ? a : b; }
static inline i32 SE_MaxI32(i32 a, i32 b) { return a > b ? a : b; }
static inline u32 SE_MaxU32(u32 a, u32 b) { return a > b ? a : b; }
static inline int SE_MaxInt(int a, int b) { return a > b ? a : b; }
#define SE_MaxF32(a, b) fmaxf(a, b)
#define SE_MaxF64(a, b) fmax(a, b)

/* Abs */
static inline i8 SE_AbsI8(i8 x) { return x < 0 ? -x : x; }
static inline i16 SE_AbsI16(i16 x) { return x < 0 ? -x : x; }
#define SE_AbsI32(x) abs(x)
#define SE_AbsInt(x) abs(x)
#define SE_AbsF32(x) fabsf(x)
#define SE_AbsF64(x) fabs(x)

#define SE_PI M_PI
#define SE_PI2 (M_PI*2)
#define SE_NAN NAN

#define SE_Rad(deg) ((deg) / 180 * SE_PI)
#define SE_Deg(rad) ((rad) * 180 / SE_PI)

#define SE_ClampI8(x, min, max) SE_MinI8(SE_MaxI8((x), (min)), (max))
#define SE_ClampI16(x, min, max) SE_MinI16(SE_MaxI16((x), (min)), (max))
#define SE_ClampI32(x, min, max) SE_MinI32(SE_MaxI32((x), (min)), (max))
#define SE_ClampF32(x, min, max) SE_MinF32(SE_MaxF32((x), (min)), (max))
#define SE_ClampF64(x, min, max) SE_MinF64(SE_MaxF64((x), (min)), (max))

#define SE_RandI32() rand()
#define SE_RandF32() ( (f32)rand() / (f32)RAND_MAX )
#define SE_Rand_SetSeed(seed) srand(seed)

#define SE_SinF32(x) sinf(x)
#define SE_SinF64(x) sin(x)
#define SE_CosF32(x) cosf(x)
#define SE_CosF64(x) cos(x)
#define SE_TanF32(x) tanf(x)
#define SE_TanF64(x) tan(x)
#define SE_ModF32(a, b) fmodf(a, b)
#define SE_ModF64(a, b) fmod(a, b)
#define SE_PowF32(a, b) powf(a, b)
#define SE_PowF64(a, b) pow(a, b)
#define SE_Atan2F32(a, b) atan2f(a, b)
#define SE_Atan2F64(a, b) atan2(a, b)
#define SE_SqrtF32(a) sqrtf(a)
#define SE_SqrtF64(a) sqrt(a)
#define SE_RoundF32(a) roundf(a)
#define SE_RoundF64(a) round(a)
#define SE_FloorF32(a) floorf(a)
#define SE_FloorF64(a) floor(a)
#define SE_CeilF32(a) ceilf(a)
#define SE_CeilF64(a) ceil(a)

static inline f32 SE_LerpF32(f32 a, f32 b, f32 t) { return a + t * (b - a); }

static inline void SE_SwapF32(f32 *a, f32 *b) { f32 t = *a; *a = *b; *b = t; }
static inline void SE_SwapInt(int *a, int *b) { int t = *a; *a = *b; *b = t; }

/**
 * Vector
 */
typedef struct
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;

} SE_Vector;

extern const SE_Vector SE_INITIAL_VECTOR;

void SE_Vector_RotateX(SE_Vector *p, f32 r);

void SE_Vector_RotateY(SE_Vector *p, f32 r);

void SE_Vector_RotateZ(SE_Vector *p, f32 r);

/**
 * Matrix
 */
typedef struct
{
    union {
        f32 m[4][4];
        struct {
            f32 m00, m01, m02, m03;
            f32 m10, m11, m12, m13;
            f32 m20, m21, m22, m23;
            f32 m30, m31, m32, m33;
        };
    };

} SE_Matrix;

extern const SE_Matrix SE_IDENTITY_MATRIX;

// Translation matrix:
// [ 1, 0, 0, 0,
//   0, 1, 0, 0,
//   0, 0, 1, 0,
//   x, y, z, 1 ]

// Scale matrix:
// [ x, 0, 0, 0,
//   0, y, 0, 0,
//   0, 0, z, 0,
//   0, 0, 0, 1 ]

void SE_MultiplyMatrices(SE_Matrix *out, SE_Matrix *a, SE_Matrix *b);

void SE_TransformVector(SE_Vector *v, SE_Matrix *m);

#endif