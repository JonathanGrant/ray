#pragma once

#include <stdexcept>
#include <memory>
#include <iterator>
#include <cstdint>
#include <algorithm>


template <typename T>
class VectorData {
public:
    VectorData(std::unique_ptr<unsigned char[]> data, size_t length, size_t stride = 1)
        : _data(std::move(data)), _length(length), _stride(stride) {}
    VectorData(const unsigned char* data, size_t length, size_t stride = 1)
        : _data(std::make_unique<unsigned char[]>(stride * sizeof(T) * length)), _length(length), _stride(stride) {
        std::copy(data, data + stride * sizeof(T) * length, _data.get());
    }

    VectorData(size_t size) : _length(size), _stride(1) {
        _data = std::make_unique<unsigned char[]>(size * sizeof(T));
    }
    VectorData(const std::vector<T>& vec) : VectorData(vec.size()) {
        for (size_t i = 0; i < vec.size(); ++i) {
            set(i, vec[i]);
        }
    }

    VectorData(const VectorData& other): _length(other._length), _stride(other._stride) {
        // Calculate total bytes
        size_t total_bytes = other.byteSize() * other.length();

        // Allocate new array on the heap
        _data = std::make_unique<unsigned char[]>(total_bytes);

        // Copy data from the other object
        std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
    }

    VectorData& operator=(const VectorData& other) {
        if (this != &other) {
            _length = other._length;
            _stride = other._stride;

            // Calculate total bytes
            size_t total_bytes = byteSize() * _length;

            // Allocate new array on the heap
            _data = std::make_unique<unsigned char[]>(total_bytes);

            // Copy data from the other object
            std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
        }
        return *this;
    }

    const size_t length() const { return _length; };
    const size_t stride() const { return _stride; };
    const size_t byteSize() const { return _stride * sizeof(T); };

    void resize(size_t new_length) {
        std::unique_ptr<unsigned char[]> new_data = std::make_unique<unsigned char[]>(byteSize() * new_length);
        std::copy(_data.get(), _data.get() + std::min(_length, new_length) * byteSize(), new_data.get());
        _data = std::move(new_data);
        _length = new_length;
    }

    //Iterator
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(VectorData* array, size_t idx = 0) : m_array(array), m_idx(idx) {}

        reference operator*() const { return m_array->get(m_idx); }
        pointer operator->() { return &m_array->get(m_idx); }
        Iterator& operator++() { m_idx++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; m_idx++; return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_idx == b.m_idx; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_idx != b.m_idx; }
    private:
        VectorData* m_array;
        size_t m_idx;
    };

    class ConstIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        ConstIterator(const VectorData* array, size_t idx = 0) : m_array(array), m_idx(idx) {}

        reference operator*() const { return m_array->get(m_idx); }
        pointer operator->() { return &m_array->get(m_idx); }
        ConstIterator& operator++() { m_idx++; return *this; }
        ConstIterator operator++(int incr) { ConstIterator tmp = *this; m_idx+=incr; return tmp; }
        friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_idx == b.m_idx; }
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_idx != b.m_idx; }

    private:
        const VectorData* m_array;
        size_t m_idx;
    };

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, _length); }

    ConstIterator begin() const { return ConstIterator(this, 0); }
    ConstIterator end() const { return ConstIterator(this, _length); }

    T& get(size_t idx) {
        // Non-const version
        if (idx >= _length) {
            throw std::out_of_range("Index out of bounds.");
        }
        return const_cast<T&>(const_cast<const VectorData*>(this)->get(idx));
    }

    const T& get(size_t idx) const {
        // Const version
        if (idx >= _length) {
            throw std::out_of_range("Index out of bounds.");
        }
        size_t start_idx = idx * byteSize();
        return *reinterpret_cast<const T*>(_data.get() + start_idx);
    }

    void set(size_t idx, T val) {
        if (idx >= _length) {
            throw std::out_of_range("Index out of bounds.");
        }
        *reinterpret_cast<T*>(&_data[idx * byteSize()]) = val;
    }

    // Arithmetic
    T sum() const {
        T total = 0;
        for(auto it = begin(); it != end(); ++it) {
            total += *it;
        }
        return total;
    }

    template<typename F>
    VectorData binary_op(T constant, F op) const {
        size_t step_size = byteSize();
        std::unique_ptr<unsigned char[]> new_data = std::make_unique<unsigned char[]>(step_size * _length);
        for(size_t idx = 0; idx < _length; ++idx) {
            *reinterpret_cast<T*>(&new_data[idx*step_size]) = op(get(idx), constant);
        }
        return VectorData(std::move(new_data), _length, _stride);
    }

    template<typename F>
    void binary_op_inplace(T constant, F op) {
        size_t step_size = byteSize();
        for(size_t idx = 0; idx < _length; ++idx) {
            *reinterpret_cast<T*>(&_data[idx*step_size]) = op(get(idx), constant);
        }
    }

    #define DEFINE_BINARY_OP(OP, FUNC) \
        VectorData operator OP(T constant) const { \
            return binary_op(constant, FUNC); \
        }
    #define DEFINE_BINARY_OP_INPLACE(OP, FUNC) \
        void operator OP(T constant) { \
            binary_op_inplace(constant, FUNC); \
        }

    DEFINE_BINARY_OP(+, [](T a, T b) { return a + b; })
    DEFINE_BINARY_OP(-, [](T a, T b) { return a - b; })
    DEFINE_BINARY_OP(*, [](T a, T b) { return a * b; })
    DEFINE_BINARY_OP(/, [](T a, T b) { return a / b; })
    DEFINE_BINARY_OP(%, [](T a, T b) { return a % b; })

    DEFINE_BINARY_OP_INPLACE(+=, [](T a, T b) { return a + b; })
    DEFINE_BINARY_OP_INPLACE(-=, [](T a, T b) { return a - b; })
    DEFINE_BINARY_OP_INPLACE(*=, [](T a, T b) { return a * b; })
    DEFINE_BINARY_OP_INPLACE(/=, [](T a, T b) { return a / b; })

    #undef DEFINE_BINARY_OP_INPLACE
    #undef DEFINE_BINARY_OP

    VectorData operator+(const VectorData& other) const {
        if (_length != other._length) {
            throw std::length_error("Vectors must be the same length for addition.");
        }
        VectorData sum = VectorData(*this);
        for(size_t i = 0; i < length(); i++) {
            sum.set(i, get(i) + other.get(i));
        }
        return sum;
    }
    VectorData operator-(const VectorData& other) const { return operator+(other * -1); }

    VectorData operator*(const VectorData& other) const {
        if (_length != other._length) {
            throw std::length_error("Vectors must be the same length for multiplication.");
        }
        VectorData prod = VectorData(*this);
        for(size_t i = 0; i < length(); i++) {
            prod.set(i, get(i) * other.get(i));
        }
        return prod;
    }
    VectorData operator/(const VectorData& other) const {
        if (_length != other._length) {
            throw std::length_error("Vectors must be the same length for division.");
        }
        VectorData prod = VectorData(*this);
        for(size_t i = 0; i < length(); i++) {
            prod.set(i, get(i) / other.get(i));
        }
        return prod;
    }

private:
    std::unique_ptr<unsigned char[]> _data;
    size_t _length;
    size_t _stride;
};
