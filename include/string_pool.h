#ifndef STRING_POOL_H
#define STRING_POOL_H

#include <vector>
#include "tustring.h"

#define MIN_CHUNK_SIZE 600000
#define MAX_STRING_LENGTH (2 << 19)

class StringPool
{
public:
    StringPool() = default;

    ~StringPool()
    {
        clear();
    }

    // Ban copy
    StringPool(const StringPool&) = delete;
    StringPool& operator=(const StringPool&) = delete;

    void clear()
    {
        for (auto& pChunk : m_chunks)
        {
            Free(pChunk);
            pChunk = nullptr;
        }

        m_chunks.clear();

        m_pNext = nullptr;
        m_pLimit = nullptr;
    }

    TuString allocString(const char* ptr)
    {
        return allocString(ptr, ptr + strlen(ptr));
    }

    TuString allocString(const char* start, const char* finish)
    {
        const size_t length = finish - start;
        const size_t lengthWithNul = length + 1;
        char* ptr = allocMemory(lengthWithNul);
        memcpy(ptr, start, length);
        ptr[length] = L'\0'; // last char null

        return TuString{ ptr, length };
    }


private:

    struct StringBlock
    {
        size_t _size;

        char* charPtr;
    };

    char* m_pNext = nullptr;  
    char* m_pLimit = nullptr;   

    std::vector<StringBlock*> m_chunks{};

    static void* allocate(size_t cbSize) noexcept
    {
        return malloc(cbSize);
    }

    static void Free(void* ptr) noexcept
    {
        return free(ptr);
    }

    char* allocMemory(size_t length)
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

        uint8_t* pChunkStart = static_cast<uint8_t*>(allocate(chunkSizeInBytes));
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
};
#endif // STRING_POOL_H