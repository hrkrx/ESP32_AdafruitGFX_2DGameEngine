 #include "Vector4.h"

 class Matrix4x4
 {
    public:
    float Get(int i, int j);
    Vector4 operator*(const Vector4& other);
    private:
 };