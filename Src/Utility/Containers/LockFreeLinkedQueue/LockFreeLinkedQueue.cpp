#include "LockFreeLinkedQueue.hpp"
#include <string>

// float templates
template class Conure::Utility::LockFreeLinkedQueue<float>;
template class Conure::Utility::LockFreeLinkedQueue<double>;

// 8-bit integer templates
template class Conure::Utility::LockFreeLinkedQueue<int8_t>;
template class Conure::Utility::LockFreeLinkedQueue<uint8_t>;

// 16-bit integer templates
template class Conure::Utility::LockFreeLinkedQueue<int16_t>;
template class Conure::Utility::LockFreeLinkedQueue<uint16_t>;

// 32-bit integer templates
template class Conure::Utility::LockFreeLinkedQueue<int32_t>;
template class Conure::Utility::LockFreeLinkedQueue<uint32_t>;

// 64-bit integer templates
template class Conure::Utility::LockFreeLinkedQueue<int64_t>;
template class Conure::Utility::LockFreeLinkedQueue<uint64_t>;

// String template
template class Conure::Utility::LockFreeLinkedQueue<std::string>;