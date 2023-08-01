#include "vector.hpp"
#include <cmath>
#include <algorithm>

float Vector3D::get(size_t pos) const {
    switch(pos) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return 0; // TODO: throw exception
    }
}

void Vector3D::set(size_t pos, float val) {
    switch(pos) {
        case 0:
            x = val;
            break;
        case 1:
            y = val;
            break;
        case 2:
            z = val;
            break;
        default:
            return; // TODO: throw exception
    }
}

float Vector3D::distance(const Vector3D& other) const {
    return std::sqrt(
        pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2)
    );
}

float Vector3D::magnitude() const {
    return std::sqrt(
        pow(x, 2) + pow(y, 2) + pow(z, 2)
    );
}

Vector3D Vector3D::add(const Vector3D& other) const {
    return Vector3D(x+other.x, y+other.y, z+other.z);
}

Vector3D Vector3D::sub(const Vector3D& other) const {
    return Vector3D(x-other.x, y-other.y, z-other.z);
}

Vector3D Vector3D::mul(float scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::div(float scalar) const {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

float Vector3D::dot(const Vector3D& other) const {
    return x*other.x + y*other.y + z*other.z;
}

float Vector3D::angle(const Vector3D& other) const {
    // a * b = |a| * |b| * cos(theta)
    // theta = cos-1 [ (a · b) / (|a| |b|) ]
    float dot_prod = dot(other);
    float denom = magnitude() * other.magnitude();
    // TODO OPTIMIZATION: Calculate magnitudes in parallel?
    return std::acos(dot_prod / denom);
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    //(a2b3 - a3b2), (a1b3 - a3b1), (a1b2 - a2b1)
    // TODO OPTIMIZATION: Calculate x,y,z in parallel?
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3D::l1Norm() const {
    return std::abs(x) + std::abs(y) + std::abs(z);
}

float Vector3D::l2Norm() const {
    return magnitude();
}

float Vector3D::linfNorm() const {
    return std::max(std::max(std::abs(x), std::abs(y)), std::abs(z));
}

float Vector3D::norm() const {
    return std::max(std::max(l1Norm(), l2Norm()), linfNorm());
}
