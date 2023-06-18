#include "string_pool.h"

void StringPool::clear()
{
    for (auto& pChunk : m_chunks)
    {
        free(pChunk);
        pChunk = nullptr;
    }

    m_chunks.clear();

    m_pNext = nullptr;
    m_pLimit = nullptr;
}

TuString StringPool::allocate(const char* ptr)
{
    return allocate(ptr, ptr + strlen(ptr));
}

TuString StringPool::allocate(const char* start, const char* finish)
{
    const size_t length = finish - start;
    const size_t lengthWithNul = length + 1;
    char* ptr = allocMemory(lengthWithNul);
    memcpy(ptr, start, length);
    ptr[length] = L'\0'; // last char null

    return TuString{ ptr, length };
}

char* StringPool::allocMemory(std::size_t length)
{
    char* ptr = m_pNext;
    if (m_pNext + length <= m_pLimit)
    {
        m_pNext += length;
        return ptr;
    }

    if (length > MAX_STRING_LENGTH)
    {
        throw std::bad_alloc();
    }

    size_t chunkSizeInBytes = (length * sizeof(char)) + sizeof(StringBlock);
    if (chunkSizeInBytes < MIN_CHUNK_SIZE)
    {
        chunkSizeInBytes = MIN_CHUNK_SIZE;
    }

    uint8_t* pChunkStart = static_cast<uint8_t*>(malloc(chunkSizeInBytes));
    if (pChunkStart == nullptr)
    {
        static std::bad_alloc outOfMemory;
        throw outOfMemory;
    }

    m_pLimit = reinterpret_cast<char*>(pChunkStart + chunkSizeInBytes);

    StringBlock* pNewChunk = reinterpret_cast<StringBlock*>(pChunkStart);
    pNewChunk->_size = chunkSizeInBytes;

    m_pNext = reinterpret_cast<char*>(pNewChunk + 1);

    m_chunks.push_back(pNewChunk);

    return allocMemory(length);
}