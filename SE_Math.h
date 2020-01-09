#ifndef SE_MATH_H
#define SE_MATH_H

#include "SE_System.h"

#include <math.h>

static inline i32 SE_AbsI32(int a) { return a < 0 ? -a : a; }
static inline int SE_MinInt(int a, int b) { return a < b ? a : b; }
static inline int SE_MaxInt(int a, int b) { return a > b ? a : b; }

#define SE_AbsF32(a) fabsf(a)

#define SE_MaxF32(a, b) fmaxf(a, b)
#define SE_MinF32(a, b) fminf(a, b)

#define SE_SinF32(a) sinf(a)
#define SE_CosF32(a) cosf(a)
#define SE_TanF32(a) tanf(a)
#define SE_ModF32(a, b) fmodf(a, b)
#define SE_SqrtF32(a) sqrtf(a)
#define SE_FloorF32(a) floorf(a)
#define SE_CeilF32(a) ceilf(a)
#define SE_PowF32(a, b) powf(a, b)

static inline void SE_SwapF32(f32 *a, f32 *b) { f32 t = *a; *a = *b; *b = t; }
static inline void SE_SwapInt(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static inline f32 SE_LerpF32(f32 v0, f32 v1, f32 t) { return v0 + t * (v1 - v0); }

/* vector */
typedef struct { f32 x, y, z, w; } SE_Vector;

void SE_Vector_RotateX(SE_Vector *p, f32 r);
void SE_Vector_RotateY(SE_Vector *p, f32 r);
void SE_Vector_RotateZ(SE_Vector *p, f32 r);

/* matrix */
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

void SE_MultiplyMatrices(SE_Matrix *out, SE_Matrix *a, SE_Matrix *b);

#endif