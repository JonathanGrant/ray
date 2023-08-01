#include "matrix.hpp"
#include <vector>
#include <vector>

Matrix3D Matrix3D::add(const Vector3D& other) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] + other);
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::add(const Matrix3D& other) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] + other.get(i));
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::sub(const Vector3D& other) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] - other);
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::sub(const Matrix3D& other) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] - other.get(i));
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::mul(float scalar) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] * scalar);
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::div(float scalar) const {
    std::vector<Vector3D> vecs;
    for (size_t i = 0; i < rows(); i++) {
        vecs.push_back(_data[i] / scalar);
    }
    return Matrix3D(vecs);
}

Vector3D Matrix3D::dot(const Vector3D& other) const {
    assert(rows() == 3);
    return Vector3D(
        _data[0].dot(other),
        _data[1].dot(other),
        _data[2].dot(other)
    );
}

Matrix3D Matrix3D::transpose() const {
    assert(rows() == 3);
    std::vector<Vector3D> vecs;
    for(std::size_t i = 0; i < 3; i++) {
        vecs.push_back(Vector3D(_data[0].get(i), _data[1].get(i), _data[2].get(i)));
    }
    return Matrix3D(vecs);
}

Matrix3D Matrix3D::mul(const Matrix3D& other) const {
    assert(rows() == other.rows());
    assert(rows() == 3);
    std::vector<Vector3D> vecs;
    Matrix3D other_t = other.transpose();
    for (std::size_t i = 0; i < rows(); i++) {
        vecs.push_back(
            Vector3D(
                _data[i].dot(other_t.get(0)),
                _data[i].dot(other_t.get(1)),
                _data[i].dot(other_t.get(2))
            )
        );
    }
    return Matrix3D(vecs);
}

float Matrix3D::determinant() const {
    assert(rows() == 3);
    return (
        _data[0].get(0) * (_data[1].get(1) * _data[2].get(2) - _data[1].get(2) * _data[2].get(1)) -
        _data[0].get(1) * (_data[1].get(0) * _data[2].get(2) - _data[1].get(2) * _data[2].get(0)) +
        _data[0].get(2) * (_data[1].get(0) * _data[2].get(1) - _data[1].get(1) * _data[2].get(0))
    );
}

float Matrix3D::minor(size_t row, size_t col) const {
    size_t rowA, rowB, colA, colB;
    switch(row) {
        case 0:
            rowA = 1;
            rowB = 2;
            break;
        case 1:
            rowA = 0;
            rowB = 2;
            break;
        case 2:
            rowA = 0;
            rowB = 1;
            break;
    }
    switch(col) {
        case 0:
            colA = 1;
            colB = 2;
            break;
        case 1:
            colA = 0;
            colB = 2;
            break;
        case 2:
            colA = 0;
            colB = 1;
            break;
    }
    return _data[rowA].get(colA) * _data[rowB].get(colB) - _data[rowA].get(colB) * _data[rowB].get(colA);
}

Matrix3D Matrix3D::cofactor() const {
    std::vector<Vector3D> vecs;
    for(size_t i = 0; i < rows(); i++) {
        vecs.push_back(Vector3D(
            minor(i, 0),
            minor(i, 1),
            minor(i, 2)
        ));
    }
    return Matrix3D(vecs);
}

float Matrix3D::trace() const {
    float sum = 0;
    for(size_t i = 0; i < rows(); i++) {
        sum += _data[i].get(i);
    }
    return sum;
}
