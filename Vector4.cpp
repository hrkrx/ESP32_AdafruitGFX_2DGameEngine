#include "Vector4.h"

Vector4 Vector4::operator+(const Vector4& other)
{
    float newX = X + other.X;
    float newY = Y + other.Y;
    float newZ = Z + other.Z;
    float newW = W + other.W;

    Vector4* result = new Vector4();
    result->X = newX;
    result->Y = newX;
    result->Z = newX;
    result->W = newX;

    return *result;
}

float Vector4::operator*(const Vector4& other)
{
    return X * other.X + Y * other.Y + Z * other.Z + W * other.W; 
}

float Vector4::Get(int i)
{
    if(i == 0)
    {
        return X;
    }
    else if (i == 1)
    {
        return Y;
    }
    else if (i == 2)
    {
        return Z;
    }
    else if (i == 3)
    {
        return W;
    }
}