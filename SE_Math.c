#include "SE_Math.h"

/**
 * Vector
 */
const SE_Vector SE_INITIAL_VECTOR = {
        0, 0, 0, 1
};

void SE_Vector_RotateX(SE_Vector *p, f32 r)
{
    f32 s = SE_SinF32(r);
    f32 c = SE_CosF32(r);

    f32 a = (p->y * c) - (p->z * s);
    f32 b = (p->y * s) + (p->z * c);

    p->y = a;
    p->z = b;
}

void SE_Vector_RotateY(SE_Vector *p, f32 r)
{
    f32 s = SE_SinF32(r);
    f32 c = SE_CosF32(r);

    f32 a = (p->z * s) + (p->x * c);
    f32 b = (p->z * c) - (p->x * s);

    p->x = a;
    p->z = b;
}

void SE_Vector_RotateZ(SE_Vector *p, f32 r)
{
    f32 s = SE_SinF32(r);
    f32 c = SE_CosF32(r);

    f32 a = (p->x * c) - (p->y * s);
    f32 b = (p->x * s) + (p->y * c);

    p->x = a;
    p->y = b;
}

/**
 * Matrix
 */
const SE_Matrix SE_IDENTITY_MATRIX = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
};

void SE_MultiplyMatrices(SE_Matrix *out, SE_Matrix *a, SE_Matrix *b)
{
    SE_Matrix tmp = {
            (a->m00 * b->m00) + (a->m01 * b->m10) + (a->m02 * b->m20) + (a->m03 * b->m30),
            (a->m00 * b->m01) + (a->m01 * b->m11) + (a->m02 * b->m21) + (a->m03 * b->m31),
            (a->m00 * b->m02) + (a->m01 * b->m12) + (a->m02 * b->m22) + (a->m03 * b->m32),
            (a->m00 * b->m03) + (a->m01 * b->m13) + (a->m02 * b->m23) + (a->m03 * b->m33),

            (a->m10 * b->m00) + (a->m11 * b->m10) + (a->m12 * b->m20) + (a->m13 * b->m30),
            (a->m10 * b->m01) + (a->m11 * b->m11) + (a->m12 * b->m21) + (a->m13 * b->m31),
            (a->m10 * b->m02) + (a->m11 * b->m12) + (a->m12 * b->m22) + (a->m13 * b->m32),
            (a->m10 * b->m03) + (a->m11 * b->m13) + (a->m12 * b->m23) + (a->m13 * b->m33),

            (a->m20 * b->m00) + (a->m21 * b->m10) + (a->m22 * b->m20) + (a->m23 * b->m30),
            (a->m20 * b->m01) + (a->m21 * b->m11) + (a->m22 * b->m21) + (a->m23 * b->m31),
            (a->m20 * b->m02) + (a->m21 * b->m12) + (a->m22 * b->m22) + (a->m23 * b->m32),
            (a->m20 * b->m03) + (a->m21 * b->m13) + (a->m22 * b->m23) + (a->m23 * b->m33),

            (a->m30 * b->m00) + (a->m31 * b->m10) + (a->m32 * b->m20) + (a->m33 * b->m30),
            (a->m30 * b->m01) + (a->m31 * b->m11) + (a->m32 * b->m21) + (a->m33 * b->m31),
            (a->m30 * b->m02) + (a->m31 * b->m12) + (a->m32 * b->m22) + (a->m33 * b->m32),
            (a->m30 * b->m03) + (a->m31 * b->m13) + (a->m32 * b->m23) + (a->m33 * b->m33)
    };
    *out = tmp;
}

void SE_TransformVector(SE_Vector *v, SE_Matrix *m)
{
    SE_Vector tmp = *v;
    v->x = (m->m00 * tmp.x) + (m->m01 * tmp.y) + (m->m02 * tmp.z) + (m->m03 * tmp.w);
    v->y = (m->m10 * tmp.x) + (m->m11 * tmp.y) + (m->m12 * tmp.z) + (m->m13 * tmp.w);
    v->z = (m->m20 * tmp.x) + (m->m21 * tmp.y) + (m->m22 * tmp.z) + (m->m23 * tmp.w);
    v->w = (m->m30 * tmp.x) + (m->m31 * tmp.y) + (m->m32 * tmp.z) + (m->m33 * tmp.w);
}