#include <vector>
#include "vector.hpp"


template <typename T>
class MatrixND {
public:
    MatrixND(std::size_t rows) { _data = std::vector<VectorND<T>>(rows); }
    MatrixND(std::vector<VectorND<T>> data): _data(data) {}

    std::size_t rows() const { return _data.size(); }
    std::size_t cols() const { if(rows() > 0) return _data[0].size(); return 0; }
    const VectorND<T>& get(std::size_t row) const { return _data[row]; }
    T get(std::size_t row, std::size_t col) const { return get(row).get(col); }
    void set(std::size_t row, std::size_t col, T val) { _data[row].set(col, val); }
    void set(std::size_t row, const VectorND<T>& vec) { _data[row] = vec; }

    MatrixND add(T scalar) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) + scalar);
        }
        return MatrixND(vecs);
    }
    MatrixND operator+(T scalar) const { return add(scalar); };
    MatrixND add(const VectorND<T>& other) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) + other);
        }
        return MatrixND(vecs);
    }
    MatrixND operator+(const VectorND<T>& other) const { return add(other); };
    MatrixND add(const MatrixND& other) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) + other.get(i));
        }
        return MatrixND(vecs);
    }
    MatrixND operator+(const MatrixND& other) const { return add(other); };

    MatrixND sub(T scalar) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) - scalar);
        }
        return MatrixND(vecs);
    }
    MatrixND operator-(T scalar) const { return sub(scalar); };
    MatrixND sub(const VectorND<T>& other) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) - other);
        }
        return MatrixND(vecs);
    }
    MatrixND operator-(const VectorND<T>& other) const { return sub(other); };
    MatrixND sub(const MatrixND& other) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) - other.get(i));
        }
        return MatrixND(vecs);
    }
    MatrixND operator-(const MatrixND& other) const { return sub(other); };

    MatrixND mul(T scalar) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) * scalar);
        }
        return MatrixND(vecs);
    }
    MatrixND operator*(T scalar) const { return mul(scalar); };
    MatrixND div(T scalar) const {
        std::vector<VectorND<T>> vecs;
        for (size_t i = 0; i < rows(); i++) {
            vecs.push_back(get(i) / scalar);
        }
        return MatrixND(vecs);
    }
    MatrixND operator/(T scalar) const { return div(scalar); };

    VectorND<T> dot(const VectorND<T>& other) const {
        assert(rows() == other.rows());
        auto data = std::make_unique<VectorData<T>>(new unsigned char[rows()*sizeof(T)], rows());
        for(size_t idx = 0; idx < rows(); idx++) {
            data->set(idx, get(idx).dot(other));
        }
        return VectorND<T>(data);
    }
    MatrixND mul(const MatrixND& other) const {
        assert(rows() == other.rows());
        std::vector<VectorND<T>> vecs;
        MatrixND other_t = other.transpose();
        for (std::size_t i = 0; i < rows(); i++) {
            auto data = std::make_unique<VectorData<T>>(new unsigned char[rows()*sizeof(T)], rows());
            for (std::size_t j = 0; j < rows(); j++) {
                data->set(j, _data[i].dot(other_t.get(j)));
            }
            vecs.push_back(VectorND<T>(std::move(data)));
        }
        return MatrixND(vecs);
    }
    MatrixND operator*(const MatrixND& other) const {return mul(other);};

    MatrixND transpose() const {
        assert(rows() == cols());
        std::vector<VectorND<T>> vecs;
        for(std::size_t i = 0; i < 3; i++) {
            auto data = std::make_unique<VectorData<T>>(new unsigned char[rows()*sizeof(T)], rows());
            for (std::size_t j = 0; j < rows(); j++) {
                data->set(j, get(j).get(i));
            }
            vecs.push_back(VectorND<T>(std::move(data)));
        }
        return MatrixND(vecs);
    }
    MatrixND minorMat(size_t row, size_t col) const {
        std::size_t height = rows()-1;
        std::vector<VectorND<T>> vecs;
        for (std::size_t i = 0; i < height; i++) {
            std::size_t _i = i;
            if (i >= row) _i++;
            auto data = std::make_unique<VectorData<T>>(new unsigned char[(height)*sizeof(T)], height);
            for (std::size_t j = 0; j < height; j++) {
                std::size_t _j = j;
                if (j >= col) _j++;
                data->set(j, get(_i).get(_j));
            }
            vecs.push_back(VectorND<T>(std::move(data)));
        }
        return MatrixND<T>(vecs);
    }
    T determinant() const {
        // Use Laplace's formula to calculate
        assert(rows() == cols());

        // Base case
        if (rows() == 2) {
            // 2x2 matrix, can hardcode the formula
            return _data[0].get(0) * _data[1].get(1) - _data[1].get(0) * _data[0].get(1);
        }

        // Recursion
        T total = 0;
        for (std::size_t col = 0; col < rows(); col++) {
            MatrixND<T> subMatrix = minorMat(0, col);
            std::int8_t sign = pow(-1, col % 2);
            T subDet = subMatrix.determinant();
            total += sign * get(0).get(col) * subDet;
        }
        return total;
    }
    MatrixND cofactor() const {
        std::vector<VectorND<T>> vecs;
        for(size_t i = 0; i < rows(); i++) {
            auto data = std::make_unique<VectorData<T>>(new unsigned char[(rows())*sizeof(T)], rows());
            for (size_t j = 0; j < rows(); j++) {
                data->set(j, minorMat(i, j).determinant());
            }
            vecs.push_back(VectorND<T>(std::move(data)));
        }
        return MatrixND(vecs);
    }
    MatrixND adjoint() const { return cofactor().transpose(); };
    MatrixND inverse() const { return adjoint() / determinant(); };

    bool isSquare() const { return rows() == 3; }
    T trace() const {
        T sum = 0;
        for(size_t i = 0; i < rows(); i++) {
            sum += _data[i].get(i);
        }
        return sum;
    }
    MatrixND normalize() const { return div(determinant()); }

private:
    std::vector<VectorND<T>> _data;
};
