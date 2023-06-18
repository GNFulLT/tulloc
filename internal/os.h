#ifndef OS_H
#define OS_H

#include <cstddef>

#ifdef WIN32
#include <windows.h>
#include <memoryapi.h>
#else
#error NOT DEFINED FOR THIS PLATFORM
#endif

#ifdef WIN32
void* allocate_page(void* lpAddress,std::size_t size, DWORD flAllocationType,DWORD flProtect)
{
	return ::VirtualAlloc
    (
        nullptr,
        size,
        flAllocationType,
        flProtect
    );
}

void free_page(void* lpAddres,DWORD size,DWORD freeType)
{
    ::VirtualFree((void*)(lpAddres), size, freeType);

}

void* allocate_page_default(void* lpAddress, std::size_t size)
{
    return ::VirtualAlloc
    (
        nullptr,
        size,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );
}

void free_page_default(void* lpAddres, DWORD size)
{
    ::VirtualFree((void*)(lpAddres), size, MEM_FREE);

}

#else
#error NOT DEFINED FOR THIS PLATFORM
#endif

#endif // OS_H