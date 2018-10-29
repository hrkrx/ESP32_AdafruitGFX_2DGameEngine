class Vector4
{
    public:
    float X;
    float Y;
    float Z;
    float W;
    float Get(int index);
    Vector4 operator+(const Vector4& other);
    float operator*(const Vector4& other);
    private:
};