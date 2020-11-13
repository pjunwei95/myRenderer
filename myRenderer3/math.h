#pragma once
#include "logger.h"
#include <immintrin.h>
#include <stdint.h>

struct Vector2
{
    __m128i m_Data;

    Vector2()
        :m_Data{ _mm_set1_epi32(0)}
    {
    }

    Vector2(uint32_t x, uint32_t y)
        : m_Data{ _mm_set_epi32(x, y, 0, 0) }
    {
    }

    //Rules of three: copy constructor, copy assignment, destructor
    ~Vector2() {}
    Vector2(Vector2& other) { m_Data = _mm_set_epi32(other.X(), other.Y(), 0, 0); }
    Vector2 operator=(Vector2& rhs)
    { 
        Vector2 copy(rhs);
        return rhs;
    }

    friend Vector2 operator+(Vector2 &lhs, Vector2& rhs)
    {
        Vector2 result;
        result.m_Data = _mm_add_epi32(lhs.m_Data, rhs.m_Data);
        return result;
    }

    uint32_t X() { return m_Data.m128i_i32[3]; }
    uint32_t Y() { return m_Data.m128i_i32[2]; }
};

void Sample1()
{
    LOG_UNIT_TEST();
    __m128i a{ 1,2,3,4 };
    __m128i b{ 2,3,4,5 };
    __m128i result = _mm_add_epi32(a, b);
    logmsg("result = %i\n", result.m128i_i32[0]);
}

void Sample2()
{
    LOG_UNIT_TEST();
    //Guide to Intrinsics
    __m128 vector = _mm_set_ps(1.0, 1.0, 1.0, 1.0);
    __m128 vector2 = _mm_set_ps1(1.0);
    vector = _mm_add_ps(vector, vector2);
    logmsg("add: v1,v2 = %f\n", vector.m128_f32[1]);
    //other ops
    //vector = _mm_sub_ps(vector, vector2);
    //vector = _mm_mul_ps(vector, vector2);
    //vector = _mm_div_ps(vector, vector2);
    float array[4];
    _mm_store_ps(array, vector);
    logmsg("array[1] = %f\n", array[1]);
}

void TestVec2Copy()
{
    LOG_UNIT_TEST();
    Vector2 a{1,2};
    logmsg("a = (%i, %i)\nCopy a to b\n", a.X(), a.Y());
    Vector2 b(a);
    logmsg("b.x, b.y = (%i, %i)\n", b.X(), b.Y());
}

void TestVec2Assignment()
{
    LOG_UNIT_TEST();
    Vector2 a(1, 2);
    logmsg("a = (%i, %i)\nSet b = a\n", a.X(), a.Y());
    Vector2 b = a;
    logmsg("b.x, b.y = (%i, %i)\n", b.X(), b.Y());
}

void TestVec2Addition()
{
    LOG_UNIT_TEST();
    //Vector2 foo{ 1.0, 2.0 };
    //Vector2 bar = { 1.0, 2.0 };

    //Vector2 baz = foo + bar;
    //operator+, -, *, / , cross_pdt, dot_pdt
}

void TestMath()
{
    LOG_TEST(Math);
    Sample1();
    Sample2();
    TestVec2Copy();
    TestVec2Assignment();
    //TestAddition();
}


//Deliverables
//Math library

//m128 a{ 1,2,3,4 };
//m128 b{ 2,3,4,5 };
//
//m128 result = _mm_add_epi32(a, b);
//
//struct Vector2;
//struct Vector3;
//struct Vector4;
//struct Matrix44;
//OrthographicMatrix
//PerspectiveMatrix;

