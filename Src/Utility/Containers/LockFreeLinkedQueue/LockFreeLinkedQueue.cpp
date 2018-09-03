#include "LockFreeLinkedQueue.hpp"
#include <string>

// float templates
template class C2D::LockFreeLinkedQueue<float>;
template class C2D::LockFreeLinkedQueue<double>;

// 8-bit integer templates
template class C2D::LockFreeLinkedQueue<int8_t>;
template class C2D::LockFreeLinkedQueue<uint8_t>;

// 16-bit integer templates
template class C2D::LockFreeLinkedQueue<int16_t>;
template class C2D::LockFreeLinkedQueue<uint16_t>;

// 32-bit integer templates
template class C2D::LockFreeLinkedQueue<int32_t>;
template class C2D::LockFreeLinkedQueue<uint32_t>;

// 64-bit integer templates
template class C2D::LockFreeLinkedQueue<int64_t>;
template class C2D::LockFreeLinkedQueue<uint64_t>;

// String template
template class C2D::LockFreeLinkedQueue<std::string>;