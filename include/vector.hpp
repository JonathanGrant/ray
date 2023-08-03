#include "vector_data.hpp"
#include <cstddef>
#include <memory>
#include <cmath>
#include <algorithm>
#include <cstring>


template <typename T>
class VectorND {
public:
    VectorND() {}
    VectorND(VectorData<T> data): _data(std::make_unique<VectorData<T>>(data)) {}
    VectorND(std::unique_ptr<VectorData<T>> data): _data(std::move(data)) {}

    VectorND(const VectorND& other): _data(std::make_unique<VectorData<T>>(*other._data)) {}

    size_t size() const { return _data->length(); }

    T get(std::size_t pos) const { return _data->get(pos); };
    void set(std::size_t pos, T val) { _data->set(pos, val); };
    const VectorData<T>& vectorData() const { return *_data; }

    T distance(const VectorND& other) const {
        T sumSq = 0;
        for(size_t i = 0; i < size(); i++) {
            sumSq += pow(get(i) - other.get(i), 2);
        }
        return std::sqrt(sumSq);
    }
    T magnitude() const {
        T sumSq = 0;
        for(size_t i = 0; i < size(); i++) {
            sumSq += pow(get(i), 2);
        }
        return std::sqrt(sumSq);
    }

    VectorND add(const VectorND& other) const {
        assert (size() == other.size());
        return VectorND(vectorData() + other.vectorData());
    }
    VectorND operator+(const VectorND& other) const { return add(other); };

    VectorND sub(const VectorND& other) const {
        assert (size() == other.size());
        return VectorND(vectorData() - other.vectorData());
    }
    VectorND operator-(const VectorND& other) const { return sub(other); };

    VectorND mul(T scalar) const { return VectorND(vectorData() * scalar); }
    VectorND operator*(T scalar) const { return mul(scalar); };

    VectorND div(T scalar) const { return VectorND(vectorData() / scalar); }
    VectorND operator/(T scalar) const { return div(scalar); };

    // Complex operations
    T dot(const VectorND& other) const {
        assert (size() == other.size());
        return (vectorData() * other.vectorData()).sum();
    }
    T angle(const VectorND& other) const {
        // a * b = |a| * |b| * cos(theta)
        // theta = cos-1 [ (a · b) / (|a| |b|) ]
        T dot_prod = dot(other);
        T denom = magnitude() * other.magnitude();
        // TODO OPTIMIZATION: Calculate magnitudes in parallel?
        return std::acos(dot_prod / denom);
    }

    // Norms
    T l1Norm() const {
        T absSum = 0;
        for (size_t i = 0; i < size(); i++) {
            absSum += std::abs(get(i));
        }
        return absSum;
    }
    T l2Norm() const { return magnitude(); }
    T linfNorm() const {
        T absMax = 0;
        for (size_t i = 0; i < size(); i++) {
            absMax = std::max(absMax, std::abs(get(i)));
        }
        return absMax;
    }
    T norm() const { return std::max(std::max(l1Norm(), l2Norm()), linfNorm()); }

protected:
    std::unique_ptr<VectorData<T>> _data;
};

class Vector3D : public VectorND<float> {
public:

    Vector3D() : VectorND<float>(std::make_unique<VectorData<float>>(new unsigned char[3*sizeof(float)] {0, 0, 0}, 3)) {}
    Vector3D(float x, float y, float z) {
        std::unique_ptr<unsigned char[]> arr(new unsigned char[3*sizeof(float)]);
        std::memcpy(arr.get(), &x, sizeof(float));
        std::memcpy(arr.get() + sizeof(float), &y, sizeof(float));
        std::memcpy(arr.get() + 2*sizeof(float), &z, sizeof(float));
        _data = std::make_unique<VectorData<float>>(std::move(arr), 3);
    }

    Vector3D(const VectorND<float>& vec) : VectorND<float>(vec) {
        assert(size() == 3);
        // The data is already copied in the VectorND<float> copy constructor, so no need to set here
    }

    float x() const { return get(0); };
    float y() const { return get(1); };
    float z() const { return get(2); };

    Vector3D cross(const Vector3D& other) const {
        //(a2b3 - a3b2), (a1b3 - a3b1), (a1b2 - a2b1)
        // TODO OPTIMIZATION: Calculate x,y,z in parallel?
        return Vector3D(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }
};
