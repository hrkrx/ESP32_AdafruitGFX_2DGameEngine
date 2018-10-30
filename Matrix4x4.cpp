#include "Matrix4x4.h"

Vector4 Matrix4x4::operator*(const Vector4& other)
{
    float x;
    float y;
    float z;
    float w;

    x = firstColumn.X * other.X + secondColumn.X * other.Y + thirdColumn.X * other.Z + fourthColumn.X * other.W;
    y = firstColumn.Y * other.X + secondColumn.Y * other.Y + thirdColumn.Y * other.Z + fourthColumn.Y * other.W;
    z = firstColumn.Z * other.X + secondColumn.Z * other.Y + thirdColumn.Z * other.Z + fourthColumn.Z * other.W;
    w = firstColumn.W * other.X + secondColumn.W * other.Y + thirdColumn.W * other.Z + fourthColumn.W * other.W;

    Vector4 result = *new Vector4();
    result.X = x;
    result.Y = y;
    result.Z = z;
    result.W = w;

    return result;
}