#pragma once
//=============================================================================================
//Vector2
struct Vector2
{
    float x;
    float y;

    Vector2(float _x, float _y)
        : x{ _x }, y{ _y }
    {
    }

    //TOOD: Add constructor to convert from vec3, vec4 to vec2

    Vector2& operator+=(const Vector2& rhs);
    Vector2& negate();

    //================================================
    //transformation
    Vector2& operator+=(float scalar);
    Vector2& operator*=(float scalar);
};

float dot(const Vector2& lhs, const Vector2& rhs);
float cross(const Vector2& lhs, const Vector2& rhs); //gives magnitude
Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

//=============================================================================================
//Vector3
struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
        : x{ _x }, y{ _y }, z{_z}
    {
    }

    Vector3& operator+=(const Vector3& rhs);

    //================================================
    //transformation
    Vector3& operator+=(float scalar);
    Vector3& operator*=(float scalar);
};

float dot(const Vector3& lhs, const Vector3& rhs);
Vector3 cross(const Vector3& lhs, const Vector3& rhs);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

//=============================================================================================
//Vector4
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

    Vector4& operator+=(const Vector4& rhs);

    //================================================
    //transformation
    Vector4& operator+=(float scalar);
    Vector4& operator*=(float scalar);
};

float dot(const Vector4& lhs, const Vector4& rhs);

//=============================================================================================
//Matrix 4x4
struct Mtx44
{
    float arr[4][4] = { 0.0f };

    Mtx44();

    void Scale(float x, float y, float z);

    void Translate(float x, float y, float z);

    //void Mtx44RotateClockWise(float x, float y, float z)

    Mtx44& Transpose();
};
// this.row x other.col
// strassen's method has better time complexity (omega(n^2.81))
Mtx44 operator*(const Mtx44& lhs, const Mtx44& rhs);

Vector4 operator*(const Mtx44& mtx, const Vector4& v);

