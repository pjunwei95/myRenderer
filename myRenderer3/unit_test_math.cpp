#include "unit_test_math.h"
#include "math.h"
#include <math.h>
#include <assert.h>

#define EPSILON 0.00005
//float EPSILON = 0.0005f;

//===================================================
//vec2
void TestVec2Constructor()
{
    LOG_UNIT_TEST();
    Vector2 foo(0.0, 0.0);
    assert(foo.x == 0.0);
    assert(foo.y == 0.0);
    Vector2 bar(1.1f, 2.2f);
    assert(fabs(bar.x - 1.1f) < EPSILON);
    assert(fabs(bar.y - 2.2f) < EPSILON);
}

void TestVec2Addition()
{
    LOG_UNIT_TEST();
    Vector2 foo(1.1f, 2.2f);
    logmsg("foo = (%.1f, %.1f)\n", foo.x, foo.y);
    Vector2 bar(1.1f, 2.2f);
    logmsg("bar = (%.1f, %.1f)\n", bar.x, bar.y);

    logmsg("operator+: baz = foo + bar = ");
    Vector2 baz = foo + bar;
    logmsg("(%.1f, %.1f)\n", baz.x, baz.y);
    assert(fabs(baz.x - 2.2) < EPSILON);
    assert(fabs(baz.y - 4.4) < EPSILON);

    logmsg("operator+=: foo += bar\n");
    foo += bar;
    logmsg("foo = (%.1f, %.1f)\n", foo.x, foo.y);
    assert(fabs(foo.x - 2.2) < EPSILON);
    assert(fabs(foo.y - 4.4) < EPSILON);
}

void TestVec2Assignment()
{
    LOG_UNIT_TEST();
    Vector2 a(1.1f, 2.2f);
    logmsg("a = (%.1f, %.1f)\nSet b = a\n", a.x, a.y);
    Vector2 b(2.2f, 3.3f);
    logmsg("b = (%.1f, %.1f)\n", b.x, b.y);
    b = a;
    logmsg("b = (%.1f, %.1f)\n", b.x, b.y);
    assert(fabs(b.x - 1.1) < EPSILON);
    assert(fabs(b.y - 2.2) < EPSILON);

    logmsg("Modifying b.x\n", b.x);
    b.x = 3.3f;
    logmsg("b = (%.1f, %.1f)\n", b.x, b.y);
    assert(fabs(b.x - 3.3) < EPSILON);
    assert(fabs(b.y - 2.2) < EPSILON);
    assert(fabs(a.x - 1.1) < EPSILON);
    assert(fabs(a.y - 2.2) < EPSILON);

    logmsg("a should remain the same\n");
    logmsg("a = (%.1f, %.1f)\n", a.x, a.y);
}

void TestVec2DotProduct()
{
    LOG_UNIT_TEST();
    Vector2 foo(2.2f, 3.3f);
    logmsg("foo = (%.1f, %.1f)\n", foo.x, foo.y);
    Vector2 bar(3.3f, 4.4f);
    logmsg("bar = (%.1f, %.1f)\n", bar.x, bar.y);

    logmsg("(foo) . (bar) = ");
    float scalar = dot(foo, bar);
    logmsg("%.3f\n", scalar);
    assert(fabs(scalar - 21.78) < EPSILON);
}

void TestVec2CrossProduct()
{
    LOG_UNIT_TEST();
    Vector2 foo(5.0, 13.0);
    logmsg("foo = (%.1f, %.1f)\n", foo.x, foo.y);
    Vector2 bar(7.0, 17.0);
    logmsg("bar = (%.1f, %.1f)\n", bar.x, bar.y);

    logmsg("(foo) X (bar) = ");
    float scalar = cross(foo, bar);
    logmsg("%.1f\n", scalar);
    assert(fabs(scalar + 6.0) < EPSILON); //scalar should be -6.0
}

//===================================================
//vec3

void TestVec3Addition()
{
    LOG_UNIT_TEST();
    Vector3 foo(1.1f, 2.2f, 3.3f);
    logmsg("foo = (%.1f, %.1f, %.1f)\n", foo.x, foo.y, foo.z);
    Vector3 bar(1.1f, 2.2f, 3.3f);
    logmsg("bar = (%.1f, %.1f, %.1f)\n", bar.x, bar.y, bar.z);

    logmsg("operator+: baz = foo + bar = ");
    Vector3 baz = foo + bar;
    logmsg("(%.1f, %.1f, %.1f)\n", baz.x, baz.y, baz.z);
    assert(fabs(baz.x - 2.2) < EPSILON);
    assert(fabs(baz.y - 4.4) < EPSILON);
    assert(fabs(baz.z - 6.6) < EPSILON);

    logmsg("operator+=: foo += bar\n");
    foo += bar;
    logmsg("foo = (%.1f, %.1f, %.1f)\n", foo.x, foo.y, foo.z);
    assert(fabs(foo.x - 2.2) < EPSILON);
    assert(fabs(foo.y - 4.4) < EPSILON);
    assert(fabs(foo.z - 6.6) < EPSILON);
}

void TestVec3DotProduct()
{
    LOG_UNIT_TEST();
    Vector3 foo(2.2f, 3.3f, 4.4f);
    logmsg("foo = (%.1f, %.1f, %.1f)\n", foo.x, foo.y, foo.z);
    Vector3 bar(3.3f, 4.4f, 5.5f);
    logmsg("bar = (%.1f, %.1f, %.1f)\n", bar.x, bar.y, bar.z);

    logmsg("(foo) . (bar) = ");
    float scalar = dot(foo, bar);
    logmsg("%.3f\n", scalar);
    assert(fabs(scalar - 45.98 < EPSILON));
}

void TestVec3CrossProduct()
{
    LOG_UNIT_TEST();
    Vector3 foo(1.0f, 3.0f, 4.0f);
    logmsg("foo = (%.1f, %.1f, %.1f)\n", foo.x, foo.y, foo.z);
    Vector3 bar(2.0f, 7.0f, -5.0f);
    logmsg("bar = (%.1f, %.1f, %.1f)\n", bar.x, bar.y, bar.z);

    logmsg("vector = (foo) X (bar) = ");
    Vector3 vector = cross(foo, bar);
    logmsg("(%.1f, %.1f, %.1f)\n", vector.x, vector.y, vector.z);
    assert(fabs(vector.x + 43.0) < EPSILON);
    assert(fabs(vector.y - 13.0) < EPSILON);
    assert(fabs(vector.z - 1.0) < EPSILON);
}

void TestVec4DotProduct()
{
    LOG_UNIT_TEST();
    Vector4 foo(2.0f, 3.0f, 4.0f, 5.0f);
    logmsg("foo = (%.1f, %.1f, %.1f, %.1f)\n", foo.x, foo.y, foo.z, foo.w);
    Vector4 bar(3.0f, 4.0f, 5.0f, 6.0f);
    logmsg("bar = (%.1f, %.1f, %.1f, %.1f)\n", bar.x, bar.y, bar.z, bar.w);

    logmsg("(foo) . (bar) = ");
    float scalar = dot(foo, bar);
    logmsg("%.1f\n", scalar);
    assert(fabs(scalar - 49.0) < EPSILON);
}

void PrettyPrintRow(Mtx44 matrix)
{
    logmsg("===============\n");
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            logmsg("%.1f ", matrix.arr[i][j]);
        }
        logmsg("\n");
    }
    logmsg("===============\n");
}

void TestMatrixConstructor()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            if (i == j)
            {
                assert(fabs(foo.arr[i][j] - 1.0) < EPSILON);
            }
            else
                assert(fabs(foo.arr[i][j]) < EPSILON);
        }
}

void TestMatrixScale()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("Identity:\n");
    PrettyPrintRow(foo);

    logmsg("Scale by (2, 3, 4):\n");
    foo.Scale(2.0f, 3.0f, 4.0f);
    PrettyPrintRow(foo);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (0 == i && 0 == j)
            {
                assert(fabs(foo.arr[i][j] - 2.0) < EPSILON);
                continue;
            }
            else if (1 == i && 1 == j)
            {
                assert(fabs(foo.arr[i][j] - 3.0) < EPSILON);
                continue;
            }
            else if (2 == i && 2 == j)
            {
                assert(fabs(foo.arr[i][j] - 4.0) < EPSILON);
                continue;
            }
            else if (3 == i && 3 == j)
            {
                assert(fabs(foo.arr[i][j] - 1.0) < EPSILON);
                continue;
            }
            else
                assert(fabs(foo.arr[i][j]) < EPSILON);
        }
    }
}

void TestMatrixTrans()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("Identity:\n");
    PrettyPrintRow(foo);

    logmsg("Translate by (2, 3, 4):\n");
    foo.Translate(2, 3, 4);
    PrettyPrintRow(foo);
}

void TestMatrixMultiplyVec()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("foo scaled by (2, 3, 4):\n");
    foo.Scale(2, 3, 4);
    PrettyPrintRow(foo);

    Vector4 vec(2, 3, 4, 5);
    logmsg("Multiply with vector (2, 3, 4, 5):\n");
    Vector4 result = foo * vec;
    logmsg("result = (%.1f, %.1f, %.1f, %.1f)\n", result.x, result.y, result.z, result.w);
}

void TestMatrixMultiplyIdentity()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("foo:\n");
    foo.Scale(1, 2, 1);
    PrettyPrintRow(foo);

    Mtx44 iden;

    logmsg("result = foo . I:\n");
    Mtx44 result = foo * iden;
    PrettyPrintRow(result);
}

void TestMatrixMultiplyMatrix()
{
    LOG_UNIT_TEST();
    Mtx44 mtx1;
    logmsg("mtx1:\n");
    mtx1.Scale(2, 1, 1);
    PrettyPrintRow(mtx1);

    Mtx44 mtx2;
    logmsg("mtx2:\n");
    mtx2.Scale(1, 2, 1);
    PrettyPrintRow(mtx2);

    logmsg("result = mtx1 . mtx2:\n");
    Mtx44 result = mtx1 * mtx2;
    PrettyPrintRow(result);
}
//#define TEST
void TestMath()
{
#ifdef TEST
    LOG_TEST(Math);
    //=======================================
    //Vec2
    TestVec2Constructor();
    TestVec2Addition();
    TestVec2Assignment();
    TestVec2DotProduct();
    TestVec2CrossProduct();
    //=======================================
    //Vec3
    TestVec3Addition();
    TestVec3DotProduct();
    TestVec3CrossProduct();
#else
    //=======================================
    //Vec4
    TestVec4DotProduct();
    //=======================================
    //Matrix
    TestMatrixScale();
    TestMatrixTrans();
    TestMatrixMultiplyVec();
    TestMatrixMultiplyIdentity();
    TestMatrixMultiplyMatrix();
    //Sample1();
    //Sample2();
    //TestVec2Copy();
#endif
}


//void Sample1()
//{
//    LOG_UNIT_TEST();
//    __m128i a{ 1,2,3,4 };
//    __m128i b{ 2,3,4,5 };
//    __m128i result = _mm_add_epi32(a, b);
//    logmsg("result = %i\n", result.m128i_i32[0]);
//}
//
//void Sample2()
//{
//    LOG_UNIT_TEST();
//    //Guide to Intrinsics
//    __m128 vector = _mm_set_ps(1.0, 1.0, 1.0, 1.0);
//    __m128 vector2 = _mm_set_ps1(1.0);
//    vector = _mm_add_ps(vector, vector2);
//    logmsg("add: v1,v2 = %f\n", vector.m128_f32[1]);
//    //other ops
//    //vector = _mm_sub_ps(vector, vector2);
//    //vector = _mm_mul_ps(vector, vector2);
//    //vector = _mm_div_ps(vector, vector2);
//    float array[4];
//    _mm_store_ps(array, vector);
//    logmsg("array[1] = %f\n", array[1]);
//}

//void TestVec2Copy()
//{
//    LOG_UNIT_TEST();
//    Vector2 a{ 1, 2 };
//    logmsg("a = (%i, %i)\nCopy a to b\n", a.X(), a.Y());
//    Vector2 b(a);
//    logmsg("b = (%i, %i)\n", b.X(), b.Y());
//}
//

