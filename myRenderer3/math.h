#pragma once
#include "logger.h"
#include <stdint.h>

struct Vector2
{
    float x;
    float y;

    Vector2(float _x, float _y)
        : x{ _x }, y{ _y }
    {
    }

    //TOOD: Add constructor to convert from vec3, vec4 to vec2

    Vector2& operator+=(const Vector2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2& negate()
    {
        x *= -1;
        y *= -1;
        return *this;
    }

    //================================================
    //transformation
    Vector2& operator+=(float scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
};

float dot(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

//gives magnitude
float cross(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    Vector2 result = lhs;
    result += rhs;
    return result;
}

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
        : x{ _x }, y{ _y }, z{_z}
    {
    }

    Vector3& operator+=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    //================================================
    //transformation
    Vector3& operator+=(float scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    Vector3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
};

float dot(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 cross(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return result;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result = lhs;
    result += rhs;
    return result;
}

struct Vector4
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    Vector4(float _x = 0.0f, float _y = 0.0f,
            float _z = 0.0f, float _w = 0.0f)
        : x{ _x }, y{ _y }, z{ _z }, w{ _w}
    {
    }

    Vector4& operator+=(const Vector4& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    //================================================
    //transformation
    Vector4& operator+=(float scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }
    Vector4& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
};

float dot(const Vector4& lhs, const Vector4& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w + rhs.w;
}

struct Mtx44
{
    float arr[4][4] = { 0.0f };

    Mtx44()
    {
        for (int i = 0; i < 4; ++i)
        {
            arr[i][i] = 1.0f;
        }
    }

    void Scale(float x, float y, float z)
    {
        arr[0][0] *= x;
        arr[1][1] *= y;
        arr[2][2] *= z;
    }

    void Translate(float x, float y, float z)
    {
        arr[0][3] += x;
        arr[1][3] += y;
        arr[2][3] += z;
    }

    Mtx44& Transpose()
    {
        Mtx44 trans;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                trans.arr[i][j] = arr[j][i];
            }
        }

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                arr[i][j] = trans.arr[i][j];
            }
        }

        return *this;
    }


    // this.row x other.col
    // strassen's method has better time complexity (omega(n^2.81))
    friend Mtx44 operator*(const Mtx44& lhs, const Mtx44& rhs)
    {
        Mtx44 result;

        //Set Identity matrix result to zero
        for (int i = 0; i < 4; ++i)
        {
            result.arr[i][i] = 0.0f;
        }

        // triple for loops
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    result.arr[i][j] += lhs.arr[i][k] * rhs.arr[k][j];
                }
            }
        }
        return result;
    }


    //void Mtx44RotateClockWise(float x, float y, float z)
    //{

    //}

};
Vector4 operator*(const Mtx44& mtx, const Vector4& v)
{
    Vector4 result;
    for (int i = 0; i < 4; ++i)
    {
        result.x += mtx.arr[0][i] * v.x;
        result.y += mtx.arr[1][i] * v.y;
        result.z += mtx.arr[2][i] * v.z;
        result.w += mtx.arr[3][i] * v.w;
    }
    return result;
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

//struct Vector2
//{
//    __m128i m_Data;
//
//    Vector2()
//        :m_Data{ _mm_set1_epi32(0)}
//    {
//    }
//
//    Vector2(uint32_t x, uint32_t y)
//        : m_Data{ _mm_set_epi32(0, 0, y, x) }
//    {
//    }
//
//    //Rules of three: copy constructor, copy assignment, destructor
//    ~Vector2() {}
//    Vector2(const Vector2& other) { m_Data = _mm_set_epi32(0, 0, other.Y(), other.X()); }
//    Vector2 operator=(const Vector2& rhs)
//    { 
//        m_Data = rhs.m_Data;
//        return *this;
//    }
//
//
//
//    Vector2 operator+=(Vector2&rhs) 
//    {
//        m_Data = _mm_add_epi32(m_Data, rhs.m_Data); 
//        //_mm_add
//        return *this; 
//    }
//
//    friend uint32_t dot(Vector2& lhs, Vector2& rhs)
//    {
//        __m128i product = _mm_mul_epi32(lhs.m_Data, rhs.m_Data);
//        uint32_t scalar = product.m128i_i32[0] + product.m128i_i32[1];
//        //uint32_t foo;
//        //__m128i result = _mm_dp_ps(lhs.m_Data, rhs.m_Data, foo);
//        //logmsg("scalar = %i, foo = %i, result.x = %i\n", scalar, foo, )
//        return scalar;
//    }
//
//    uint32_t X() const { return m_Data.m128i_i32[0]; }
//    uint32_t Y() const { return m_Data.m128i_i32[1]; }
//};
//Vector2 operator+(const Vector2 &lhs, const Vector2& rhs)
//{
//    Vector2 result;
//    result.m_Data = _mm_add_epi32(lhs.m_Data, rhs.m_Data);
//    return result;
//}

