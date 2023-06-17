#ifndef STRING_POOL_H
#define STRING_POOL_H

#include <vector>
#include "tustring.h"
class StringPool
{
public:

    // Initialize an empty allocator.
    // Call AllocString when you need a new string.
    StringPool() = default;

    // Release all the allocated chunks (if any).
    ~StringPool()
    {
        clear();
    }

    // Ban copy
    StringPool(const StringPool&) = delete;
    StringPool& operator=(const StringPool&) = delete;

    // Release every allocated chunk.
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

    // Allocate a string using the pool allocator, deep-copying the string
    // from a C-style NUL-terminated string pointer.
    // Throws std::bad_alloc on allocation failure.
    TuString allocString(const char* ptr)
    {
        return allocString(ptr, ptr + strlen(ptr));
    }

    // Allocate a string using the pool allocator, deep-copying the string
    // from a [start, finish) "string view".
    // As per the STL convention: start is included, finish is excluded.
    // Throws std::bad_alloc on allocation failure.
    TuString allocString(const char* start, const char* finish)
    {
        const size_t length = finish - start;
        const size_t lengthWithNul = length + 1;
        char* ptr = allocMemory(lengthWithNul);
        memcpy(ptr, start, length);
        ptr[length] = L'\0'; // terminating NUL

        return TuString{ ptr, length };
    }


private:

    // A memory chunk is made by this header followed by the allocated chars.
    struct ChunkHeader
    {
        // Total chunk size, in bytes
        size_t SizeInBytes;

        // Followed by array of char characters 
        char Chars[1];
    };

    enum
    {
        // An allocated chunk must be minimum this size, in bytes
        kMinChunkSizeInBytes = 600000,

        // Can't alloc strings larger than that (in chars)
        kMaxStringLength = 1024 * 1024
    };


    char* m_pNext{};    // First available char slot in the current chunk
    char* m_pLimit{};   // One past last available char slot in the current chunk

    // Keep a list of all allocated chunks.
    // NOTE: ChunkHeader pointers are *owning* raw pointers, 
    // that will be released by this class destructor.
    std::vector<ChunkHeader*> m_chunks{};


    //------------------------------------------------------------------------------------
    // Helper Methods
    //------------------------------------------------------------------------------------


    //
    // Helper functions to allocate and free memory.
    // Those could be factored out as a trait class, to experiment with pool allocators
    // using different alloc/free techniques/APIs.
    // 

    // Request a memory allocation.
    // Return nullptr on failure.
    static void* allocate(size_t cbSize) noexcept
    {
        return malloc(cbSize);
    }

    // Free a previous allocation.
    static void Free(void* ptr) noexcept
    {
        return free(ptr);
    }

    // Helper function to allocate memory using the pool allocator.
    // 'length' is the number of chars requested.
    // 
    // First tries to carve memory from the current chunk.
    // If there's not enough space, allocates a new chunk.
    // Throws std::bad_alloc on allocation errors.
    char* allocMemory(size_t length)
    {
        // First let's try allocation in current chunk
        char* ptr = m_pNext;
        if (m_pNext + length <= m_pLimit)
        {
            // There's enough room in current chunk, so a simple pointer increase will do!
            m_pNext += length;
            return ptr;
        }

        // There's not enough room in current chunk. We need to allocate a new chunk.

        // Prevent request of too long strings
        if (length > kMaxStringLength)
        {
            throw std::bad_alloc();
        }

        // Allocate a new chunk, not smaller than minimum chunk size
        size_t chunkSizeInBytes = (length * sizeof(char)) + sizeof(ChunkHeader);
        if (chunkSizeInBytes < kMinChunkSizeInBytes)
        {
            chunkSizeInBytes = kMinChunkSizeInBytes;
        }

        uint8_t* pChunkStart = static_cast<uint8_t*>(allocate(chunkSizeInBytes));
        if (pChunkStart == nullptr)
        {
            // Allocation failure: throw std::bad_alloc
            static std::bad_alloc outOfMemory;
            throw outOfMemory;
        }

        // Point one past the last available char in current chunk
        m_pLimit = reinterpret_cast<char*>(pChunkStart + chunkSizeInBytes);

        // Prepare the chunk header
        ChunkHeader* pNewChunk = reinterpret_cast<ChunkHeader*>(pChunkStart);
        pNewChunk->SizeInBytes = chunkSizeInBytes;

        // Set the pointer to point to the free bytes to serve the next allocation
        m_pNext = reinterpret_cast<char*>(pNewChunk + 1);

        // Keep track of the newly allocated chunk,
        // adding it to the chunk pointer vector
        m_chunks.push_back(pNewChunk);

        // Now that we have allocated a new chunk, 
        // we can retry the allocation with a simple pointer increase
        return allocMemory(length);
    }
};
#endif // STRING_POOL_H