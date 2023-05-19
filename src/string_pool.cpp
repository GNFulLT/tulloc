#include "string_pool.h"

StringPool::StringPool(std::size_t blockSize) noexcept : m_defaultBlockSize(blockSize)
{
}
