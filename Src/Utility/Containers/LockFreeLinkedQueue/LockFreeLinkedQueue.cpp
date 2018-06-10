#include "LockFreeLinkedQueue.hpp"
#include <string>

using namespace Utility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// float templates
template class LockFreeLinkedQueue<float>;
template class LockFreeLinkedQueue<double>;

// 8-bit integer templates
template class LockFreeLinkedQueue<int8_t>;
template class LockFreeLinkedQueue<uint8_t>;

// 16-bit integer templates
template class LockFreeLinkedQueue<int16_t>;
template class LockFreeLinkedQueue<uint16_t>;

// 32-bit integer templates
template class LockFreeLinkedQueue<int32_t>;
template class LockFreeLinkedQueue<uint32_t>;

// 64-bit integer templates
template class LockFreeLinkedQueue<int64_t>;
template class LockFreeLinkedQueue<uint64_t>;

// String template
template class LockFreeLinkedQueue<std::string>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
