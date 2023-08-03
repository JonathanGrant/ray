// #include "vector_data.hpp"


// template <typename T>
// VectorData<T>::VectorData(const VectorData& other) 
//     : _length(other._length), _stride(other._stride) {
//     // Calculate total bytes
//     size_t total_bytes = byteSize() * _length;

//     // Allocate new array on the heap
//     _data = std::make_unique<unsigned char[]>(total_bytes);

//     // Copy data from the other object
//     std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
// }

// template <typename T>
// VectorData<T>& VectorData<T>::operator=(const VectorData& other) {
//     if (this != &other) {
//         _length = other._length;
//         _stride = other._stride;

//         // Calculate total bytes
//         size_t total_bytes = byteSize() * _length;

//         // Allocate new array on the heap
//         _data = std::make_unique<unsigned char[]>(total_bytes);

//         // Copy data from the other object
//         std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
//     }
//     return *this;
// }

// template <typename T>
// void VectorData<T>::resize(size_t new_length) {
//     std::unique_ptr<unsigned char[]> new_data = std::make_unique<unsigned char[]>(byteSize() * new_length);
//     std::copy(_data.get(), _data.get() + std::min(_length, new_length) * byteSize(), new_data.get());
//     _data = std::move(new_data);
//     _length = new_length;
// }
