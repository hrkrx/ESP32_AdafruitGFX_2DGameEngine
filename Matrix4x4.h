 #include "Vector4.h"

 class Matrix4x4
 {
    public:
    Vector4 firstColumn;
    Vector4 secondColumn;
    Vector4 thirdColumn;
    Vector4 fourthColumn;
    float Get(int i, int j);
    Vector4 operator*(const Vector4& other);
    private:
 };