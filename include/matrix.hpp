#include <vector>
#include "vector.hpp"

class Matrix3D {
public:
    Matrix3D(std::size_t rows) { _data = std::vector<Vector3D>(rows); }
    Matrix3D(std::vector<Vector3D> data): _data(data) {}

    std::size_t rows() const { return _data.size(); }
    const Vector3D& get(std::size_t row) const { return _data[row]; }
    float get(std::size_t row, std::size_t col) const { return _data[row].get(col); }
    void set(std::size_t row, std::size_t col, float val) { _data[row].set(col, val); }
    void set(std::size_t row, Vector3D vec) { _data[row] = vec; }

    Matrix3D add(const Vector3D& other) const;
    Matrix3D operator+(const Vector3D& other) const { return add(other); };
    Matrix3D add(const Matrix3D& other) const;
    Matrix3D operator+(const Matrix3D& other) const { return add(other); };

    Matrix3D sub(const Vector3D& other) const;
    Matrix3D operator-(const Vector3D& other) const { return sub(other); };
    Matrix3D sub(const Matrix3D& other) const;
    Matrix3D operator-(const Matrix3D& other) const { return sub(other); };

    Matrix3D mul(float scalar) const;
    Matrix3D operator*(float scalar) const { return mul(scalar); };
    Matrix3D div(float scalar) const;
    Matrix3D operator/(float scalar) const { return div(scalar); };

    Vector3D dot(const Vector3D& other) const;
    Matrix3D mul(const Matrix3D& other) const;
    Matrix3D operator*(const Matrix3D& other) const {return mul(other);};

    Matrix3D transpose() const;
    float determinant() const;
    float minor(size_t row, size_t col) const;
    Matrix3D cofactor() const;
    Matrix3D adjoint() const { return cofactor().transpose(); };
    Matrix3D inverse() const { return adjoint() / determinant(); };

    bool isSquare() const { return rows() == 3; }
    float trace() const;
    Matrix3D normalize() const { return div(determinant()); }

private:
    std::vector<Vector3D> _data;
};
