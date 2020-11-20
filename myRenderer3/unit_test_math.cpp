#include "unit_test_math.h"
#include "math.h"
#include <math.h>
#include <assert.h>

#define EPSILON 0.00005

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

void TestVec4Constructor()
{
    LOG_UNIT_TEST();
    Vector4 foo(0.0f, 0.0f, 0.0f, 0.0f);
    assert(foo.x == 0.0);
    assert(foo.y == 0.0);
    assert(foo.z == 0.0);
    assert(foo.w == 0.0);
    Vector4 bar(2.2f, 3.3f, 4.4f, 5.5f);
    assert(fabs(bar.x - 2.2f) < EPSILON);
    assert(fabs(bar.y - 3.3f) < EPSILON);
    assert(fabs(bar.z - 4.4f) < EPSILON);
    assert(fabs(bar.w - 5.5f) < EPSILON);
}

void TestVec4Addition()
{
    LOG_UNIT_TEST();
    Vector4 foo(2.2f, 3.3f, 4.4f, 5.5f);
    Vector4 bar(2.2f, 3.3f, 4.4f, 5.5f);
    bar += foo;
    assert(fabs(bar.x - 4.4f) < EPSILON);
    assert(fabs(bar.y - 6.6f) < EPSILON);
    assert(fabs(bar.z - 8.8f) < EPSILON);
    assert(fabs(bar.w - 11.0f) < EPSILON);
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

void TestMatrixTranslate()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("Identity:\n");
    PrettyPrintRow(foo);

    logmsg("Translate by (2, 3, 4):\n");
    foo.Translate(2.0f, 3.0f, 4.0f);
    PrettyPrintRow(foo);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (0 == i && 3 == j)
            {
                assert(fabs(foo.arr[i][j] - 2.0) < EPSILON);
                continue;
            }
            else if (1 == i && 3 == j)
            {
                assert(fabs(foo.arr[i][j] - 3.0) < EPSILON);
                continue;
            }
            else if (2 == i && 3 == j)
            {
                assert(fabs(foo.arr[i][j] - 4.0) < EPSILON);
                continue;
            }
            else if (i == j)
            {
                assert(fabs(foo.arr[i][j] - 1.0) < EPSILON);
                continue;
            }
            else
                assert(fabs(foo.arr[i][j]) < EPSILON);
        }
    }
}

void TestMatrixMultiplyVec()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("foo scaled by (2, 3, 4):\n");
    foo.Scale(2.0f, 3.0f, 4.0f);
    PrettyPrintRow(foo);

    Vector4 vec(2.0f, 3.0f, 4.0f, 5.0f);
    logmsg("Multiply with vector (2, 3, 4, 5):\n");
    Vector4 result = foo * vec;
    logmsg("result = (%.1f, %.1f, %.1f, %.1f)\n", result.x, result.y, result.z, result.w);
    assert(fabs(result.x - 4.0) < EPSILON);
    assert(fabs(result.y - 9.0) < EPSILON);
    assert(fabs(result.z - 16.0) < EPSILON);
    assert(fabs(result.w - 5.0) < EPSILON);

}

void TestMatrixMultiplyIdentity()
{
    LOG_UNIT_TEST();
    Mtx44 foo;
    logmsg("foo:\n");
    foo.Scale(1.0f, 2.0f, 1.0f);
    PrettyPrintRow(foo);

    Mtx44 iden;

    logmsg("result = foo . I:\n");
    Mtx44 result = foo * iden;
    PrettyPrintRow(result);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (1 == i && 1 == j)
            {
                assert(fabs(foo.arr[i][j] - 2.0) < EPSILON);
                continue;
            }
            else if (i == j)
            {
                assert(fabs(foo.arr[i][j] - 1.0) < EPSILON);
                continue;
            }
            else
                assert(fabs(foo.arr[i][j]) < EPSILON);
        }
    }
}

void TestMatrixMultiplyMatrix()
{
    LOG_UNIT_TEST();
    Mtx44 mtx1;
    logmsg("mtx1:\n");
    mtx1.Scale(2.0f, 1.0f, 1.0f);
    PrettyPrintRow(mtx1);

    Mtx44 mtx2;
    logmsg("mtx2:\n");
    mtx2.Scale(1.0f, 2.0f, 1.0f);
    PrettyPrintRow(mtx2);

    logmsg("result = mtx1 . mtx2:\n");
    Mtx44 result = mtx1 * mtx2;
    PrettyPrintRow(result);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (0 == i && 0 == j)
            {
                assert(fabs(result.arr[i][j] - 2.0) < EPSILON);
                continue;
            }
            else if (1 == i && 1 == j)
            {
                assert(fabs(result.arr[i][j] - 2.0) < EPSILON);
                continue;
            }
            else if (i == j)
            {
                assert(fabs(result.arr[i][j] - 1.0) < EPSILON);
                continue;
            }
            else
                assert(fabs(result.arr[i][j]) < EPSILON);
        }
    }
}


/*
* 1 2 3 4
* 2 3 4 5
* 3 4 5 6
* 4 5 6 7
*/
void Hardcode1(Mtx44& mat)
{
    mat.arr[0][0] = 1.0f;
    mat.arr[0][1] = mat.arr[1][0] = 2.0f;
    mat.arr[0][2] = mat.arr[2][0] = mat.arr[1][1] = 3.0f;
    mat.arr[0][3] = mat.arr[3][0] = mat.arr[1][2] = mat.arr[2][1] = 4.0f;
    mat.arr[1][3] = mat.arr[3][1] = mat.arr[2][2] = 5.0f;
    mat.arr[2][3] = mat.arr[3][2] = 6.0f;
    mat.arr[3][3] = 7.0f;
}

void TestHardcoded1Matrix()
{
    LOG_UNIT_TEST();
    Mtx44 mat;
    Hardcode1(mat);
    //PrettyPrintRow(mat);
    assert(fabs(mat.arr[0][0] - 1.0) < EPSILON);
    assert(fabs(mat.arr[0][1] - 2.0) < EPSILON);
    assert(fabs(mat.arr[1][0] - 2.0) < EPSILON);
    assert(fabs(mat.arr[0][2] - 3.0) < EPSILON);
    assert(fabs(mat.arr[2][0] - 3.0) < EPSILON);
    assert(fabs(mat.arr[1][1] - 3.0) < EPSILON);
    assert(fabs(mat.arr[0][3] - 4.0) < EPSILON);
    assert(fabs(mat.arr[3][0] - 4.0) < EPSILON);
    assert(fabs(mat.arr[1][2] - 4.0) < EPSILON);
    assert(fabs(mat.arr[2][1] - 4.0) < EPSILON);

    assert(fabs(mat.arr[1][3] - 5.0) < EPSILON);
    assert(fabs(mat.arr[3][1] - 5.0) < EPSILON);
    assert(fabs(mat.arr[2][2] - 5.0) < EPSILON);
    assert(fabs(mat.arr[2][3] - 6.0) < EPSILON);
    assert(fabs(mat.arr[3][2] - 6.0) < EPSILON);
    assert(fabs(mat.arr[3][3] - 7.0) < EPSILON);
}

void TestHardMatrixAssignment()
{ 
    LOG_UNIT_TEST();
    Mtx44 mat;
    Hardcode1(mat);

    Mtx44 duplicate = mat;
    //modifying first index of matrix
    duplicate.arr[0][0] = 99.9f;
    assert(fabs(duplicate.arr[0][0] - 99.9) < EPSILON);
    assert(fabs(mat.arr[0][0] - 1.0) < EPSILON);
}


void TestHardMatrixMultiply()
{

    LOG_UNIT_TEST();
    Mtx44 mat1;
    Hardcode1(mat1);
    Mtx44 mat2;
    Hardcode1(mat2);
    /*
    * 30 40 50 60
    * 40 54 68 82
    * 50 68 86 104
    * 60 82 104 126
    */
    Mtx44 result = mat1 * mat2;

    //sanity checks
    assert(fabs(mat1.arr[0][0] - 1.0) < EPSILON);
    assert(fabs(mat1.arr[3][3] - 7.0) < EPSILON);

    assert(fabs(mat2.arr[0][0] - 1.0) < EPSILON);
    assert(fabs(mat2.arr[3][3] - 7.0) < EPSILON);

    //result
    assert(fabs(result.arr[0][0] - 30.0) < EPSILON);
    assert(fabs(result.arr[0][1] - 40.0) < EPSILON);
    assert(fabs(result.arr[1][0] - 40.0) < EPSILON);
    assert(fabs(result.arr[0][2] - 50.0) < EPSILON);
    assert(fabs(result.arr[2][0] - 50.0) < EPSILON);
    assert(fabs(result.arr[1][1] - 54.0) < EPSILON);
    assert(fabs(result.arr[0][3] - 60.0) < EPSILON);
    assert(fabs(result.arr[3][0] - 60.0) < EPSILON);
    assert(fabs(result.arr[1][2] - 68.0) < EPSILON);
    assert(fabs(result.arr[2][1] - 68.0) < EPSILON);

    assert(fabs(result.arr[1][3] - 82.0) < EPSILON);
    assert(fabs(result.arr[3][1] - 82.0) < EPSILON);
    assert(fabs(result.arr[2][2] - 86.0) < EPSILON);
    assert(fabs(result.arr[2][3] - 104.0) < EPSILON);
    assert(fabs(result.arr[3][2] - 104.0) < EPSILON);
    assert(fabs(result.arr[3][3] - 126.0) < EPSILON);

}


//07 12 01 14
//02 13 08 11
//16 03 10 05
//09 06 15 04
void Hardcode2(Mtx44& mat)
{
    mat.arr[0][0] = 7.0f;
    mat.arr[0][1] = 12.0f;
    mat.arr[0][2] = 1.0f;
    mat.arr[0][3] = 14.0f;
    mat.arr[1][0] = 2.0f;
    mat.arr[1][1] = 13.0f;
    mat.arr[1][2] = 8.0f;
    mat.arr[1][3] = 11.0f;
    mat.arr[2][0] = 16.0f;
    mat.arr[2][1] = 3.0f;
    mat.arr[2][2] = 10.0f;
    mat.arr[2][3] = 5.0f;
    mat.arr[3][0] = 9.0f;
    mat.arr[3][1] = 6.0f;
    mat.arr[3][2] = 15.0f;
    mat.arr[3][3] = 4.0f;
}

void TestHardcoded2Matrix()
{
    LOG_UNIT_TEST();
    Mtx44 mat;
    Hardcode2(mat);
    //PrettyPrintRow(mat);
    assert(fabs(mat.arr[0][0] - 7.0) < EPSILON);
    assert(fabs(mat.arr[0][1] - 12.0) < EPSILON);
    assert(fabs(mat.arr[0][2] - 1.0) < EPSILON);
    assert(fabs(mat.arr[0][3] - 14.0) < EPSILON);
    assert(fabs(mat.arr[1][0] - 2.0) < EPSILON);
    assert(fabs(mat.arr[1][1] - 13.0) < EPSILON);
    assert(fabs(mat.arr[1][2] - 8.0) < EPSILON);
    assert(fabs(mat.arr[1][3] - 11.0) < EPSILON);
    assert(fabs(mat.arr[2][0] - 16.0) < EPSILON);
    assert(fabs(mat.arr[2][1] - 3.0) < EPSILON);
    assert(fabs(mat.arr[2][2] - 10.0) < EPSILON);
    assert(fabs(mat.arr[2][3] - 5.0) < EPSILON);
    assert(fabs(mat.arr[3][0] - 9.0) < EPSILON);
    assert(fabs(mat.arr[3][1] - 6.0) < EPSILON);
    assert(fabs(mat.arr[3][2] - 15.0) < EPSILON);
    assert(fabs(mat.arr[3][3] - 4.0) < EPSILON);
}

void TestMatrixTranspose()
{
    LOG_UNIT_TEST();
    Mtx44 mat;
    Hardcode2(mat);

    mat.Transpose();
    //PrettyPrintRow(mat);
    assert(fabs(mat.arr[0][0] - 7.0) < EPSILON);
    assert(fabs(mat.arr[0][1] - 2.0) < EPSILON);
    assert(fabs(mat.arr[0][2] - 16.0) < EPSILON);
    assert(fabs(mat.arr[0][3] - 9.0) < EPSILON);
    assert(fabs(mat.arr[1][0] - 12.0) < EPSILON);
    assert(fabs(mat.arr[1][1] - 13.0) < EPSILON);
    assert(fabs(mat.arr[1][2] - 3.0) < EPSILON);
    assert(fabs(mat.arr[1][3] - 6.0) < EPSILON);
    assert(fabs(mat.arr[2][0] - 1.0) < EPSILON);
    assert(fabs(mat.arr[2][1] - 8.0) < EPSILON);
    assert(fabs(mat.arr[2][2] - 10.0) < EPSILON);
    assert(fabs(mat.arr[2][3] - 15.0) < EPSILON);
    assert(fabs(mat.arr[3][0] - 14.0) < EPSILON);
    assert(fabs(mat.arr[3][1] - 11.0) < EPSILON);
    assert(fabs(mat.arr[3][2] - 5.0) < EPSILON);
    assert(fabs(mat.arr[3][3] - 4.0) < EPSILON);
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
    TestVec4Constructor();
    TestVec4Addition();
    TestVec4DotProduct();
    //=======================================
    //Matrix
    TestMatrixScale();
    TestMatrixTranslate();
    TestMatrixMultiplyVec();
    TestMatrixMultiplyIdentity();
    TestMatrixMultiplyMatrix();
    //Hard-coded
    TestHardcoded1Matrix();
    TestHardMatrixAssignment();
    TestHardMatrixMultiply();
    TestHardcoded2Matrix();
    TestMatrixTranspose();

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

