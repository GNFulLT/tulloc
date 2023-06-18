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

    void clear();

    TuString allocate(const char* ptr);

    TuString allocate(const char* start, const char* finish);


private:

    struct StringBlock
    {
        size_t _size;

        char* charPtr;
    };

    char* m_pNext = nullptr;  
    char* m_pLimit = nullptr;   

    std::vector<StringBlock*> m_chunks{};

    char* allocMemory(std::size_t length);
};
#endif // STRING_POOL_H