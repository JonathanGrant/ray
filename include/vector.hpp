#include <cstddef>

class Vector3D {
public:
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}

    float get(std::size_t pos) const;
    void set(std::size_t pos, float val);

    float distance(const Vector3D& other) const;
    float magnitude() const;

    Vector3D add(const Vector3D& other) const;
    Vector3D operator+(const Vector3D& other) const { return add(other); };

    Vector3D sub(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const { return sub(other); };

    Vector3D mul(float scalar) const;
    Vector3D operator*(float scalar) const { return mul(scalar); };

    Vector3D div(float scalar) const;
    Vector3D operator/(float scalar) const { return div(scalar); };

    // Complex operations
    float dot(const Vector3D& other) const;
    float angle(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;

    // Norms
    float l1Norm() const;
    float l2Norm() const;
    float linfNorm() const;
    float norm() const;

    float x, y, z;
private:
};
